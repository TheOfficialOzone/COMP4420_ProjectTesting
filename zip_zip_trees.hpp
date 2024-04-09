
class ZipZipTreeNode {
public:
    int r1;
    int r2;
    int key;

    ZipZipTreeNode* left;
    ZipZipTreeNode* right;

    static ZipZipTreeNode* create_node(int key, int tree_size);

    ZipZipTreeNode(int r1, int r2, int key);

    void print();
    int sum_of_depth(int current_depth);
    int get_height_of_subtree(int current_depth);
};

class ZipZipTree {
public:
    ZipZipTreeNode* root;
    int size;

    ZipZipTree();

    void print();

    ZipZipTreeNode* create_node(int key);

    void insertion(ZipZipTreeNode* new_node);
    void deletion(ZipZipTreeNode* new_node);

    int height();
    float average_depth();
};