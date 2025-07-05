#include "tree.h"
#include <QQueue>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

// Базовые операции
void BinarySearchTree::add(int value) {
    root = addNode(root, value);
}

void BinarySearchTree::remove(int value) {
    root = removeNode(root, value);
}

bool BinarySearchTree::contains(int value) const {
    return findNode(root, value) != nullptr;
}

QString BinarySearchTree::traverse(TraversalType type) const {
    QString result;
    switch(type) {
    case IN_ORDER:
        traverseInOrder(root, result);
        break;
    case PRE_ORDER:
        traversePreOrder(root, result);
        break;
    case POST_ORDER:
        traversePostOrder(root, result);
        break;
    case LEVEL_ORDER:
        traverseLevelOrder(result);
        break;
    }
    return result.trimmed();
}

// Расширенные операции
void BinarySearchTree::insertSubtree(int parentValue, bool isLeft, const BinarySearchTree& subtree) {
    TreeNode* parent = findNode(root, parentValue);
    if (!parent) return;

    if (isLeft) {
        deleteTree(parent->left);
        parent->left = copyTree(subtree.getRoot());
    } else {
        deleteTree(parent->right);
        parent->right = copyTree(subtree.getRoot());
    }
}

void BinarySearchTree::removeSubtree(int rootValue) {
    if (!root) return;

    if (root->value == rootValue) {
        deleteTree(root);
        root = nullptr;
        return;
    }

    TreeNode* parent = findParent(root, rootValue);
    if (!parent) return;

    if (parent->left && parent->left->value == rootValue) {
        deleteTree(parent->left);
        parent->left = nullptr;
    } else if (parent->right && parent->right->value == rootValue) {
        deleteTree(parent->right);
        parent->right = nullptr;
    }
}

void BinarySearchTree::insertBranch(int parentValue, bool isLeft, const BinarySearchTree& branch) {
    TreeNode* parent = findNode(root, parentValue);
    if (!parent || !branch.getRoot()) return;

    if (isLeft) {
        if (parent->left) {
            branch.getRoot()->left = parent->left;
        }
        parent->left = copyTree(branch.getRoot());
    } else {
        if (parent->right) {
            branch.getRoot()->right = parent->right;
        }
        parent->right = copyTree(branch.getRoot());
    }
}

void BinarySearchTree::removeBranch(int branchValue, bool isLeft) {
    TreeNode* parent = findNode(root, branchValue);
    if (!parent) return;

    if (isLeft) {
        deleteTree(parent->left);
        parent->left = nullptr;
    } else {
        deleteTree(parent->right);
        parent->right = nullptr;
    }
}

void BinarySearchTree::insertAtPosition(int parentValue, bool isLeft, int newValue) {
    TreeNode* parent = findNode(root, parentValue);
    if (!parent) return;

    TreeNode* newNode = new TreeNode(newValue);
    if (isLeft) {
        newNode->left = parent->left;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        parent->right = newNode;
    }
}

int BinarySearchTree::findLCA(int n1, int n2) const {
    TreeNode* lca = findLCANode(root, n1, n2);
    return lca ? lca->value : -1;
}

// Вспомогательные методы
TreeNode* BinarySearchTree::addNode(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);

    if (value < node->value) {
        node->left = addNode(node->left, value);
    } else if (value > node->value) {
        node->right = addNode(node->right, value);
    }

    return node;
}

TreeNode* BinarySearchTree::removeNode(TreeNode* node, int value) {
    if (!node) return node;

    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = minValueNode(node->right);
        node->value = temp->value;
        node->right = removeNode(node->right, temp->value);
    }

    return node;
}

TreeNode* BinarySearchTree::findNode(TreeNode* node, int value) const {
    if (!node || node->value == value) return node;
    return value < node->value ? findNode(node->left, value) : findNode(node->right, value);
}

TreeNode* BinarySearchTree::findParent(TreeNode* node, int value) const {
    if (!node || node->value == value) return nullptr;

    if ((node->left && node->left->value == value) ||
        (node->right && node->right->value == value)) {
        return node;
    }

    return value < node->value ? findParent(node->left, value) : findParent(node->right, value);
}

TreeNode* BinarySearchTree::findLCANode(TreeNode* node, int n1, int n2) const {
    if (!node) return nullptr;

    if (node->value > n1 && node->value > n2) {
        return findLCANode(node->left, n1, n2);
    }
    if (node->value < n1 && node->value < n2) {
        return findLCANode(node->right, n1, n2);
    }

    return node;
}

void BinarySearchTree::traverseInOrder(TreeNode* node, QString& result) const {
    if (!node) return;
    traverseInOrder(node->left, result);
    if (!result.isEmpty()) result += " ";
    result += QString::number(node->value);
    traverseInOrder(node->right, result);
}

void BinarySearchTree::traversePreOrder(TreeNode* node, QString& result) const {
    if (!node) return;
    if (!result.isEmpty()) result += " ";
    result += QString::number(node->value);
    traversePreOrder(node->left, result);
    traversePreOrder(node->right, result);
}

void BinarySearchTree::traversePostOrder(TreeNode* node, QString& result) const {
    if (!node) return;
    traversePostOrder(node->left, result);
    traversePostOrder(node->right, result);
    if (!result.isEmpty()) result += " ";
    result += QString::number(node->value);
}

void BinarySearchTree::traverseLevelOrder(QString& result) const {
    if (!root) return;

    QQueue<TreeNode*> queue;
    queue.enqueue(root);

    while (!queue.isEmpty()) {
        TreeNode* node = queue.dequeue();
        if (!result.isEmpty()) result += " ";
        result += QString::number(node->value);

        if (node->left) queue.enqueue(node->left);
        if (node->right) queue.enqueue(node->right);
    }
}

TreeNode* BinarySearchTree::minValueNode(TreeNode* node) const {
    TreeNode* current = node;
    while (current && current->left) current = current->left;
    return current;
}

void BinarySearchTree::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

TreeNode* BinarySearchTree::copyTree(TreeNode* node) const {
    if (!node) return nullptr;
    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}
