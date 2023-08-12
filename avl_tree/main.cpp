#include <iostream>

using namespace std;

class AVLNode {
public:
    int key;
    int height;
    int size;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int size(AVLNode* node) {
        return node ? node->size : 0;
    }

    int fator_balance(AVLNode* node) {
        return height(node->left) - height(node->right);
    }

    void update(AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y);
        update(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        update(x);
        update(y);
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (!node)
            return nullptr;

        update(node);

        if (fator_balance(node) > 1) {
            if (fator_balance(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (fator_balance(node) < -1) {
            if (fator_balance(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node)
            return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        return balance(node);
    }

    int findIndex(AVLNode* node, int key) {
        if (!node)
            return -1;

        int leftSize = size(node->left);

        if (key == node->key)
            return leftSize + 1;

        if (key < node->key)
            return findIndex(node->left, key);
        else {
            int rightIndex = findIndex(node->right, key);
            return (rightIndex != -1) ? leftSize + 1 + rightIndex : -1;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int findIndex(int key) {
        return findIndex(root, key);
    }
};

int main() {
    int Q;
    cin >> Q;

    AVLTree avlTree;

    for (int i = 0; i < Q; ++i) {
        int comando, x;
        cin >> comando >> x;

        if (comando == 1)
            avlTree.insert(x);
        else if (comando == 2) {
            int index = avlTree.findIndex(x);
            if (index == -1)
                cout << "Data tidak ada" << endl;
            else
                cout << index << endl;
        }
    }

    return 0;
}
