#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left, * right, * parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& root, Node*& pt) {
        Node* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right != nullptr) {
            pt->right->parent = pt;
        }

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_right;
        } else if (pt == pt->parent->left) {
            pt->parent->left = pt_right;
        } else {
            pt->parent->right = pt_right;
        }

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node*& root, Node*& pt) {
        Node* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left != nullptr) {
            pt->left->parent = pt;
        }

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_left;
        } else if (pt == pt->parent->left) {
            pt->parent->left = pt_left;
        } else {
            pt->parent->right = pt_left;
        }

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node*& root, Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) &&
               (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node* uncle_pt = grand_parent_pt->left;

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

public:
    RedBlackTree() { root = nullptr; }

    void insert(const int& data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
    }

    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr) {
            return pt;
        }

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void inorder() {
        inorderHelper(root);
    }

    void inorderHelper(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderHelper(root->left);
        cout << root->data << " ";
        inorderHelper(root->right);
    }
};

int main() {
    RedBlackTree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);

    cout << "Inorder traversal of the Red-Black tree is: ";
    tree.inorder();
    cout << endl;

    return 0;
}
