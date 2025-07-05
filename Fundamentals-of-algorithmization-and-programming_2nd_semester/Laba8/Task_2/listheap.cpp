#include "listheap.h"

void ListHeap::insert(int value) {
    auto newNode = std::make_shared<HeapNode>(value);

    if (!root) {
        root = newNode;
    } else {
        std::queue<std::shared_ptr<HeapNode>> q;
        q.push(root);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            if (!current->left) {
                current->left = newNode;
                newNode->parent = current;
                break;
            } else if (!current->right) {
                current->right = newNode;
                newNode->parent = current;
                break;
            } else {
                q.push(current->left);
                q.push(current->right);
            }
        }
    }

    heapSize++;
    heapifyUp(newNode);
}

int ListHeap::extractMax() {
    if (!root) {
        throw std::out_of_range("Heap is empty");
    }

    int maxValue = root->value;

    if (heapSize == 1) {
        root.reset();
    } else {
        auto lastNode = getLastNode();
        root->value = lastNode->value;
        removeLastNode();
        heapifyDown(root);
    }

    heapSize--;
    return maxValue;
}

int ListHeap::getMax() const {
    if (!root) {
        throw std::out_of_range("Heap is empty");
    }
    return root->value;
}

std::vector<int> ListHeap::toVector() const {
    std::vector<int> result;
    if (!root) return result;

    std::queue<std::shared_ptr<HeapNode>> q;
    q.push(root);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        result.push_back(current->value);

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }

    return result;
}

void ListHeap::heapifyUp(std::shared_ptr<HeapNode> node) {
    while (auto parent = node->parent.lock()) {
        if (node->value <= parent->value) {
            break;
        }
        std::swap(node->value, parent->value);
        node = parent;
    }
}

void ListHeap::heapifyDown(std::shared_ptr<HeapNode> node) {
    while (node) {
        auto largest = node;

        if (node->left && node->left->value > largest->value) {
            largest = node->left;
        }

        if (node->right && node->right->value > largest->value) {
            largest = node->right;
        }

        if (largest == node) {
            break;
        }

        std::swap(node->value, largest->value);
        node = largest;
    }
}

std::shared_ptr<HeapNode> ListHeap::getLastNode() const {
    if (!root) return nullptr;

    std::queue<std::shared_ptr<HeapNode>> q;
    q.push(root);
    std::shared_ptr<HeapNode> last;

    while (!q.empty()) {
        last = q.front();
        q.pop();

        if (last->left) q.push(last->left);
        if (last->right) q.push(last->right);
    }

    return last;
}

void ListHeap::removeLastNode() {
    if (!root) return;

    std::queue<std::shared_ptr<HeapNode>> q;
    q.push(root);
    std::shared_ptr<HeapNode> lastParent;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current->left) {
            if (!current->left->left && !current->left->right) {
                lastParent = current;
            }
            q.push(current->left);
        }

        if (current->right) {
            if (!current->right->left && !current->right->right) {
                lastParent = current;
            }
            q.push(current->right);
        }
    }

    if (lastParent->right) {
        lastParent->right.reset();
    } else if (lastParent->left) {
        lastParent->left.reset();
    }
}
