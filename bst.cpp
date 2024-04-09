#include "bst.hpp"

#include <iostream>


BSTNode::BSTNode(int key) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
}


//
uint64_t BSTNode::sum_of_depth(uint64_t current_depth) {
    uint64_t depth_total = current_depth;
    uint64_t child_depth = current_depth + 1;

    if (this->left != nullptr) {
        depth_total += this->left->sum_of_depth(child_depth);
    }
    if (this->right != nullptr) {
        depth_total += this->right->sum_of_depth(child_depth);
    }

    return depth_total;
}

void BST::insertion(BSTNode* new_node) {
    size++;

    if (root == nullptr) {
        root = new_node;
        return;
    }

    // Descend to bottom
    BSTNode *parent = root;
    BSTNode *current_node = root;

    while (true) {
        parent = current_node;

        if (current_node->key < new_node->key) {
            // Right
            if (current_node->right != nullptr) {
                current_node = current_node->right;
            } else {
                current_node->right = new_node;
                break;
            }
        } else {
            // Left
            if (current_node->left != nullptr) {
                current_node = current_node->left;
            } else {
                current_node->left = new_node;
                break;
            }
        }
    }
}

// 
uint64_t BSTNode::get_height_of_subtree(uint64_t current_depth) {
    uint64_t max_height = current_depth;

    if (this->left != nullptr) {
        uint64_t left_height = this->left->get_height_of_subtree(current_depth + 1);
        max_height = std::max(left_height, max_height);
    }
    if (this->right != nullptr) {
        uint64_t right_height = this->right->get_height_of_subtree(current_depth + 1);
        max_height = std::max(right_height, max_height);
    }

    return max_height;
}


BST::BST() {
    size = 0;
    root = nullptr;
}

// Gets the average depth of the tree
float BST::average_depth() {
    uint64_t total_depth = this->root->sum_of_depth(0);
    return (float)total_depth / size;
}

// Height of the tree
int BST::height() {
    if (root == nullptr) { return 1; }
    return root->get_height_of_subtree(0);
}