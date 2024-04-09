




class ZipTreeNode {
public:
    int rank;
    int key;

    ZipTreeNode* left;
    ZipTreeNode* right;

    static ZipTreeNode* create_node(int key);
    ZipTreeNode(int rank, int key);

    void print();

    bool is_leaf();

    int sum_of_depth(int current_depth);
    int get_height_of_subtree(int current_depth);
};

class ZipTree {
public:
    ZipTreeNode* root;
    int size;

    ZipTree();

    void print();

    void insertion(ZipTreeNode* new_node);
    void deletion(ZipTreeNode* new_node);


    int height();
    float average_depth();
};