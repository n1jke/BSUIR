#pragma once

#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

namespace sml {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<const Key, T>>>
class map {
   public:
    enum Color { RED, BLACK };
    struct Node {
        std::pair<const Key, T> kv;
        Node* parent;
        Node* left;
        Node* right;
        Color color;
        Node(const Key& k, const T& v, Color c, Node* p)
            : kv(std::make_pair(k, v)),
              parent(p),
              left(nullptr),
              right(nullptr),
              color(c) {}
    };

   private:
    Node* _root;
    size_t _size;
    Compare _comp;
    Alloc _alloc;
    typename Alloc::template rebind<Node>::other _nodeAlloc;
    Node* _nil;	 // sentinel

    // allocate & construct a node
    Node* create_node(const Key& k, const T& v, Color c, Node* p) {
        Node* x = _nodeAlloc.allocate(1);
        std::allocator_traits<decltype(_nodeAlloc)>::construct(_nodeAlloc, x, k,
                                                               v, c, p);
        return x;
    }
    // destroy & deallocate a node


    void destroy_node(Node* x) {
        std::allocator_traits<decltype(_nodeAlloc)>::destroy(_nodeAlloc, x);
        _nodeAlloc.deallocate(x, 1);
    }

    // left rotate around x


    void rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != _nil)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == _nil)
            _root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // right rotate around x


    void rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != _nil)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == _nil)
            _root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    // fixup after insertion


    void insert_fixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_right(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
        _root->color = BLACK;
    }

    // transplant subtree u -> v


    void transplant(Node* u, Node* v) {
        if (u->parent == _nil)
            _root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    // find minimum from x
    static Node* minimum(Node* x, Node* nil) {
        while (x->left != nil)
            x = x->left;
        return x;
    }
    // find maximum from x
    static Node* maximum(Node* x, Node* nil) {
        while (x->right != nil)
            x = x->right;
        return x;
    }

    // fixup after deletion


    void erase_fixup(Node* x) {
        while (x != _root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotate_left(x->parent);
                    x = _root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotate_right(x->parent);
                    x = _root;
                }
            }
        }
        x->color = BLACK;
    }

    // destroy all nodes recursively


    void destroy_subtree(Node* x) {
        if (x == _nil)
            return;
        destroy_subtree(x->left);
        destroy_subtree(x->right);
        destroy_node(x);
    }

   public:
    // value_compare for compatibility
    class value_compare {
        friend class map;

       protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

       public:
        bool operator()(const std::pair<const Key, T>& a,
                        const std::pair<const Key, T>& b) const {
            return comp(a.first, b.first);
        }
    };

    // iterator
    template <bool IsConst>
    class _iterator {
        friend class map;
        using node_ptr =
            typename std::conditional<IsConst, const Node*, Node*>::type;

       private:
        node_ptr _node;
        const map* _m;
        explicit _iterator(node_ptr n, const map* m) : _node(n), _m(m) {}

       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, T>;
        using reference = typename std::conditional<IsConst, const value_type&,
                                                    value_type&>::type;
        using pointer = typename std::conditional<IsConst, const value_type*,
                                                  value_type*>::type;
        using difference_type = std::ptrdiff_t;

        _iterator() : _node(nullptr), _m(nullptr) {}

        reference operator*() const { return _node->kv; }
        pointer operator->() const { return &_node->kv; }

        _iterator& operator++() {
            if (_node->right != _m->_nil) {
                _node = minimum(_node->right, _m->_nil);
            } else {
                Node* p = _node->parent;
                while (p != _m->_nil && _node == p->right) {
                    _node = p;
                    p = p->parent;
                }
                _node = p;
            }
            return *this;
        }
        _iterator operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
        }

        _iterator& operator--() {
            if (_node == _m->_nil) {
                _node = maximum(_m->_root, _m->_nil);
            } else if (_node->left != _m->_nil) {
                _node = maximum(_node->left, _m->_nil);
            } else {
                Node* p = _node->parent;
                while (p != _m->_nil && _node == p->left) {
                    _node = p;
                    p = p->parent;
                }
                _node = p;
            }
            return *this;
        }
        _iterator operator--(int) {
            auto tmp = *this;
            --*this;
            return tmp;
        }

        bool operator==(const _iterator& o) const { return _node == o._node; }
        bool operator!=(const _iterator& o) const { return !(*this == o); }
    };

    using iterator = _iterator<false>;
    using const_iterator = _iterator<true>;

    // ctor/dtor
    map()
        : _size(0),
          _comp(Compare()),
          _alloc(Alloc()),
          _nodeAlloc(),
          _nil(nullptr),


          _root(nullptr) {
        _nil = create_node(Key(), T(), BLACK, nullptr);
        _nil->left = _nil->right = _nil->parent = _nil;
        _root = _nil;
    }

    explicit map(const Compare& comp, const Alloc& alloc = Alloc())
        : _size(0),
          _comp(comp),
          _alloc(alloc),
          _nodeAlloc(),
          _nil(nullptr),


          _root(nullptr) {
        _nil = create_node(Key(), T(), BLACK, nullptr);
        _nil->left = _nil->right = _nil->parent = _nil;
        _root = _nil;
    }

    map(const map& other) : map(other._comp, other._alloc) {
        for (auto& kv : other)
            insert(kv);
    }
    map(map&& other) noexcept
        : _root(other._root),
          _size(other._size),
          _comp(std::move(other._comp)),
          _alloc(std::move(other._alloc)),
          _nodeAlloc(std::move(other._nodeAlloc)),


          _nil(other._nil) {
        other._root = other._nil = nullptr;
        other._size = 0;
    }
    map& operator=(map o) {
        swap(o);
        return *this;
    }

    ~map() {


        if (_nil) {
            destroy_subtree(_root);
            destroy_node(_nil);
        }
    }

    // iterators


    iterator begin() { return iterator(minimum(_root, _nil), this); }


    const_iterator begin() const {
        return const_iterator(minimum(_root, _nil), this);
    }


    iterator end() { return iterator(_nil, this); }


    const_iterator end() const { return const_iterator(_nil, this); }

    // capacity


    bool empty() const { return _size == 0; }


    size_t size() const { return _size; }


    size_t max_size() const { return static_cast<size_t>(-1) / sizeof(Node); }

    // element access
    T& operator[](const Key& k) {
        auto it = insert(std::make_pair(k, T())).first;
        return it->second;
    }
    T& at(const Key& k) {
        auto it = find(k);
        if (it == end())
            throw std::out_of_range("map::at");
        return it->second;
    }
    const T& at(const Key& k) const {
        auto it = find(k);
        if (it == end())
            throw std::out_of_range("map::at");
        return it->second;
    }

    // modifiers
    std::pair<iterator, bool> insert(const std::pair<const Key, T>& kv) {
        Node* y = _nil;
        Node* x = _root;


        while (x != _nil) {
            y = x;
            if (_comp(kv.first, x->kv.first))
                x = x->left;
            else if (_comp(x->kv.first, kv.first))
                x = x->right;
            else
                return {iterator(x, this), false};
        }
        Node* z = create_node(kv.first, kv.second, RED, y);
        z->left = z->right = _nil;
        if (y == _nil)
            _root = z;
        else if (_comp(z->kv.first, y->kv.first))
            y->left = z;
        else
            y->right = z;
        ++_size;
        insert_fixup(z);
        return {iterator(z, this), true};
    }


    iterator erase(const_iterator pos) {
        Node* z = const_cast<Node*>(pos._node);
        Node* y = z;
        Node* x = nullptr;
        Color y_orig_color = y->color;
        if (z->left == _nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == _nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right, _nil);
            y_orig_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        destroy_node(z);
        --_size;
        if (y_orig_color == BLACK)
            erase_fixup(x);
        return iterator(x, this);
    }


    size_t erase(const Key& key) {
        auto it = find(key);
        if (it == end())
            return 0;
        erase(it);
        return 1;
    }


    void clear() {
        destroy_subtree(_root);
        _root = _nil;
        _size = 0;
    }

    void swap(map& other) noexcept {
        std::swap(_root, other._root);
        std::swap(_nil, other._nil);
        std::swap(_size, other._size);
        std::swap(_comp, other._comp);
        std::swap(_alloc, other._alloc);
    }

    // lookup


    iterator find(const Key& k) {
        Node* x = _root;
        while (x != _nil) {
            if (_comp(k, x->kv.first))
                x = x->left;
            else if (_comp(x->kv.first, k))
                x = x->right;
            else
                return iterator(x, this);
        }
        return end();
    }


    const_iterator find(const Key& k) const {
        return const_cast<map*>(this)->find(k);
    }

    // lower_bound / upper_bound


    iterator lower_bound(const Key& k) {
        Node* x = _root;
        Node* res = _nil;
        while (x != _nil) {
            if (!_comp(x->kv.first, k)) {
                res = x;
                x = x->left;
            } else
                x = x->right;
        }
        return iterator(res, this);
    }


    iterator upper_bound(const Key& k) {
        Node* x = _root;
        Node* res = _nil;
        while (x != _nil) {
            if (_comp(k, x->kv.first)) {
                res = x;
                x = x->left;
            } else
                x = x->right;
        }
        return iterator(res, this);
    }
    std::pair<iterator, iterator> equal_range(const Key& k) {
        return {lower_bound(k), upper_bound(k)};
    }

    // observers


    Compare key_comp() const { return _comp; }


    value_compare value_comp() const { return value_compare(_comp); }

    std::pair<iterator, bool> insert(const Key& key, const T& value) {
        return insert(std::make_pair(key, value));
    }

    friend class MainWindow;
    Node* root() const { return _root; }
    Node* nil() const { return _nil; }
};

}  // namespace sml
