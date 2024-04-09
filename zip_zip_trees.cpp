


#include "zip_zip_trees.hpp"
#include <random>
#include <iostream>


int c = 3;

ZipZipTreeNode* ZipZipTreeNode::create_node(int key, int tree_size) {
    int r1 = 0, r2 = 0;

    while (rand() % 2 == 0) {
        r1 += 1;
    }

    if (tree_size >= 1) {
        int modulo = (int)(powf(log2f(tree_size), c));
        r2 = rand() % modulo;
    }

    return new ZipZipTreeNode(r1, r2, key);
}

ZipZipTreeNode::ZipZipTreeNode(int r1, int r2, int key) {
    this->r1 = r1;
    this->r2 = r2;
    this->key = key;

    this->left = nullptr;
    this->right = nullptr;
}

void ZipZipTreeNode::print() {
    std::cout << " V ";
    if (left != nullptr) {
        left->print();
    }
    std::cout << "( (" << this->r1 << "," << this->r2 << ") " << "," << this->key << ") ";
    if (right != nullptr) {
        right->print();
    }
    std::cout << " ^ ";
}

int ZipZipTreeNode::sum_of_depth(int current_depth) {
    int depth_total = current_depth;
    int child_depth = current_depth + 1;

    if (this->left != nullptr) {
        depth_total += this->left->sum_of_depth(child_depth);
    }
    if (this->right != nullptr) {
        depth_total += this->right->sum_of_depth(child_depth);
    }

    return depth_total;
}

// 
int ZipZipTreeNode::get_height_of_subtree(int current_depth) {
    int max_height = current_depth;

    if (this->left != nullptr) {
        int left_height = this->left->get_height_of_subtree(current_depth + 1);
        max_height = std::max(left_height, max_height);
    }
    if (this->right != nullptr) {
        int right_height = this->right->get_height_of_subtree(current_depth + 1);
        max_height = std::max(right_height, max_height);
    }

    return max_height;
}


ZipZipTree::ZipZipTree() {
    root = nullptr;
    size = 0;
}

void ZipZipTree::print() {
    if (root == nullptr) {
        std::cout << "Empty" << std::endl;
    } else {
        root->print();
    }
}

// Gets the average depth of the tree
float ZipZipTree::average_depth() {
    if (root == nullptr) { return 0; }

    int total_depth = this->root->sum_of_depth(0);
    return (float)total_depth / size;
}

// Height of the tree
int ZipZipTree::height() {
    if (root == nullptr) { return 0; }

    return root->get_height_of_subtree(0);
}

ZipZipTreeNode* ZipZipTree::create_node(int key) {
    // ZipZipTreeNode* new_node = new ZipZipTreeNode(key, size);
    ZipZipTreeNode* new_node = ZipZipTreeNode::create_node(key, size);

    return new_node;
}

void ZipZipTree::insertion(ZipZipTreeNode* new_node) {
    size++;

    if (root == nullptr) {
        root = new_node;
        return;
    }

    ZipZipTreeNode *parent = nullptr;
    ZipZipTreeNode *current_node = root;

    while (current_node != nullptr 
        && (current_node->r1 > new_node->r1
        || (new_node->r1 == current_node->r1 && current_node->r2 > new_node->r2)
        || (new_node->r1 == current_node->r1 && current_node->r2 == new_node->r2 && new_node->key > current_node->key))) {
        
        parent = current_node;

        if (new_node->key <= current_node->key) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    
    // If it is now a leaf (Might not need this case)
    if (current_node == nullptr) {
        if (new_node->key <= parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        return;
    }

    std::vector<ZipZipTreeNode*> nodes_on_path;
    std::vector<ZipZipTreeNode*> P;
    std::vector<ZipZipTreeNode*> Q;
    // Not a leaf
    if (current_node != nullptr) {
        ZipZipTreeNode* searched_node = current_node;
        // Now we descend to the bottom of the search path
        while (searched_node != nullptr) {

            if (new_node->key <= searched_node->key) {
                Q.push_back(searched_node);
            } else {
                P.push_back(searched_node);
            }

            nodes_on_path.push_back(searched_node);

            if (new_node->key <= searched_node->key) {
                searched_node = searched_node->left;
            } else {
                searched_node = searched_node->right;
            }
        }
        
        if (parent == nullptr) {
            root = new_node;
        } else {
            if (new_node->key <= parent->key) {
                parent->left = new_node;
            } else {
                parent->right = new_node;
            }
        }

        if (P.size() != 0) {
            new_node->left = P[0];

            P[P.size()-1]->right = nullptr;
        }
        if (Q.size() != 0) {
            new_node->right = Q[0];

            Q[Q.size()-1]->left = nullptr;
        }

        for (int i = 1; i < P.size(); i++) {
            P[i-1]->right = P[i];
        }
        for (int i = 1; i < Q.size(); i++) {
            Q[i-1]->left = Q[i];
        }

        // for (int i = 0; i < nodes_on_path.size(); i++) {
        //     std::cout << nodes_on_path[i]->key << std::endl;
        // }

    }

}