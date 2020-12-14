#pragma once
#include <iostream>
#include <queue>
#include <stack>

template <class T>
struct nodeTree {
    nodeTree* left;
    nodeTree* right;
    int key;
    T value;
    nodeTree(T v, int k, nodeTree* l = NULL, nodeTree* r = NULL) {
        value = v;
        key = k;
        left = l;
        right = r;
    }
};

template <class T>
class binSTree {
    nodeTree<T>* first;

    int length_p(nodeTree<T>* q) {
        if(!q) {
            return 0;
        }
        return 1 + length_p(q->left) + length_p(q->right);
    }

    void copy_tree(nodeTree<T>* q) {
        if(q) {
            nodeTree<T>* g = new nodeTree<T>(q->value, q->key);
            insert(g);
            copy_tree(q->left);
            copy_tree(q->right);
        }
        return;
    }

    int isLeaf(nodeTree<T>* q) {
        if(!q)
            return 0;

        if(q->left || q->right)
            return isLeaf(q->left) + isLeaf(q->right);
        
        return 1;
        
    }

    int get_level_p(nodeTree<T>* q, nodeTree<T>* pos, int level) {
        if(!pos)
            return 0;
        if(pos == q)
            return level;
        
        return get_level_p(q, pos->left, level + 1) + get_level_p(q, pos->right, level + 1);
    }


    int rev_level(nodeTree<T>* q, int lev = 0) {
        if(!q)
            return lev - 1;
        
        if(q->left || q->right) {
            return std::max(rev_level(q->left, lev + 1), rev_level(q->right, lev + 1));
        }

        return lev;
    }

public:
    binSTree() {
        first = NULL;
    }

    binSTree(const binSTree<T>& a) {
        first = NULL;
        copy_tree(a.first);
    }

    void insert(nodeTree<T>* q) {
        nodeTree<T>* u = q;
        if(empty()) {
            first = u;
            return;
        }
        nodeTree<T>* g = first;
        while(true) {
            if(u->key > g->key) {
                if(g->right) {
                    g = g->right;
                }
                else {
                    g->right = u;
                    break;
                }
            }
            else if(u->key < g->key) {
                if(g->left) {
                    g = g->left;
                }
                else {
                    g->left = u;
                    break;
                }
            }
            else
            {
                break;
            }
            
        }
    }

    void deleteM(int k) {
        if(first->key == k) {
            if(first->left) {
                nodeTree<T>* q = first->right;
                first = first->left;
                if(q)
                    insert(q);
            }
            else {
                first = first->right;
            }
        }
        else {
            nodeTree<T>* parent = first;
            nodeTree<T>* q;
            if(first->key > k)
                q = first->left;
            else 
                q = first->right;
            while(1) {
                if(!q) {
                    return;
                }
                if(q->key > k) {
                    parent = q;
                    q = q->left;
                }
                if(q->key < k) {
                    parent = q;
                    q = q->right;
                }
                if(q->key == k) {
                    if(q->left) {
                        if(q == parent->left) {
                            parent->left = q->left;
                        }
                        else {
                            parent->right = q->left;
                        }
                        if(q->right) {
                            insert(q->right);
                        }
                    }
                    else if(q->right) {
                        if(q == parent->left) {
                            parent->left = q->right;
                        }
                        else {
                            parent->right = q->right;
                        }
                    }
                    else {
                        if(q == parent->left) {
                            parent->left = nullptr;
                        }
                        else {
                            parent->right = nullptr;
                        }
                    }
                    return;
                }
            }
        }
    }


    nodeTree<T>* find(int k) {
        nodeTree<T>* q = first;
        while(1) {
            if(!q) {
                return NULL;
            }
            if(q->key == k) {
                return q;
            }
            if(q->key > k) {
                q = q->left;
            }
            if(q->key < k) {
                q = q->right;
            }
        }
    }


    bool empty() const {
        if(first)
            return false;
        return true;
    }

    int length() {
        return length_p(first);
    }

    int max_level() {
        if(empty())
            return 0;
        
        std::queue<nodeTree<T>*> q1, q2;
        q1.push(first);
        int ans = 0;
        while(1) {
            while(!q1.empty()) {
                nodeTree<T>* u = q1.front();
                if(u->left)
                    q2.push(u->left);
                if(u->right)
                    q2.push(u->right);
                q1.pop();
            }
            
            if(q2.empty()) {
                return ans;
            }


            while(!q2.empty()) {
                q1.push(q2.front());
                q2.pop();
            }
            ++ans;
        }
        return rev_level(first);
    }

    int leaf_count() {
        return isLeaf(first);
    }

    void change_node_value_to_node_depth() {
        int max_lev = max_level(), lev = 0;
        std::queue<nodeTree<T>*> q1, q2;
        first->value = max_lev;
        q1.push(first);

        while(1) {
            ++lev;
            while(!q1.empty()) {
                nodeTree<T>* u = q1.front();
                if(u->left)
                    q2.push(u->left);
                if(u->right)
                    q2.push(u->right);
                q1.pop();
            }
            
            if(q2.empty()) {
                return;
            }

            while(!q2.empty()) {
                q2.front()->value = rev_level(q2.front());
                q1.push(q2.front());
                q2.pop();
            }
        }
    }

    bool isFull() {
        return leaf_count() == 1<<max_level();
    }

    int get_level(nodeTree<T>* q) {
        return get_level_p(q, first, 0);
    }

    void preorder() {
        std::stack<nodeTree<T>*> a;
        if(empty())
            return;

        a.push(first);
        std::cout<<first->value<<" ";
        nodeTree<T>* q = first;
        bool t = 0;
        while(1) {
            if(q->left && !t) {
                q = q->left;
                a.push(q);
                std::cout<<q->value<<" ";
            }
            else if(q->right) {
                a.pop();
                q = q->right;
                a.push(q);
                std::cout<<q->value<<" ";
                t = 0;
            }
            else {
                a.pop();
                if(a.empty()) {
                    std::cout<<std::endl;
                    return;
                }
                q = a.top();
                t = 1;
            }
        }

    }

    void inorder() { // որոնման բինար ծառերի համար այս շրջանցման դեպքում կարող ենք ուղղակի սորտավորել ըստ բանալու
        if(empty())
            return;
        std::stack<nodeTree<T>*> a;
        a.push(first);
        bool t = 1;
        nodeTree<T>* q = first;
        while(1) {
            if(q->left && t) {
                q = q->left;
                a.push(q);
            }
            else if(q->right) {
                std::cout<<q->value<<" ";
                a.pop();
                q = q->right;
                a.push(q);
                t = 1;
            }
            else {
                std::cout<<q->value<<" ";
                a.pop();
                if(a.empty()) {
                    std::cout<<std::endl;
                    return;
                }
                
                q = a.top();
                t = 0;
            }
        }
    }

    void postorder() {
        if(empty())
            return;
        
        std::stack<nodeTree<T>*> a;
        a.push(first);
        nodeTree<T>* q = first, * last = first;

        while(1) {
            if(q->left && last != q->left && last != q->right) {
                q = q->left;
                a.push(q);
            }
            else if(q->right && last != q->right) {
                q = q->right;
                a.push(q);
            }
            else {
                std::cout<<q->value<<" ";
                last = a.top();
                a.pop();
                if(a.empty()) {
                    std::cout<<std::endl;
                    return;
                }

                q = a.top();
            }
        }
    }

    

};