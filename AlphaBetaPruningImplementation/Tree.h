#include <iostream>
#include <vector>

using namespace std;

#ifndef TREE_H
#define TREE_H

class Node{
    
public:
    Node();
    void recount(Node *root, int &Nodeindex, int &Leafindex);
    void setTree(Node *root, vector<double> options, int& Nodeindex,int &Leafindex);
    void generateTree(Node *node, int depth, int max_depth, int branching_factor);
    int AlphaBetaPruning(Node *root, int depth, int max_depth, int alpha, int beta, bool maximizingPlayer);
    void printIndex(Node *root, int depth, vector<vector<double>> &tree);
    void printOptions(Node *root);    
    void changeNode(Node *root, int index, int value);
    void resetIndex(Node *root, int &index, int& Nodeindex);
    bool delNode(Node *root, int index);
    bool insertBranch(Node* root, int branchIndex, int depth, int max_depth, int branching_factor, int& total);
    bool insertLeaf(Node *root, int Leafindex, int value);
    bool printPath(Node *root, int best_value, vector<int> &path);

private:
    int index = -1;
    double value;
    Node *parent;
    bool leaf;
    vector<Node *> children;
};

#endif
