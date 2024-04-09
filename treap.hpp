


class TreapNode {
public:
    float priority;
    int key;

    TreapNode *left;
    TreapNode *right;

    TreapNode(int key);

    void print();
    bool is_leaf();
    
    int sum_of_depth(int current_depth);
    int get_height_of_subtree(int current_depth);
};


class Treap {
public:
    TreapNode* root;
    int size;

    Treap();

    void insert(TreapNode* new_node);
    
    void print();

    int height();
    float average_depth();
};

// class TreapNode {
// public:
//     float priority;
//     int key;

//     TreapNode *parent;
//     TreapNode *left;
//     TreapNode *right;

//     TreapNode(int key);

//     void print();
//     bool is_leaf();
    
//     int sum_of_depth(int current_depth);
//     int get_height_of_subtree(int current_depth);
// };


// class Treap {
// public:
//     TreapNode* root;
//     int size;

//     Treap();

//     void insert(TreapNode* new_node);
    
//     void print();

//     int height();
//     float average_depth();
// };