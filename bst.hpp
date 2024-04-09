
#include "stdint.h"

class BSTNode {
public:
    int key;

    BSTNode *left;
    BSTNode *right;

    BSTNode(int key);
    
    uint64_t sum_of_depth(uint64_t current_depth);
    uint64_t get_height_of_subtree(uint64_t current_depth);
};


class BST {
public:
    BSTNode* root;
    int size;

    BST();

    void insertion(BSTNode* node);

    int height();
    float average_depth();
};