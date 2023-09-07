#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <bits/stdc++.h>
#include "Tree.h"

using namespace std;

int main(){
        // initializing all variable to be used by the simulation
        int nodeType;
        string command;
        int temp = 0, Leafindex = 0, Nodeindex = 0,Tempindex = 0, total = 0, branching_factor = 0, max_depth = 0, depth = 0;
        bool maximizingPlayer = true, exists = false, set = false, defined = false;
        double alpha = INT_MIN, beta = INT_MAX, best_value = INT_MIN, value = 0;
        vector<int> path;
        vector<double> options;
        vector<vector<double>> tree;
        Node *root = new Node();

        // Anncouncing the options that the user can input
        cout << "Enter which command to run (q to quit)" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Option 1: 'Define' Tree" << endl;
        cout << "Option 2: 'Generate' Tree" << endl;
        cout << "Option 3: 'Set' Tree" << endl;
        cout << "Option 4: 'Run' the algorithm" << endl;
        cout << "Option 5: 'Delete' Tree" << endl;
        cout << "Option 6: 'Print' Tree" << endl;
        cout << "Option 7: 'Change' Node" << endl;
        cout << "Option 8: 'Del' Node" << endl;
        cout << "Option 9: 'Insert' Node" << endl;
        cout << "Option 10: 'PrintPath' Tree" << endl;

        // Running the simulation
        while (command != "q"){
                cout << endl;
                getline(cin, command);
                if (command == "q"){
                        cout << "Exiting Simulation..." << endl;
                }
                // Option 1: Define Tree
                else if (command == "1" || command == "Define"){
                        if (defined == true){
                                cout << "Tree has already been defined" << endl;;
                        }
                        else{
                        // Prompt user to enter the branching factor
                        cout << "Enter the branching factor (a positive integer): ";
                        cin >> branching_factor;

                        // Validate the input for the branching factor
                        if (branching_factor <= 0){
                                cout << "Invalid branching factor. Please enter a positive integer: ";
                                cin >> branching_factor;
                        }

                        // Prompt user to enter the maximum depth of the tree
                        cout << "Enter the maximum depth of the tree (a non-negative integer): ";
                        cin >> max_depth;

                        // Validate the input for the maximum depth
                        if (max_depth < 0){
                                cout << "Invalid maximum depth. Please enter a non-negative integer: ";
                                cin >> max_depth;
                        }

                        // Calculate the total number of nodes in the tree based on the branching factor and maximum depth
                        total = 1;
                        for (int i = 0; i < max_depth; i++){
                                total *= branching_factor;
                        }

                        // Print the details of the tree that the user has defined
                        cout << endl;
                        cout << "You have defined a tree with the following details:" << endl;
                        cout << "Branching factor: " << branching_factor << endl;
                        cout << "Maximum depth: " << max_depth << endl;
                        cout << "Total nodes: " << total << endl;
                        defined = true;
                        }
                        cin.ignore();
                }

                // Option 2: Generate Tree: Generates a new tree based on the defined parameters.
                else if (command == "2" || command == "Generate"){
                        if (defined == false){
                                cout << "Max depth and branching factor must be defined first.";
                                cout << endl;
                        }
                        else if (exists == true){
                                cout << "Tree already exists." << endl;
                        }
                        else{
                                // creates an empty tree that is based off the user's specification
                                cout << "Generating the tree..." << endl;
                                root->generateTree(root, depth, max_depth, branching_factor);
                                exists = true;
                        }
                }
                // Check if user input is for Option 3: Set Tree
                else if (command == "3" || command == "Set"){
                        // If the tree has not been generated, prompt the user to generate the tree first
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == true){
                                cout << "Tree has already been set" << endl;
                        }
                        else{
                                // Resize the options vector to match the total number of nodes in the tree
                                options.resize(total);

                                // Prompt the user to enter values for the tree
                                cout << "Enter " << options.size() << " values for the tree:" << endl;
                                cout << "----------------------------------------------------" << endl;

                                // Loop through each node in the tree and set its value
                                for (int i = 0; i < (int)options.size(); i++){
                                        cin >> value;
                                        options[i] = value;
                                }
                                cout << endl;

                                // Display a message indicating that the tree is being set
                                cout << "Setting the tree...";

                                // Set the values of the leaf nodes in the tree
                                root->setTree(root, options, Leafindex, Nodeindex);
                                set = true;

                                // Ignore any additional input from the user
                                cout << endl;
                                cin.ignore();
                        }
                }

                // Check if user input is for Option 4: Run
                else if (command == "4" || command == "Run")
                {
                        // If the tree has not been set, prompt the user to set the tree first
                        if (exists == false){
                                cout << "Please generate the tree first";
                        }
                        else if (set == false){
                                cout << "Tree has not been set";
                        }
                        else{
                                // Run the alpha-beta pruning algorithm on the current tree
                                cout << "Running the algorithm... " << endl;
                                cout << "------------------------" << endl;

                                // Call the AlphaBetaPruning function to find the best value in the tree
                                best_value = root->AlphaBetaPruning(root, depth, max_depth, alpha, beta, maximizingPlayer);

                                // Output the best value found
                                cout << "The best value found is: " << best_value;
                        }
                        cout << endl;
                }

                // Check if user input is for Option 5: Delete
                else if (command == "5" || command == "Delete"){
                        // If the tree has already been deleted, output a message to indicate that it does not exist
                        if (exists == false){
                                cout << "Please generate the tree first";
                        }
                        else if (set == false){
                                cout << "Tree has not been set";
                        }
                        else{
                                // Delete the current tree and create a new empty root node
                                delete root;
                                root = new Node();

                                // Reset variables used for alpha-beta pruning
                                beta = INT_MAX;
                                alpha = INT_MIN;
                                best_value = 0;

                                // Reset other variables used in the program
                                total = 0;
                                value = 0;
                                Leafindex = 0;
                                Nodeindex = 0;
                                options.clear();
                                tree.clear();
                                temp = 0;
                                depth = 0;
                                maximizingPlayer = true;
                                exists = false;
                                set = false;
                                defined = false;

                                // Output a message to indicate that the tree has been deleted
                                cout << "Tree deleted.";
                        }
                        cout << endl;
                }

                // Check if user input is for Option 6: Print Tree
                else if (command == "6" || command == "Print"){
                        // If the tree has not been defined, output an error message
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == false){
                                cout << "Tree has not been set" << endl;
                        }
                        else{
                                temp = 0;
                                cout << "Would you like to print the indexes (1) or the options (2):" << endl;
                                cin >> temp;
                                if (temp == 1){
                                        //Print the tree indexes generated earlier
                                        temp = 0;
                                        cout << "Printing the tree..." << endl;
                                        root->printIndex(root, temp, tree);
                                        for (int i = 0; i < (int)tree.size(); i++){
                                                cout << "Level " << i << ": ";
                                                for (int j = 0; j < (int)tree[i].size(); j++){
                                                        cout << tree[i][j] << " ";
                                                }
                                                cout<< endl;
                                        }
                                        tree.clear();
                                }
                                else{

                                        // Print the options that were inserted earlier
                                        cout << "Printing the options..." << endl;
                                        root->printOptions(root);
                                        cout << endl;
                                }
                                cin.ignore();
                        }
                }
                // Check if user input is for Option 7: Change Node
                else if (command == "7" || command == "Change"){
                        // If the tree has not been defined, output an error message
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == false){
                                cout << "Tree has not been set" << endl;
                        }
                        else{
                                // User picks an index to be able to change a node at that index.
                                cout << "Enter the index to add a node at (between 0 and " << total - 1 << "): ";
                                cin >> temp;
                                if (temp < 0 || temp >= total){
                                        cout << "Error: Index is out of range." << endl;
                                }
                                else{
                                        Leafindex = temp;
                                        cout << "Enter the value of the node: ";
                                        cin >> value;
                                        root->changeNode(root, Leafindex, value);
                                        cout << "Node changed successfully." << endl;
                                }
                                cin.ignore();
                        }
                }

                // This option allows the user to delete a node at a specified index from the tree.
                else if (command == "8" || command == "Del Node"){
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == false){
                                cout << "Tree has not been set" << endl;
                        }
                        else{
                                // Prompt the user to input the index of the node to be deleted.
                                Leafindex = 0;
                                Nodeindex = 0;
                                root->recount(root, Nodeindex, Leafindex);
                                cout << "Enter the index to delete a node at (between " << Nodeindex << " and " << Leafindex << "): ";
                                cin >> temp;
                                if (temp < Nodeindex || temp > Leafindex){ // Check if the input index is valid.
                                        cout << "Error: Index is out of range." << endl;
                                }
                                else{
                                        Leafindex = temp;
                                        root->delNode(root, Leafindex); // Delete the node at the specified index.
                                        cout << "Node deleted successfully." << endl;
                                        Leafindex = 0;
                                        Nodeindex = -1;
                                        root->resetIndex(root, Leafindex, Nodeindex);
                                }
                                cin.ignore();
                        }
                }
                // Option 9: Insert Node: Inserts a new node at the specified index with the specified value, shifting existing nodes to make room if necessary.
                else if (command == "9" || command == "Insert Node") {
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == false){
                                cout << "Tree has not been set" << endl;
                        } else {
                                Leafindex = 0;
                                Nodeindex = 0;
                                root->recount(root, Nodeindex, Leafindex);
                                // Prompt user to choose node type
                                cout << "What type of node do you want to insert? Leaf(1) or Branch(2): ";
                                cin >> nodeType;
                                cin.ignore();
                                if (nodeType == 1) {
                                        // Prompt user to enter index to insert new leaf node
                                        cout << "Enter the index to insert a leaf node at (between 0 and " << Leafindex << "): ";
                                        cin >> Tempindex;
                                        if (Tempindex < 0 || Tempindex > Leafindex) {
                                                // Check if index is within range
                                                cout << "Error: Index is out of range." << endl;
                                        } else {
                                                // Prompt user to enter value of the new leaf node
                                                cout << "Enter the value of the leaf node: ";
                                                cin >> temp;
                                                // Insert the new leaf node
                                                root->insertLeaf(root, Tempindex, temp);
                                                // Reset the index for the nodes
                                                Leafindex = 0;
                                                Nodeindex = -1;
                                                root->resetIndex(root, Leafindex, Nodeindex);
                                                cout << "Leaf node inserted successfully." << endl;
                                                // Increase the total number of nodes in the tree
                                                total++;
                                        }
                                } else if (nodeType == 2) {
                                        // Prompt user to enter index to insert new branch node
                                        cout << "Enter the index to insert a branch node at (between -2 and " <<  Nodeindex << ")"<< endl;
                                        int branchIndex;
                                        cin >> branchIndex;
                                        if (branchIndex < Nodeindex || branchIndex >= -1) {
                                                // Check if index is within range
                                                cout << "Error: Index is out of range." << endl;
                                        } else {
                                                depth = 0;
                                                // Insert the new branch node
                                                root->insertBranch(root, branchIndex, depth, max_depth, branching_factor, total);
                                                // Reset the index for the nodes
                                                Leafindex = 0;
                                                Nodeindex = -1;
                                                root->resetIndex(root, Leafindex, Nodeindex);
                                                cout << "Branch node inserted successfully." << endl;
                                        }
                                } else{
                                        // Invalid node type entered
                                        cout << "Error: Invalid node type entered." << endl;
                                }
                                cin.ignore();
                        }
                }
                // Option 10: PrintPath: Prints the path from the root node to the node with the best value found during alpha-beta pruning.
                else if (command == "10" || command == "PrintPath"){
                        if (exists == false){
                                cout << "Please generate the tree first" << endl;
                        }
                        else if (set == false){
                                cout << "Tree has not been set" << endl;
                        }
                        else if (best_value == INT_MIN){
                                // Checks if alpha-beta pruning algorithm has been run before
                                cout << "Error: The algorithm has not been run yet." << endl;
                        }
                        else{
                                // Prints the path so the user can see what path to take
                                cout << "Printing the path to the best value..." << endl;

                                // Calls function to find the path and stores it in a vector
                                root->printPath(root, best_value, path);

                                // Reverses the path vector since it is from bottom to top
                                reverse(path.begin(), path.end());

                                // Prints the path in a user-friendly format
                                cout << "Best Path is: Current => ";
                                for (int i = 0; i < (int)path.size() - 1; i++){
                                        cout << "Option " << path[i] + 1 << " => ";
                                }
                                cout << " End." << endl;
                                path.clear();
                        }
                }
                else{
                        cout << "Invalid Command: Please enter a valid command" << endl;
                }
        }
        delete root;
        return 0;
}


