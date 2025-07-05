#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sml {

template <typename T, typename Compare = std::less<T>>
class ListHeap {
   public:
    struct Node {
        T value;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        explicit Node(T v) : value(std::move(v)) {}
    };

    ListHeap() = default;
    ~ListHeap() = default;


    void insert(T value) {
        auto node = std::make_shared<Node>(std::move(value));
        if (!root_) {
            root_ = node;
        } else {
            auto spot = findInsertionParent();
            node->parent = spot;
            if (!spot->left)
                spot->left = node;
            else
                spot->right = node;
        }
        ++size_;
        heapifyUp(node);
    }


    T extractMax() {
        if (!root_)
            throw std::out_of_range("Heap is empty");
        T max = root_->value;
        if (size_ == 1) {
            root_.reset();
        } else {
            auto last = findLastNode();
            root_->value = std::move(last->value);
            removeLastNode();
            heapifyDown(root_);
        }
        --size_;
        return max;
    }

    const T& getMax() const {
        if (!root_)
            throw std::out_of_range("Heap is empty");
        return root_->value;
    }

    bool isEmpty() const noexcept { return size_ == 0; }
    size_t size() const noexcept { return size_; }

    void clear() noexcept {
        root_.reset();
        size_ = 0;
    }

    std::vector<T> toVector() const {
        std::vector<T> out;
        if (!root_)
            return out;
        std::queue<std::shared_ptr<Node>> q;
        q.push(root_);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            out.push_back(cur->value);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        return out;
    }

   private:
    std::shared_ptr<Node> root_;
    size_t size_ = 0;
    Compare cmp_;


    void heapifyUp(std::shared_ptr<Node> node) {
        while (auto p = node->parent.lock()) {
            if (!cmp_(p->value, node->value))
                break;
            std::swap(p->value, node->value);
            node = p;
        }
    }


    void heapifyDown(std::shared_ptr<Node> node) {
        while (node) {
            auto largest = node;
            if (node->left && cmp_(largest->value, node->left->value))
                largest = node->left;
            if (node->right && cmp_(largest->value, node->right->value))
                largest = node->right;
            if (largest == node)
                break;
            std::swap(largest->value, node->value);
            node = largest;
        }
    }

    std::shared_ptr<Node> findInsertionParent() const {
        std::queue<std::shared_ptr<Node>> q;
        q.push(root_);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (!cur->left || !cur->right)
                return cur;
            q.push(cur->left);
            q.push(cur->right);
        }
        return nullptr;	 // unreachable
    }

    std::shared_ptr<Node> findLastNode() const {
        std::shared_ptr<Node> last;
        std::queue<std::shared_ptr<Node>> q;
        q.push(root_);
        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left)
                q.push(last->left);
            if (last->right)
                q.push(last->right);
        }
        return last;
    }


    void removeLastNode() {
        std::shared_ptr<Node> last;
        std::shared_ptr<Node> parent;
        std::queue<std::shared_ptr<Node>> q;
        q.push(root_);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (cur->left) {
                if (!cur->left->left && !cur->left->right) {
                    parent = cur;
                    last = cur->left;
                }
                q.push(cur->left);
            }
            if (cur->right) {
                if (!cur->right->left && !cur->right->right) {
                    parent = cur;
                    last = cur->right;
                }
                q.push(cur->right);
            }
        }
        if (parent && last) {
            if (parent->right == last)
                parent->right.reset();
            else
                parent->left.reset();
        }
    }
};

}  // namespace sml
