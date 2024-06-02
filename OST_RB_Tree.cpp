#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    int size;
    Color color;
    Node* left, * right, * parent;

    Node(int data) : data(data), size(1), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class OrderStatisticsTree {
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

        pt->size = 1 + size(pt->left) + size(pt->right);
        pt_right->size = 1 + size(pt_right->left) + size(pt_right->right);
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

        pt->size = 1 + size(pt->left) + size(pt->right);
        pt_left->size = 1 + size(pt_left->left) + size(pt_left->right);
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

        root->size = 1 + size(root->left) + size(root->right);

        return root;
    }

    int size(Node* node) {
        return (node == nullptr) ? 0 : node->size;
    }

public:
    OrderStatisticsTree() { root = nullptr; }

    void insert(const int& data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
    }

    Node* kthSmallest(Node* root, int k) {
        if (root == nullptr) {
            return nullptr;
        }

        int leftSize = size
