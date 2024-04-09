


class BiasedTreapNode {
public:
    int r1;
    float r2;
    int key;

    BiasedTreapNode *left;
    BiasedTreapNode *right;

    BiasedTreapNode(int key, int weight);

    void print();
    bool is_leaf();
    
    int sum_of_depth(int current_depth);
    int get_height_of_subtree(int current_depth);
};


class BiasedTreap {
public:
    BiasedTreapNode* root;
    int size;

    BiasedTreap();

    void insert(BiasedTreapNode* new_node);

    bool search(int key);
    
    void print();

    int height();
    float average_depth();
};

// class BiasedTreapNode {
// public:
//     float priority;
//     int key;

//     BiasedTreapNode *parent;
//     BiasedTreapNode *left;
//     BiasedTreapNode *right;

//     BiasedTreapNode(int key);

//     void print();
//     bool is_leaf();
    
//     int sum_of_depth(int current_depth);
//     int get_height_of_subtree(int current_depth);
// };


// class BiasedTreap {
// public:
//     BiasedTreapNode* root;
//     int size;

//     BiasedTreap();

//     void insert(BiasedTreapNode* new_node);
    
//     void print();

//     int height();
//     float average_depth();
// };