#pragma once
#include <QString>
#include <functional>
#include <memory>
#include <stack>
#include <utility>


namespace sml {
template <typename Key, typename Value, typename Compare = std::less<Key>>
class AVLTree {
   public:
    struct Node {
        Key key;
        Value value;
        int height;	 // rh - lh
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        template <typename K, typename V>
        explicit Node(K&& k, V&& v)
            : key(std::forward<K>(k)),
              value(std::forward<V>(v)),
              height(1),
              left(nullptr),
              right(nullptr) {}
    };

    void clear() noexcept { root_.reset(); }

   private:
    using NodePtr = std::unique_ptr<Node>;
    NodePtr root_;
    Compare compare_;

    int height(const Node* node) const noexcept {
        return node ? node->height : 0;
    }


    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left.get()),
                                        height(node->right.get()));
        }
    }

    int bFactor(const Node* node) const noexcept {
        return node ? height(node->right.get()) - height(node->left.get()) : 0;
    }


    // RR disbalance


    NodePtr rotateLeft(NodePtr node) noexcept {
        auto new_root = std::move(node->right);
        node->right = std::move(new_root->left);
        new_root->left = std::move(node);

        updateHeight(new_root->left.get());
        updateHeight(new_root.get());

        return new_root;  // new subtree root
    }

    // LL disbalance


    NodePtr rotateRight(NodePtr node) noexcept {
        auto new_root = std::move(node->left);
        node->left = std::move(new_root->right);
        new_root->right = std::move(node);

        updateHeight(new_root->right.get());
        updateHeight(new_root.get());

        return new_root;  // new subtree root
    }

    // LR disbalance


    NodePtr rotateLeftRight(NodePtr node) noexcept {
        node->left = rotateLeft(std::move(node->left));
        return rotateRight(std::move(node));
    }

    // RL disbalance


    NodePtr rotateRightLeft(NodePtr node) noexcept {
        node->right = rotateRight(std::move(node->right));
        return rotateLeft(std::move(node));
    }


    NodePtr balance(NodePtr node) noexcept {


        if (node == nullptr) {
            return nullptr;
        }

        updateHeight(node.get());

        // left disbalance
        if (bFactor(node.get()) > 1) {
            if (bFactor(node->right.get()) < 0) {
                return rotateRightLeft(std::move(node));
            }
            return rotateLeft(std::move(node));
        }

        // right disbalnce
        if (bFactor(node.get()) < -1) {
            if (bFactor(node->left.get()) > 0) {
                return rotateLeftRight(std::move(node));
            }
            return rotateRight(std::move(node));
        }
        return node;
    }


    NodePtr insertNode(NodePtr node, Key&& key, Value&& value) {
        if (!node) {
            return std::make_unique<Node>(std::move(key), std::move(value));
        }

        if (compare_(key, node->key)) {
            node->left = insertNode(std::move(node->left), std::move(key),
                                    std::move(value));
        } else if (compare_(node->key, key)) {
            node->right = insertNode(std::move(node->right), std::move(key),
                                     std::move(value));
        } else {
            node->value = std::move(value);
            return node;
        }

        return balance(std::move(node));
    }

    Node* findMin(Node* node) const noexcept {


        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }


    NodePtr removeMin(NodePtr node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left) {
            node->left = removeMin(std::move(node->left));
            return balance(std::move(node));
        }

        return std::move(node->right);
    }

    Node* findMax(Node* node) const noexcept {


        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }


    NodePtr removeMax(NodePtr node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->right) {
            node->right = removeMax(std::move(node->right));
            return balance(std::move(node));
        }

        return std::move(node->right);
    }


    NodePtr removeNode(NodePtr node, const Key& key) {
        if (!node) {
            return nullptr;
        }

        if (compare_(key, node->key)) {
            node->left = removeNode(std::move(node->left), key);
        } else if (compare_(node->key, key)) {
            node->right = removeNode(std::move(node->right), key);
        } else {
            // find
            if (!node->left && !node->right) {
                return nullptr;	 // list node
            } else if (!node->left) {
                return std::move(node->right);	// rchild
            } else if (!node->right) {
                return std::move(node->left);  // lchild
            } else {
                // 2 children
                auto successor = findMin(node->right.get());

                auto new_node =
                    std::make_unique<Node>(successor->key, successor->value);

                new_node->left = std::move(node->left);
                new_node->right = removeMin(std::move(node->right));
                updateHeight(new_node.get());

                node = std::move(new_node);
            }
        }

        return balance(std::move(node));
    }

    Node* findNode(Node* node, const Key& key) const noexcept {


        while (node) {
            if (compare_(key, node->key)) {
                node = node->left.get();
            } else if (compare_(node->key, key)) {
                node = node->right.get();
            } else {
                break;
            }
        }
        return node;
    }

   public:
    AVLTree() noexcept = default;
    ~AVLTree() noexcept = default;

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    AVLTree(AVLTree&&) noexcept = default;
    AVLTree& operator=(AVLTree&&) noexcept = default;


    void insert(Key key, Value value) {
        root_ = insertNode(std::move(root_), std::move(key), std::move(value));
    }


    bool erase(const Key& key) {
        Node* node = findNode(root_.get(), key);
        if (!node) {
            return false;
        }

        root_ = removeNode(std::move(root_), key);
        return true;
    }

    Value* find(const Key& key) noexcept {
        Node* node = findNode(root_.get(), key);
        return node ? &node->value : nullptr;
    }

    const Value* find(const Key& key) const noexcept {
        Node* node = findNode(root_.get(), key);
        return node ? &node->value : nullptr;
    }

    bool empty() const noexcept { return !root_; }

    Node* getRoot() const noexcept { return root_.get(); }


    void PreOrderTraversal(Node* root, std::vector<std::string>& result) {
        if (!root) {
            return;
        }
        std::stack<Node*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node* node = stack.top();
            stack.pop();
            result.push_back((QString::number(node->key) + ": " + node->value).toStdString());
            if (node->right) {
                stack.push(node->right.get());
            }
            if (node->left) {
                stack.push(node->left.get());
            }
        }
    }


    void PostOrderTraversal(Node* root, std::vector<std::string>& result) {
        if (!root) {
            return;
        }
        std::stack<Node*> stack1, stack2;
        stack1.push(root);
        while (!stack1.empty()) {
            Node* node = stack1.top();
            stack1.pop();
            stack2.push(node);
            if (node->left) {
                stack1.push(node->left.get());
            }
            if (node->right) {
                stack1.push(node->right.get());
            }
        }
        while (!stack2.empty()) {
            Node* node = stack2.top();
            stack2.pop();
            result.push_back((QString::number(node->key) + ": " + node->value).toStdString());
        }
    }


    void InOrderTraversal(Node* root, std::vector<std::string>& result) {
        std::stack<Node*> stack;
        Node* current = root;
        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            result.push_back((QString::number(current->key) + ": " +
                             current->value).toStdString());
            current = current->right;
        }
    }
};
}  // namespace sml
