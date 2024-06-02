struct Node {
    int data;
    int size;
    int height;
    Node* left;
    Node* right;

    Node(int data) : data(data), size(1), height(1), left(nullptr), right(nullptr) {}
};

class OrderStatisticsTree {
private:
    Node* root;

    int height(Node* N) {
        return (N == nullptr) ? 0 : N->height;
    }

    int size(Node* N) {
        return (N == nullptr) ? 0 : N->size;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        y->size = size(y->left) + size(y->right) + 1;

        x->height = max(height(x->left), height(x->right)) + 1;
        x->size = size(x->left) + size(x->right) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        x->size = size(x->left) + size(x->right) + 1;

        y->height = max(height(y->left), height(y->right)) + 1;
        y->size = size(y->left) + size(y->right) + 1;

        return y;
    }

    int getBalance(Node* N) {
        return (N == nullptr) ? 0 : height(N->left) - height(N->right);
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* kthSmallest(Node* root, int k) {
        if (root == nullptr) {
            return nullptr;
        }

        int leftSize = size(root->left);

        if (k == leftSize + 1) {
            return root;
        } else if (k <= leftSize) {
            return kthSmallest(root->left, k);
        } else {
            return kthSmallest(root->right, k - leftSize - 1);
        }
    }

    int rank(Node* root, int data) {
        if (root == nullptr) {
            return 0;
        }

        if (data < root->data) {
            return rank(root->left, data);
        } else if (data > root->data) {
            return 1 + size(root->left) + rank(root->right, data);
        } else {
            return size(root->left) + 1;
        }
    }

public:
    OrderStatisticsTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int kthSmallest(int k) {
        Node* result = kthSmallest(root, k);
        return (result == nullptr) ? -1 : result->data;
    }

    int rank(int data) {
        return rank(root, data);
    }
};

int main() {
    OrderStatisticsTree tree;

    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(30);

    cout << "The 3rd smallest element is " << tree.kthSmallest(3) << endl; // Output: 10
    cout << "The rank of element 25 is " << tree.rank(25) << endl;        // Output: 6

    return 0;
}
