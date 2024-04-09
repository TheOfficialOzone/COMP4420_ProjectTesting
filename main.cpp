
#include <iostream>
#include <random>
#include <chrono>


#include "AVL-Tree/AVLTreeNode.hpp"
#include "AVL-Tree/AVLTree.hpp"
#include "zip_trees.hpp"
#include "zip_zip_trees.hpp"
#include "treap.hpp"
#include "bst.hpp"
/*
F == 4, 6
D == 2, 4
S == 4, 20
H == 2, 8
X == 2, 24
G == 0, 7
M == 2, 13
L == 1, 12
J == 0, 10
K == 3, 11
*/
// Do K at the end

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

    float optimal_height = 0;
    const int INCREMENT = 10000;

    const int AVERAGED_OVER = 5;

    // Testing
    for (int i = MAX_INSERTS % INCREMENT; i <= MAX_INSERTS; i += INCREMENT) {
        optimal_height = log2f(i);

        float running_depth = 0;
        float running_height = 0;
        uint64_t time = 0;

        //
        for (int z = 0; z < AVERAGED_OVER; z++) {
            auto start = high_resolution_clock::now();

            AVLTree<int> avl = AVLTree<int>();
            for (int k = 0; k < i; k++) {
                avl.insert(elements[k]);
            }
            float average_depth = avl.average_depth();

            running_depth += average_depth;
            running_height += avl.height();
            // Treap treap = Treap();
            // for (int k = 0; k < i; k++) {
            //     treap.insert(new TreapNode(elements[k]));
            // }
            // float average_depth = treap.average_depth();

            // running_depth += average_depth;
            // running_height += treap.height();
            // BST bst = BST();
            // for (int k = 0; k < i; k++) {
            //     bst.insertion(new BSTNode(elements[k]));
            // }
            // float average_depth = bst.average_depth();

            // running_depth += average_depth;
            // running_height += bst.height();
            // ZipTree zip_tree = ZipTree();
            // for (int k = 0; k < i; k++) {
            //     zip_tree.insertion(ZipTreeNode::create_node(elements[k]));
            // }
            // float average_depth = zip_tree.average_depth();

            // running_depth += average_depth;
            // running_height += zip_tree.height();
            // ZipZipTree zip_zip_tree = ZipZipTree();

            // for (int k = 0; k < i; k++) {
            //     zip_zip_tree.insertion(zip_zip_tree.create_node(elements[k]));
            // }
            // float average_depth = zip_zip_tree.average_depth();

            // running_depth += average_depth;
            // running_height += zip_zip_tree.height();

            // Operations have finished running
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<milliseconds>(stop - start);
            time += duration.count();

        }
        float average_depth = running_depth / AVERAGED_OVER;
        float average_height = running_height / AVERAGED_OVER;
        uint64_t average_milliseconds = time / AVERAGED_OVER;
        std::cout << i << ", " << average_depth << ", " << average_depth / optimal_height << ", " << average_height << ", " << average_milliseconds << std::endl;
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