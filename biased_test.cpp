

#include <iostream>
#include <random>
#include <chrono>


// #include "AVL-Tree/AVLTreeNode.hpp"
// #include "AVL-Tree/AVLTree.hpp"
// #include "zip_trees.hpp"
// #include "zip_zip_trees.hpp"
// #include "treap.hpp"
// #include "bst.hpp"

#include "biased_treap.hpp"
#include "biased_zip_zip_tree.hpp"


const int MAX_INSERTS = 1048576; // 2 ^ 20
const int INSERTS = 1000000;

using namespace std::chrono;

int main(int argc, char** argv) {
    srand(time(NULL));
    std::srand(std::time(NULL));
    
    // Shuffles the order of the elements inserted
    std::vector<int> elements;
    for (int k = 0; k < MAX_INSERTS; k++) {
        elements.push_back(k);
    }
    std::shuffle(elements.begin(), elements.end(), std::default_random_engine(rand()));

    // Store the highest priority elements


    float optimal_height = 0;
    const int INCREMENT = 10000;

    const int AVERAGED_OVER = 5;

    // Testing
    for (int i = MAX_INSERTS % INCREMENT; i <= MAX_INSERTS; i += INCREMENT) {
        optimal_height = log2f(i);

        float running_depth = 0;
        float running_height = 0;
        
        uint64_t insert_time = 0;
        uint64_t search_time = 0;
        uint64_t low_weight_search_time = 0;
        uint64_t high_weight_search_time = 0;
        //
        for (int z = 0; z < AVERAGED_OVER; z++) {
            auto start = high_resolution_clock::now();

            // BiasedZipZipTree b_zip_zip_tree = BiasedZipZipTree();
            // for (int k = 0; k < i; k++) {
            //     b_zip_zip_tree.insertion(b_zip_zip_tree.create_node(elements[k], elements[k]));
            // }

            // running_depth += b_zip_zip_tree.average_depth();
            // running_height += b_zip_zip_tree.height();
            BiasedTreap b_treap = BiasedTreap();
            for (int k = 0; k < i; k++) {
                b_treap.insert(new BiasedTreapNode(elements[k], elements[k]));
            }

            running_depth += b_treap.average_depth();
            running_height += b_treap.height();
            auto stop = high_resolution_clock::now();

            auto millis_duration = duration_cast<milliseconds>(stop - start);
            insert_time += millis_duration.count();
            
            /// Searching Top 10%
            start = high_resolution_clock::now();

            for (int k = i - i/100; k < i; k++) {
                // b_zip_zip_tree.search(elements[k]);
                b_treap.search(elements[k]);
            }

            stop = high_resolution_clock::now();
            auto micro_duration = duration_cast<microseconds>(stop - start);
            high_weight_search_time += micro_duration.count();

            /// Searching Bottom 10%
            start = high_resolution_clock::now();

            for (int k = 0; k < i / 100; k++) {
                b_treap.search(elements[k]);
                // b_zip_zip_tree.search(elements[k]);
            }

            stop = high_resolution_clock::now();
            micro_duration = duration_cast<microseconds>(stop - start);
            low_weight_search_time += micro_duration.count();

            /// Searching everything
            start = high_resolution_clock::now();

            for (int k = 0; k < i; k++) {
                b_treap.search(elements[k]);
                // b_zip_zip_tree.search(elements[k]);
            }

            stop = high_resolution_clock::now();
            micro_duration = duration_cast<microseconds>(stop - start);
            search_time += micro_duration.count();
        }
        float average_depth = running_depth / AVERAGED_OVER;
        float average_height = running_height / AVERAGED_OVER;
        uint64_t average_insert_milliseconds = insert_time / AVERAGED_OVER;
        uint64_t average_search_microseconds = search_time / AVERAGED_OVER;
        uint64_t low_search_microseconds = low_weight_search_time / AVERAGED_OVER;
        uint64_t high_search_microseconds = high_weight_search_time / AVERAGED_OVER;
        // uint64_t average_search_micrioseconds = search_time / AVERAGED_OVER;
        std::cout << i << ", " << average_depth << ", " << average_depth / optimal_height << ", " << average_height << ", " << average_insert_milliseconds << ", " << average_search_microseconds << ", " << low_search_microseconds << ", " << high_search_microseconds << std::endl;
    }

    if (true) { return 0; }
    // Optimal
    std::cout << "---- Optimal ----" << std::endl;
    std::cout << "Average Depth: " << log2f(INSERTS) << std::endl;
    std::cout << "Tree Height: " << log2f(INSERTS) << std::endl;

    // // Shuffles the order of the elements inserted
    // std::vector<int> elements;
    // for (int i = 0; i < INSERTS; i++) {
    //     elements.push_back(i);
    // }
    // std::shuffle(elements.begin(), elements.end(), std::default_random_engine(rand()));

/*
    // Zip Tree
    ZipTree zip_tree = ZipTree();
    
    for (int i = 0; i < INSERTS; i++) {
        zip_tree.insertion(ZipTreeNode::create_node(elements[i]));
    }

    std::cout << "---- ZIP TREE ----" << std::endl;
    std::cout << "Average Depth: " << zip_tree.average_depth() << std::endl;
    std::cout << "Tree Height: " << zip_tree.height() << std::endl;

    /// Zip Zip Tree
    ZipZipTree zip_zip_tree = ZipZipTree();

    for (int i = 0; i < INSERTS; i++) {
        zip_zip_tree.insertion(zip_zip_tree.create_node(elements[i]));
    }

    std::cout << "---- ZIP ZIP TREE ----" << std::endl;
    std::cout << "Average Depth: " << zip_zip_tree.average_depth() << std::endl;
    std::cout << "Tree Height: " << zip_zip_tree.height() << std::endl;

    /// Treap
    Treap treap = Treap();

    for (int i = 0; i < INSERTS; i++) {
        // std::cout << "\nNEXT\n";
        treap.insert(new TreapNode(elements[i]));
        // treap.insert(new TreapNode( 10000 - i));
        // treap.print();
    }
    std::cout << "---- TREAP ----" << std::endl;
    std::cout << "Average Depth: " << treap.average_depth() << std::endl;
    std::cout << "Tree Height: " << treap.height() << std::endl;

    /// BST
    BST bst = BST();
    
    for (int i = 0; i < INSERTS; i++) {
        bst.insertion(new BSTNode(elements[i]));
    }
    std::cout << "---- BST ----" << std::endl;
    std::cout << "Average Depth: " << bst.average_depth() << std::endl;
    std::cout << "Tree Height: " << bst.height() << std::endl;

    /// AVL Tree
    AVLTree<int> avl = AVLTree<int>();

    for (int i = 0; i < INSERTS; i++) {
        avl.insert(elements[i]);
        // avl.insert(i);
    }
    std::cout << "---- AVL ----" << std::endl;
    std::cout << "Average Depth: " << avl.average_depth() << std::endl;
    std::cout << "Tree Height: " << avl.height() << std::endl;
    */
}
    
    
    // zip_zip_tree.insertion(zip_zip_tree.create_node(4));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(20));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(8));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(24));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(7));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(13));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(12));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(10));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(6));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(11));
    // zip_zip_tree.insertion(zip_zip_tree.create_node(19));