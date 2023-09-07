#include <iostream>
#include <climits>
#include <cmath>
#include "Tree.h"

using namespace std;

Node::Node(){
        value = 0;
        parent = NULL;
}

void Node::recount(Node* root, int &Nodeindex, int &Leafindex){
        if (root->children.empty()){
                //cout << root->value << endl;
                Leafindex++;
                return;
        }
        else{
                Nodeindex--;
                for (auto child : root->children){
                        recount(child,Nodeindex,Leafindex);
                }
        }
}
/*
    This function recursively sets the values of a tree's nodes given an input vector of options. 
    If a node has no children, its value is set to the value at the corresponding index in the options vector and its index is updated. 
    If a node has children, the function is called recursively on each child node. 
*/
void Node::setTree(Node* root, vector<double> options, int& Nodeindex, int& Leafindex) {
        if (root->children.empty()) {
                root->value = options[Leafindex];
                root->index = Leafindex; // Set the index of the new node
                root->leaf = true;
                Leafindex++;
        }
        else {
                Nodeindex--;
                root->index = Nodeindex;
                root->leaf = false;
                for (auto child : root->children) {
                        setTree(child, options, Nodeindex, Leafindex);
                }
        }
}

/*
  This function generates a tree with a specified max depth and branching factor.
  The nodes are created as children of the input node, up to the max depth.
  The parent of each child is set to be the input node.
*/
void Node::generateTree(Node *node, int depth, int max_depth, int branching_factor){
        if (depth == max_depth){
                return;
        }
        for (int i = 0; i < branching_factor; i++){
                Node *child = new Node();
                node->children.push_back(child);
                child->parent = node;
                generateTree(child, depth + 1, max_depth, branching_factor);
        }
        return;
}

/*
    This function recursively prints the values of all the indexes of a given tree.
*/
void Node::printIndex(Node* root, int depth, vector<vector<double>> &tree){   
    if (depth >= (int)tree.size()) {
        tree.push_back({});
    }
    tree[depth].push_back(root->index);
    if (root->children.empty()){
        return;
    }
    for (auto &child : root->children){
        printIndex(child, depth+1, tree);
    }
}

/*
    This function recursively prints the values of all the leaf nodes of a given tree.
    If the node is a leaf node, it prints its value.
    If the node is not a leaf node, it calls itself on its children nodes.
*/
void Node::printOptions(Node* root){
        if (!root){
                return;
        }
        if (root->children.empty()){
                cout << root->value << " ";
                return;
        }
        for (auto &child : root->children){
                printOptions(child);
        }
}

/*
AlphaBetaPruning - implementation of the alpha-beta pruning algorithm to find the best value of a given tree.

Description: This function recursively implements the alpha-beta pruning algorithm to traverse the game tree and find the best move based on the given utility function. 
It takes a node, depth, max depth, alpha, beta, and maximizing player as input parameters and returns an integer value representing the best value found during the search.
 
Parameters:
      node - pointer to the current node being analyzed
      depth - current depth of the tree
      max_depth - maximum depth of the tree
      alpha - the current best value found for the maximizing player so far
      beta - the current best value found for the minimizing player so far
      maximizingPlayer - boolean indicating whether we are currently analyzing a maximizing player (true) or a minimizing player (false)
  
 Returns:
      The best value found for the given tree
 */

int Node::AlphaBetaPruning(Node *node, int depth, int max_depth, int alpha, int beta, bool maximizingPlayer){
        if (depth == max_depth || node->children.empty()){
                return node->value;
        }
        if (maximizingPlayer){
                int value = -INT_MAX;
                for (int i = 0; i < (int)node->children.size(); i++){
                        value = max(value, AlphaBetaPruning(node->children[i], depth + 1, max_depth, alpha, beta, false));
                        alpha = max(alpha, value);
                        if (beta <= alpha){
                                break;
                        }
                }
                return value;
        }
        else{
                int value = INT_MAX;
                for (Node *child : node->children){
                        value = min(value, AlphaBetaPruning(child, depth + 1, max_depth, alpha, beta, true));
                        beta = min(beta, value);
                        if (beta <= alpha){
                                break;
                        }
                }
                return value;
        }
}

/*
    Given a root Node and an index, this function recursively sets the index for each node in the tree.
    If the current node is a leaf node, it sets the index of the node to the current value of the index and increments it.
    Otherwise, the function recursively calls itself on each child of the node.
*/
void Node::resetIndex(Node* root, int& index, int& Nodeindex){
        if (root->children.size() == 0){
                root->index = index++;
        }
        else{
                root->index =  Nodeindex;
                Nodeindex--;
                for(auto child : root->children){
                        resetIndex(child,index, Nodeindex);
                }
        }
        return;
}

/* 
    This function takes in a root node, an index, and a value. 
    It recursively searches the tree for the node with the given index and updates its value to the given value. 
    If the node is not found, it outputs the index of the current node. 
*/
void Node::changeNode(Node* root, int index, int value){
        if (root->index == index) {
                root->value = value;
                return;
        }
        else if (root->children.empty()){
                return;
        }
        else{
                for (int i = 0; i < (int)root->children.size(); i++) {
                        changeNode(root->children[i], index, value);
                }
        }
}

/*
    This function attempts to delete a node with a specified index in the given root node and its children recursively. 
    If the node is found and deleted, it returns true. Otherwise, it returns false. 
    If a child node is deleted, it is replaced by NULL and erased from the parent's children vector. 
    The function takes a root node pointer and an index to search for as parameters.
*/
bool Node::delNode(Node* root, int index){
        if (root->children.size() == 0 && root->index != index){
                return false;
        }
        if (root->index == index){
                return true;
        }
        for (int i = 0; i < (int)root->children.size(); i++) {
            if(delNode(root->children[i], index)){
                root->children[i] = NULL;
                root->children.erase(root->children.begin()+i,root->children.begin()+i+1 );
                return false;
            }
        }
        return false;
}

bool Node::insertBranch(Node* root, int branchIndex, int depth, int max_depth, int branching_factor, int& total){
        if (root->index == branchIndex){
                return true;
        }
        else if (root->children.size() == 0){
                return false;
        }
        for (int i = 0; i < (int)root->children.size(); i++){
                if (insertBranch(root->children[i], branchIndex,depth+1,max_depth, branching_factor, total)){
                        Node* new_node = new Node();
                        new_node->parent = root;
                        new_node->leaf = false;
                        cout << "Left(0) or Right(1) of node: " << endl;
                        int position = 0;
                        cin >> position;
                        root->children.insert(root->children.begin()+i+position,new_node);
                        root->children[i+position]->generateTree(root->children[i+position], depth+1, max_depth, branching_factor);
                        vector<double>options;
                        int temp = pow(branching_factor,max_depth-depth-1);
                        options.resize(temp);
                        int Leafindex = 0;
                        int Nodeindex = 0;
                        cout << "Enter " << options.size() << " values for the tree:" << endl;
                        cout << "----------------------------------------------------" << endl;
                        for (int i = 0; i < (int)options.size(); i++){
                                cin >> value;
                                options[i] = value;
                        }
                        root->children[i+position]->setTree(root->children[i+position], options, Leafindex, Nodeindex);
                        cout << endl;
                        total += temp;
                        return false;
                }
        }
        return false;
}

/*
    A method to insert a new node at a specified index in a given tree.
    If the index is found in the tree, a new node is created with the given value and inserted at that index as a child of the corresponding node.
    If the index is not found in the tree, the function returns false.
    If the function inserts a new node, it returns true.
*/
bool Node::insertLeaf(Node* root, int Leafindex, int value) {
        if (root->index == Leafindex){
                return true;
        }
        else if (root->children.size() == 0){
                return false;
        }
        else{
                for (int i = 0; i < (int)root->children.size(); i++){
                         if(insertLeaf(root->children[i], Leafindex, value)){
                                Node* new_node = new Node();
                                new_node->value = value;
                                new_node->parent = root;
                                new_node->index = Leafindex;
                                new_node->leaf = true;
                                cout << "Left(0) or Right(1) of node: " << endl;
                                int position = 0;
                                cin >> position;
                                root->children.insert(root->children.begin()+i+position,new_node);
                                return false;
                         }
                }
        }
        return false;
}

/* 
    This function searches for a path from the root node to a node with a specified value.
    If the node with the specified value is found, the function returns true and the path is stored in the 'path' vector.
    If the node is not found, the function returns false.
    The function takes three parameters:
        a pointer to the root node of the tree
        an integer representing the value to be searched for
        a reference to a vector of integers to store the path
*/
bool Node::printPath(Node *root, int best_value, vector<int> &path){
        if (root->value == best_value) {
                path.push_back(root->index);
                return true;
        }
        if (root->children.size() != 0){
                for (int i = 0; i < (int)root->children.size(); i++) {
                        if (printPath(root->children[i], best_value, path)) {
                                path.push_back(i);
                                return true;
                        }
                }
        }
    return false;
}


