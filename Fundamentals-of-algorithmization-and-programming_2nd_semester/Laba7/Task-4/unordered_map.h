#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#pragma once
#include <chrono>
#include <cstddef>
#include <functional>
#include <new>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

enum class ProbingStrategy { kLinear, kQuadratic, kDoubleHashing };

namespace sml {

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          ProbingStrategy Strategy = ProbingStrategy::kDoubleHashing>
class unordered_map {
public:
    struct Stats {
        std::size_t collisions = 0;
        std::vector<std::size_t> collision_hashes;	// h'(key) для коллизий
        std::vector<std::size_t> probe_counts;	// количество проб при вставке
        std::vector<double> search_times;		// время поиска (мкс)

        void reset() {
            collisions = 0;
            collision_hashes.clear();
            probe_counts.clear();
            search_times.clear();
        }
    };

    const Stats& get_stats() const { return stats_; }
    void reset_stats() { stats_.reset(); }

    using key_type = Key;
    using map_type = Value;
    using value_type = std::pair<const Key, Value>;
    using size_type = std::size_t;

    explicit unordered_map(size_type init_size = 16)
        : table_(init_size), size_(0) {
        if (init_size == 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
    }

    explicit unordered_map(size_type init_size, const Hash& hash)
        : table_(init_size), size_(0), hash_(hash) {
        if (init_size == 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
    }

    unordered_map(const unordered_map& other)
        : table_(other.table_.size()),
          size_(0),
          hash_(other.hash_),
          equal_(other.equal_) {
        for (size_type i = 0; i < other.table_.size(); ++i) {
            const Bucket& cell = other.table_[i];
            if (cell.state == CellState::kOccupied) {
                const value_type* vp = cell.ptr();
                insert(vp->first, vp->second);
            }
        }
    }

    unordered_map& operator=(const unordered_map& other) {
        if (this != &other) {
            clear();
            table_.assign(other.table_.size(), Bucket());
            hash_ = other.hash_;
            equal_ = other.equal_;
            size_ = 0;
            for (size_type i = 0; i < other.table_.size(); ++i) {
                const Bucket& cell = other.table_[i];
                if (cell.state == CellState::kOccupied) {
                    const value_type* vp = cell.ptr();
                    insert(vp->first, vp->second);
                }
            }
        }
        return *this;
    }

    ~unordered_map() { clear(); }

    unordered_map(unordered_map&&) = delete;
    unordered_map& operator=(unordered_map&&) = delete;

    bool insert(const Key& key, const Value& value) {
        ensure_capacity();
        auto [ptr, inserted] = emplace_impl(key, value);
        return inserted;
    }

    Value& operator[](const Key& key) {
        ensure_capacity();
        auto [ptr, inserted] = emplace_impl(key, Value{});
        return ptr->second;
    }

    size_type erase(const Key& key) {
        size_type idx = find_index(key);
        if (idx == kNpos)
            return 0;
        destroy_at(idx);
        table_[idx].state = CellState::kDeleted;
        --size_;
        return 1;
    }

    size_type size() const noexcept { return size_; }

    bool empty() const noexcept { return size_ == 0; }

    size_type bucket_count() const noexcept { return table_.size(); }

    double load_factor() const noexcept {
        return static_cast<double>(size_) / table_.size();
    }

    Value* find(const Key& key) {
        size_type idx = find_index(key);
        if (idx == kNpos)
            return nullptr;
        return &table_[idx].ptr()->second;
    }

    void rehash(size_type new_cap) {
        if (new_cap < size_) {
            throw std::invalid_argument("New cap too small");
        }
        rehash_impl(new_cap);
    }

private:
    enum class CellState { kEmpty, kOccupied, kDeleted };

    struct Bucket {
        std::aligned_storage_t<sizeof(value_type), alignof(value_type)> storage;
        CellState state = CellState::kEmpty;
        value_type* ptr() noexcept {
            return std::launder(reinterpret_cast<value_type*>(&storage));
        }
    };

    static constexpr size_type kNpos = static_cast<size_type>(-1);
    static constexpr double kMaxLoad = 0.7;

    std::vector<Bucket> table_;
    size_type size_;
    Hash hash_;
    KeyEqual equal_;

    Stats stats_;

    std::pair<value_type*, bool> emplace_impl(const Key& key, const Value& value) {
        size_type cap = table_.size();
        size_type h1  = hash_(key) % cap;
        size_type h2  = (Strategy == ProbingStrategy::kDoubleHashing)
                     ? (1 + (hash_(key) % (cap - 1))) : 0;
        size_type idx = kNpos;
        std::size_t local_collisions = 0;

        for (size_type i = 0; i < cap; ++i) {
            size_type pos = probe_index(h1, h2, i, cap);
            Bucket& cell = table_[pos];
            if (cell.state == CellState::kEmpty) {
                idx = pos;
                break;
            }
            if (cell.state == CellState::kDeleted && idx == kNpos) {
                idx = pos;
            }
            if (cell.state == CellState::kOccupied) {
                if (equal_(cell.ptr()->first, key)) {
                    cell.ptr()->second = value;
                    stats_.probe_counts.push_back(i+1);
                    return { cell.ptr(), false };
                } else {
                    ++local_collisions;
                    stats_.collisions++;
                    stats_.collision_hashes.push_back(pos);
                }
            }
        }

        if (idx == kNpos) {
            rehash_impl(table_.size() * 2);
            return emplace_impl(key, value);
        }
        Bucket& cell = table_[idx];
        new (&cell.storage) value_type(key, value);
        cell.state = CellState::kOccupied;
        ++size_;
        stats_.probe_counts.push_back(local_collisions+1);
        return { cell.ptr(), true };
    }

    static size_type probe_index(size_type h1, size_type h2, size_type i,
                                 size_type cap) noexcept {
        switch (Strategy) {
            case ProbingStrategy::kLinear:
                return (h1 + i) % cap;
            case ProbingStrategy::kQuadratic:
                return (h1 + i + i * i) % cap;
            case ProbingStrategy::kDoubleHashing:
                return (h1 + i * h2) % cap;
        }
        return (h1 + i) % cap;
    }

    size_type find_index(const Key& key) const noexcept {
        size_type cap = table_.size();
        size_type h1 = hash_(key) % cap;
        size_type h2 = (Strategy == ProbingStrategy::kDoubleHashing)
                           ? (1 + (hash_(key) % (cap - 1)))
                           : 0;

        for (size_type i = 0; i < cap; ++i) {
            size_type pos = probe_index(h1, h2, i, cap);
            const Bucket& cell = table_[pos];
            if (cell.state == CellState::kEmpty) {
                return kNpos;
            }
            if (cell.state == CellState::kOccupied &&
                equal_(cell.ptr()->first, key)) {
                return pos;
            }
        }
        return kNpos;
    }

    void ensure_capacity() {
        if (load_factor() > kMaxLoad) {
            rehash_impl(table_.size() * 2);
        }
    }

    void rehash_impl(size_type new_cap) {
        std::vector<Bucket> old = std::move(table_);
        table_.assign(new_cap, Bucket());
        size_ = 0;
        for (auto& cell : old) {
            if (cell.state == CellState::kOccupied) {
                value_type* vp = cell.ptr();
                emplace_impl(vp->first, vp->second);
                vp->~value_type();
            }
        }
    }

    void destroy_at(size_type idx) noexcept {
        table_[idx].ptr()->~value_type();
    }

    void clear() noexcept {
        for (auto& cell : table_) {
            if (cell.state == CellState::kOccupied) {
                cell.ptr()->~value_type();
            }
            cell.state = CellState::kEmpty;
        }
        size_ = 0;
    }

    Value* find_with_stats(const Key& key) {
        auto start = std::chrono::high_resolution_clock::now();
        size_type idx = find_index(key);
        auto end = std::chrono::high_resolution_clock::now();
        double micros =
            std::chrono::duration<double, std::micro>(end - start).count();
        stats_.search_times.push_back(micros);
        if (idx == kNpos)
            return nullptr;
        return &table_[idx].ptr()->second;
    }
};

struct UniversalHash {
    using result_type = std::size_t;
    using argument_type = std::size_t;
    std::size_t a, b, p, m;
    UniversalHash(std::size_t m_, std::size_t p_ = 2147483647)
        : p(p_), m(m_) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> dist(1, p - 1);
        a = dist(gen);
        b = dist(gen);
    }
    std::size_t operator()(std::size_t key) const {
        return ((a * key + b) % p) % m;
    }
};

}  // namespace sml

#endif	// UNORDERED_MAP_H
