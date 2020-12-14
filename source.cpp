#include <iostream>
#include "BinSTree.h"
#include <queue>

using namespace std;

int main() {

    nodeTree<int>* a = new nodeTree<int>(1, 1);
    nodeTree<int>* b = new nodeTree<int>(2, 2);
    nodeTree<int>* c = new nodeTree<int>(3, 3);
    nodeTree<int>* d = new nodeTree<int>(4, 4);
    nodeTree<int>* e = new nodeTree<int>(5, 5);
    nodeTree<int>* f = new nodeTree<int>(6, 6);
    nodeTree<int>* g = new nodeTree<int>(7, 7);
    binSTree<int> tree;
    tree.insert(d);
    tree.insert(f);
    tree.insert(e);
    tree.insert(g);
    tree.insert(b);
    tree.insert(c);
    tree.insert(a);
    tree.preorder();
    tree.inorder();
    tree.postorder();
    tree.change_node_value_to_node_depth();
    tree.postorder();
    cout<<tree.leaf_count()<<endl;
    return 0;
}