#pragma once
#include <QString>
#include <functional>
#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

namespace sml {

template <typename Key, typename Value, typename Compare = std::less<Key>>
class AVLTree {
public:
    struct Node {
        Key key;
        Value value;
        int height;        // subtree height
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;      // raw pointer to parent

        template <typename K, typename V>
        explicit Node(K&& k, V&& v, Node* p = nullptr)
            : key(std::forward<K>(k)), value(std::forward<V>(v)), height(1),
              left(nullptr), right(nullptr), parent(p) {}
    };

    enum TraversalType { IN_ORDER, PRE_ORDER, POST_ORDER, LEVEL_ORDER };

    AVLTree() noexcept = default;
    ~AVLTree() noexcept = default;
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree(AVLTree&&) noexcept = default;
    AVLTree& operator=(AVLTree&&) noexcept = default;

    // Basic operations
    void add(Key key, Value value) {
        root_ = insertNode(std::move(root_), std::move(key), std::move(value), nullptr);
    }
    bool remove(const Key& key) {
        if (!findNode(root_.get(), key)) return false;
        root_ = removeNode(std::move(root_), key);
        return true;
    }
    bool contains(const Key& key) const noexcept {
        return findNode(root_.get(), key) != nullptr;
    }
    QString traverse(TraversalType type = IN_ORDER) const {
        QString result;
        switch (type) {
            case IN_ORDER:  traverseInOrder(root_.get(), result); break;
            case PRE_ORDER: traversePreOrder(root_.get(), result); break;
            case POST_ORDER: traversePostOrder(root_.get(), result); break;
            case LEVEL_ORDER: traverseLevelOrder(result); break;
        }
        return result.trimmed();
    }

    // Subtree operations
    void insertSubtree(const Key& parentKey, bool isLeft, const AVLTree& subtree) {
        Node* parent = findNode(root_.get(), parentKey);
        if (!parent) return;
        if (isLeft) parent->left.reset(copyTree(subtree.root_.get(), parent));
        else parent->right.reset(copyTree(subtree.root_.get(), parent));
    }

    void removeSubtree(const Key& rootKey) {
        Node* target = findNode(root_.get(), rootKey);
        if (!target) return;
        if (target == root_.get()) root_.reset();
        else if (target->parent->left.get() == target) target->parent->left.reset();
        else target->parent->right.reset();
    }

    // Branch operations
    void insertBranch(const Key& parentKey, bool isLeft, const AVLTree& branch) {
        Node* parent = findNode(root_.get(), parentKey);
        if (!parent || !branch.root_) return;
        Node* cloned = copyTree(branch.root_.get(), parent);
        if (isLeft) parent->left.reset(cloned);
        else parent->right.reset(cloned);
    }

    void removeBranch(const Key& branchKey, bool isLeft) {
        Node* parent = findNode(root_.get(), branchKey);
        if (!parent) return;
        if (isLeft) parent->left.reset(); else parent->right.reset();
    }

    // Position-based insertion
    void insertAtPosition(const Key& parentKey, bool isLeft, Key newKey, Value newVal) {
        Node* parent = findNode(root_.get(), parentKey);
        if (!parent) return;
        auto newNode = std::make_unique<Node>(std::move(newKey), std::move(newVal), parent);
        if (isLeft) {
            newNode->left = std::move(parent->left);
            if (newNode->left) newNode->left->parent = newNode.get();
            parent->left = std::move(newNode);
        } else {
            newNode->right = std::move(parent->right);
            if (newNode->right) newNode->right->parent = newNode.get();
            parent->right = std::move(newNode);
        }
    }

    // LCA via binary lifting
    Key findLCA(const Key& k1, const Key& k2) {
        if (!root_) return Key();
        // Collect nodes & parent pointers
        std::vector<Node*> nodes;
        std::unordered_map<Node*, int> idx;
        depth_.clear(); parent0_.clear(); up_.clear();
        std::function<void(Node*)> dfs = [&](Node* u) {
            if (!u) return;
            idx[u] = nodes.size();
            nodes.push_back(u);
            parent0_.push_back(u->parent);
            depth_.push_back(u->parent ? depth_[idx[u->parent]] + 1 : 0);
            dfs(u->left.get()); dfs(u->right.get());
        };
        dfs(root_.get());

        int n = nodes.size();
        int LOG = std::ceil(std::log2(n+1));
        up_.assign(LOG, std::vector<Node*>(n, nullptr));
        for (int i = 0; i < n; ++i) up_[0][i] = parent0_[i];
        for (int j = 1; j < LOG; ++j)
            for (int i = 0; i < n; ++i)
                if (up_[j-1][i])
                    up_[j][i] = up_[j-1][ idx[ up_[j-1][i] ] ];

        Node* a = findNode(root_.get(), k1);
        Node* b = findNode(root_.get(), k2);
        if (!a || !b) return Key();
        int ia = idx[a], ib = idx[b];
        if (depth_[ia] < depth_[ib]) std::swap(ia, ib);
        // lift ia
        for (int j = LOG-1; j >= 0; --j)
            if (depth_[ia] - (1<<j) >= depth_[ib]) ia = idx[ up_[j][ia] ];
        if (ia == ib) return nodes[ia]->key;
        for (int j = LOG-1; j >= 0; --j) {
            if (up_[j][ia] && up_[j][ia] != up_[j][ib]) {
                ia = idx[ up_[j][ia] ];
                ib = idx[ up_[j][ib] ];
            }
        }
        Node* lca = parent0_[ia];
        return lca ? lca->key : Key();
    }

private:
    using NodePtr = std::unique_ptr<Node>;
    NodePtr root_;
    Compare compare_;
    // LCA support
    std::vector<int> depth_;
    std::vector<Node*> parent0_;
    std::vector<std::vector<Node*>> up_;

    // Height & balance
    int height(const Node* n) const noexcept { return n ? n->height : 0; }
    void updateHeight(Node* n) noexcept {
        n->height = 1 + std::max(height(n->left.get()), height(n->right.get()));
    }
    int balanceFactor(const Node* n) const noexcept { return height(n->right.get()) - height(n->left.get()); }

    // Rotations
    NodePtr rotateLeft(NodePtr x) noexcept {
        NodePtr y = std::move(x->right);
        x->right = std::move(y->left);
        if (x->right) x->right->parent = x.get();
        y->left = std::move(x);
        y->parent = y->left->parent;
        y->left->parent = y.get();
        updateHeight(y->left.get()); updateHeight(y.get());
        return y;
    }
    NodePtr rotateRight(NodePtr y) noexcept {
        NodePtr x = std::move(y->left);
        y->left = std::move(x->right);
        if (y->left) y->left->parent = y.get();
        x->right = std::move(y);
        x->parent = x->right->parent;
        x->right->parent = x.get();
        updateHeight(x->right.get()); updateHeight(x.get());
        return x;
    }
    NodePtr balance(NodePtr n) noexcept {
        updateHeight(n.get());
        int bf = balanceFactor(n.get());
        if (bf > 1) {
            if (balanceFactor(n->right.get()) < 0) n->right = rotateRight(std::move(n->right));
            return rotateLeft(std::move(n));
        }
        if (bf < -1) {
            if (balanceFactor(n->left.get()) > 0) n->left = rotateLeft(std::move(n->left));
            return rotateRight(std::move(n));
        }
        return n;
    }

    // Insert & remove
    NodePtr insertNode(NodePtr node, Key key, Value val, Node* parent) {
        if (!node) return std::make_unique<Node>(std::move(key), std::move(val), parent);
        if (compare_(key, node->key)) node->left = insertNode(std::move(node->left), std::move(key), std::move(val), node.get());
        else if (compare_(node->key, key)) node->right = insertNode(std::move(node->right), std::move(key), std::move(val), node.get());
        else node->value = std::move(val);
        return balance(std::move(node));
    }
    Node* findMin(Node* n) const noexcept { while (n && n->left) n = n->left.get(); return n; }
    NodePtr removeMin(NodePtr n) {
        if (!n->left) return std::move(n->right);
        n->left = removeMin(std::move(n->left));
        return balance(std::move(n));
    }
    NodePtr removeNode(NodePtr node, const Key& key) {
        if (!node) return nullptr;
        if (compare_(key, node->key)) node->left = removeNode(std::move(node->left), key);
        else if (compare_(node->key, key)) node->right = removeNode(std::move(node->right), key);
        else {
            if (!node->left) return std::move(node->right);
            if (!node->right) return std::move(node->left);
            Node* m = findMin(node->right.get());
            node->key = m->key; node->value = m->value;
            node->right = removeNode(std::move(node->right), m->key);
        }
        return balance(std::move(node));
    }
    Node* findNode(Node* n, const Key& key) const noexcept {
        while (n) {
            if (compare_(key, n->key)) n = n->left.get();
            else if (compare_(n->key, key)) n = n->right.get();
            else break;
        }
        return n;
    }

    // Traversals
    void traverseInOrder(Node* n, QString& res) const {
        if (!n) return; traverseInOrder(n->left.get(), res);
        if (!res.isEmpty()) res += ' ';
        res += QString::number(n->key);
        traverseInOrder(n->right.get(), res);
    }
    void traversePreOrder(Node* n, QString& res) const {
        if (!n) return; if (!res.isEmpty()) res += ' ';
        res += QString::number(n->key);
        traversePreOrder(n->left.get(), res);
        traversePreOrder(n->right.get(), res);
    }
    void traversePostOrder(Node* n, QString& res) const {
        if (!n) return;
        traversePostOrder(n->left.get(), res);
        traversePostOrder(n->right.get(), res);
        if (!res.isEmpty()) res += ' ';
        res += QString::number(n->key);
    }
    void traverseLevelOrder(QString& res) const {
        if (!root_) return;
        std::queue<Node*> q; q.push(root_.get());
        while (!q.empty()) {
            Node* u = q.front(); q.pop();
            if (!res.isEmpty()) res += ' ';
            res += QString::number(u->key);
            if (u->left) q.push(u->left.get());
            if (u->right) q.push(u->right.get());
        }
    }

    // Copy tree recursively
    Node* copyTree(const Node* src, Node* parent) {
        if (!src) return nullptr;
        Node* dst = new Node(src->key, src->value, parent);
        dst->left.reset(copyTree(src->left.get(), dst));
        dst->right.reset(copyTree(src->right.get(), dst));
        return dst;
    }
};

} // namespace sml
