
class BiasedZipZipTreeNode {
public:
    int r1;
    int r2;
    int key;

    BiasedZipZipTreeNode* left;
    BiasedZipZipTreeNode* right;

    static BiasedZipZipTreeNode* create_node(int key, int tree_size, int weight);

    BiasedZipZipTreeNode(int r1, int r2, int key);

    void print();
    int sum_of_depth(int current_depth);
    int get_height_of_subtree(int current_depth);
};

class BiasedZipZipTree {
public:
    BiasedZipZipTreeNode* root;
    int size;

    BiasedZipZipTree();

    void print();

    BiasedZipZipTreeNode* create_node(int key, int weight);


    bool search(int key);
    void insertion(BiasedZipZipTreeNode* new_node);
    void deletion(BiasedZipZipTreeNode* new_node);

    int height();
    float average_depth();
};