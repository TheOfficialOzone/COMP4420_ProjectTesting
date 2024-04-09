#include <iostream>

#include "treap.hpp"
#include "random"

TreapNode::TreapNode(int key) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
    // this->parent = nullptr;
    this->priority = (float)std::rand() / RAND_MAX;
}

bool TreapNode::is_leaf() {
    return this->left != nullptr || this->right != nullptr;
}
    
int TreapNode::sum_of_depth(int current_depth) {
    int total_depth = current_depth;

    if (this->left != nullptr) {
        total_depth += this->left->sum_of_depth(current_depth + 1);
    }
    if (this->right != nullptr) {
        total_depth += this->right->sum_of_depth(current_depth + 1);
    }

    return total_depth;
}

int TreapNode::get_height_of_subtree(int current_depth) {
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

void TreapNode::print() {
    std::cout << " V ";
    if (left != nullptr) {
        left->print();
    }
    std::cout << "_(" << this->priority << "," << this->key << ")_ ";
    if (right != nullptr) {
        right->print();
    }
    std::cout << " ^ ";
}

Treap::Treap() {
    this->root = nullptr;
    this->size = 0;
}

void Treap::print() {
    if (root == nullptr) {
        std::cout << "Empty" << std::endl;
    } else {
        root->print();
        std::cout << std::endl;
    }
}

int Treap::height() {
    if (this->root == nullptr) { return 0; }
    return this->root->get_height_of_subtree(1);
}

float Treap::average_depth() {
    if (this->root == nullptr) { return 0; }
    return (float)this->root->sum_of_depth(0) / size;
}

void Treap::insert(TreapNode* new_node) {
    size++;
    
    if (root == nullptr) {
        root = new_node;
        return;
    }
    
    // Treaps
    std::vector<TreapNode*> treaps_on_path;
    TreapNode *parent = nullptr;
    TreapNode *current_node = root;

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
        TreapNode *parent = treaps_on_path[i + 1];

        TreapNode *parent_parent = nullptr;
        if (i >= 0) {
            parent_parent = treaps_on_path[i];
        }


        if (new_node->priority > parent->priority) {
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
                    } else {
                        std::cout << "FUCK ME 2\n";
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
                    } else {
                        std::cout << "FUCK ME 2\n";
                    }
                }

            } else {
                std::cout << "FUCK ME\n";
            }
        }
    }

    if (is_root) {
        root = new_node;
    }
}

// void Treap::insert(TreapNode* new_node) {
//     size++;

//     if (root == nullptr) {
//         root = new_node;
//         return;
//     }

//     // Descend to bottom
//     TreapNode *parent = root;
//     TreapNode *current_node = root;

//     std::cout << "New Node: " << new_node->key << " " << new_node->priority << std::endl;

//     while (true) {
//         parent = current_node;

//         if (current_node->key < new_node->key) {
//             std::cout << "Right\n";
//             // Right
//             if (current_node->right != nullptr) {
//                 std::cout << "Descending past: " << current_node->key << std::endl;
//                 if (current_node->right->parent != current_node) {
//                     std::cout << "Broken Link\n";
//                 }

//                 current_node = current_node->right;

//             } else {
//                 current_node->right = new_node;
//                 new_node->parent = current_node;
//                 break;
//             }
//         } else {
//             // Left
//             std::cout << "Left\n";
//             if (current_node->left != nullptr) {
//                 std::cout << "Descending past: " << current_node->key << std::endl;
//                 current_node = current_node->left;
//             } else {
//                 current_node->left = new_node;
//                 new_node->parent = current_node;
//                 break;
//             }
//         }
//     }

//     bool new_node_root = false;
//     TreapNode* parent_parent = nullptr;

//     if (parent != nullptr) {
//         std::cout << "Current Parent: " << parent->key << " " << parent->priority << std::endl;
//     }
//     // Rotate to top
//     while (parent != nullptr && 
//         parent->priority < new_node->priority ) {
//         parent_parent = parent->parent;
//         if (parent == root) {
//             new_node_root = true;
//         }

//         std::cout << "ITER\n";
//         if (parent_parent != nullptr) {
//             std::cout << "Parent_Parent: " << parent_parent->key << " " << parent_parent->priority << std::endl;
//         } else {
//             std::cout << "No parent" << std::endl;
//         }
//         std::cout << "Parent: " << parent->key << " " << parent->priority << std::endl;
//         if (parent->left != nullptr) {
//             std::cout << "Parent Left: " << parent->left->key << " " << parent->left->priority << std::endl;
//         }
//         if (parent->right != nullptr) {
//             std::cout << "Parent Right: " << parent->right->key << " " << parent->right->priority << std::endl;
//         }
//         // if ()

//         if (new_node == parent->left) {
//             std::cout << "Right Rotate\n";
//             parent->left = new_node->right;
//             new_node->right = parent;

//             // Parent needs to switch
//             if (parent_parent != nullptr) {
//                 if (parent->parent->left == parent) {
//                     parent->parent->left = new_node;
//                 }
//                 if (parent->parent->right == parent) {
//                     parent->parent->right = new_node;
//                 }
//             } else {
//                 // We are the root
//                 std::cout << "NEW ROOT\n";
//             }
//             parent->parent = new_node;
//             new_node->parent = parent_parent;

//         } else if (new_node == parent->right) {
//             std::cout << "Left Rotate\n";
//             parent->right = new_node->left;
//             new_node->left = parent;

//             // Parent needs to switch
//             if (parent_parent != nullptr) {
//                 if (parent_parent->left == parent) {
//                     parent_parent->left = new_node;
//                 }
//                 if (parent_parent->right == parent) {
//                     parent_parent->right = new_node;
//                 }
//             } else {
//                 // We are the root
//                 std::cout << "NEW ROOT\n";
//             }
//             parent->parent = new_node;
//             new_node->parent = parent_parent;
//         } else {
//             std::cout << "NOT A CHILD" << std::endl;
//             // std::cout << 
//         }

//         if ((new_node->left == parent || new_node->right == parent) &&
//          (parent_parent == nullptr || (parent_parent->left == new_node || parent_parent->right == new_node)) &&
//          (parent->parent == new_node)) {
//             std::cout << "Valid ROT\n";
//         } else {
//             std::cout << "INVALID ROT\n";

//             std::cout << (new_node->left == parent || new_node->right == parent) << std::endl;
//             std::cout << (parent_parent == nullptr || (parent_parent->left == new_node || parent_parent->right == new_node)) << std::endl;
//             std::cout << (parent->parent == new_node) << std::endl;;

//             std::cout << "New Node: " << new_node->key << " " << std::endl;
//             std::cout << "Previous parent's parent: " <<  parent->parent->key << std::endl;
//             if (new_node->left != nullptr) {
//                 std::cout << "Left Child: " << new_node->left->key << " Parent " << new_node->left->parent->key << std::endl;
//             }
//             if (new_node->right != nullptr) {
//                 std::cout << "Right Child " << new_node->right->key << " Parent " << new_node->right->parent->key << std::endl;
//             }
//         }

//         // Go to the next parent
//         parent = parent_parent;
//     }

//     if (new_node_root) { 
//         std::cout << "Root rotate\n";
//         root = new_node; 
//     }
// }