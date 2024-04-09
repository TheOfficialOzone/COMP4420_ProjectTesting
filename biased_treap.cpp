

#include "biased_treap.hpp"


#include <iostream>
#include "random"

BiasedTreapNode::BiasedTreapNode(int key, int weight) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
    // this->parent = nullptr;
    this->r2 = (float)std::rand() / RAND_MAX;

    this->r1 = (int)log2f(weight);
    while (rand() % 2 == 0) {
        this->r1 += 1;
    }
}

bool BiasedTreapNode::is_leaf() {
    return this->left != nullptr || this->right != nullptr;
}
    
int BiasedTreapNode::sum_of_depth(int current_depth) {
    int total_depth = current_depth;

    if (this->left != nullptr) {
        total_depth += this->left->sum_of_depth(current_depth + 1);
    }
    if (this->right != nullptr) {
        total_depth += this->right->sum_of_depth(current_depth + 1);
    }

    return total_depth;
}

int BiasedTreapNode::get_height_of_subtree(int current_depth) {
    int max_height = current_depth;

    if (this->left != nullptr) {
        int other_height = this->left->get_height_of_subtree(current_depth + 1);
        max_height = std::max(max_height, other_height);
    }
    if (this->right != nullptr) {
        int other_height = this->right->get_height_of_subtree(current_depth + 1);
        max_height = std::max(max_height, other_height);
    }

    return max_height;
}

void BiasedTreapNode::print() {
    std::cout << " V ";
    if (left != nullptr) {
        left->print();
    }
    std::cout << "_(" << "( " << this->r1 << ", " << this->r2 << ")" << "," << this->key << ")_ ";
    if (right != nullptr) {
        right->print();
    }
    std::cout << " ^ ";
}

BiasedTreap::BiasedTreap() {
    this->root = nullptr;
    this->size = 0;
}

void BiasedTreap::print() {
    if (root == nullptr) {
        std::cout << "Empty" << std::endl;
    } else {
        root->print();
        std::cout << std::endl;
    }
}

int BiasedTreap::height() {
    if (this->root == nullptr) { return 0; }
    return this->root->get_height_of_subtree(1);
}

float BiasedTreap::average_depth() {
    if (this->root == nullptr) { return 0; }
    return (float)this->root->sum_of_depth(0) / size;
}

// Searches the DS for the key
bool BiasedTreap::search(int key) {
    BiasedTreapNode *current = root;

    while (current != nullptr) {

        if (current->key == key) { return true; }
        if (current->key < key) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return false;
}

void BiasedTreap::insert(BiasedTreapNode* new_node) {
    size++;
    
    if (root == nullptr) {
        root = new_node;
        return;
    }
    
    // BiasedTreaps
    std::vector<BiasedTreapNode*> treaps_on_path;
    BiasedTreapNode *parent = nullptr;
    BiasedTreapNode *current_node = root;

    while (current_node != nullptr) {
        parent = current_node;

        treaps_on_path.push_back(current_node);

        if (new_node->key < current_node->key) {
            // Left
            current_node = current_node->left;
        } else {
            // Right
            current_node = current_node->right;
        }
    }

    if (new_node->key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    // Now rotate up
    bool is_root = false;

    // Want to skip the parent node
    for (int i = treaps_on_path.size() - 2; i >= -1; i--) {
        BiasedTreapNode *parent = treaps_on_path[i + 1];

        BiasedTreapNode *parent_parent = nullptr;
        if (i >= 0) {
            parent_parent = treaps_on_path[i];
        }


        if (new_node->r1 > parent->r1 || 
        (new_node->r1 == parent->r1 && new_node->r2 > parent->r2)) {
            if (parent == root) { is_root = true;}
            // Find path
            if (parent->left == new_node) {
                parent->left = new_node->right;
                new_node->right = parent;

                if (parent_parent != nullptr) {
                    if (parent_parent->left == parent) {
                        parent_parent->left = new_node;
                    } else 
                    if (parent_parent->right == parent) {
                        parent_parent->right = new_node;
                    }
                }
            } else 
            if (parent->right == new_node) {
                parent->right = new_node->left;
                new_node->left = parent;

                if (parent_parent != nullptr) {
                    if (parent_parent->left == parent) {
                        parent_parent->left = new_node;
                    } else 
                    if (parent_parent->right == parent) {
                        parent_parent->right = new_node;
                    }
                }
            }
        }
    }

    if (is_root) {
        root = new_node;
    }
}
