//#include <iostream>  // For input/output operations (cout, cin)
//#include <vector>    // For internal list operations and serialization
//#include <string>    // For string manipulation and output
//#include <algorithm> // For std::max, if not using custom max
//
//using namespace std;
//
//// Constants for traversal orders (as in your original code)
//#define IN_ORDER 0
//#define PRE_ORDER 1
//#define POST_ORDER 2
//
//// Node structure for the AVL Tree
//class Node {
//public:
//    int data;     // In this system, 'data' represents the Patient ID
//    Node* left;
//    Node* right;
//    int height;   // Height of the node (maximum depth of any leaf from this node)
//
//    // Constructor for a new node, taking a Patient ID
//    Node(int patientId)
//    {
//        data = patientId;
//        left = NULL;
//        right = NULL;
//        height = 1; // New node is initially a leaf, so its height is 1
//    }
//};
//
//// Main AVLTree class, specialized for managing Patient IDs
//class AVLTree {
//public:
//    Node* root; // Root of the AVL tree storing Patient IDs
//
//    // Constructor
//    AVLTree()
//    {
//        root = NULL; // Initialize the tree as empty
//    }
//
//    // Helper function for destructor to recursively delete nodes (memory management)
//    void DeleteSubtree(Node* node)
//    {
//        if (node == NULL)
//        {
//            return;
//        }
//        DeleteSubtree(node->left);  // Delete left subtree first
//        DeleteSubtree(node->right); // Then delete right subtree
//        delete node;                // Finally, delete the current node
//    }
//
//    // Destructor to clean up memory when the AVLTree object is destroyed
//    ~AVLTree() {
//        DeleteSubtree(root); // Call helper to delete all nodes
//    }
//
//    // --- Core AVL Tree Basic/Helper Functions (for internal tree management) ---
//
//    // Get height of a node (0 if null)
//    int getHeight(Node* node)
//    {
//        if (node == NULL)
//        {
//            return 0;
//        }
//        return node->height;
//    }
//
//    // Get balance factor of a node (Height of Left Subtree - Height of Right Subtree)
//    int getBalance(Node* node)
//    {
//        if (node == NULL)
//        {
//            return 0;
//        }
//        return getHeight(node->left) - getHeight(node->right);
//    }
//
//    // Simple max function (used for height calculations)
//    int max(int a, int b)
//    {
//        if (a > b)
//        {
//            return a;
//        }
//        else
//        {
//            return b;
//        }
//    }
//
//    // Right rotation for balancing (used in LL and LR cases)
//    Node* rightRotate(Node* y)
//    {
//        Node* x = y->left;
//        Node* T2 = x->right;
//
//        x->right = y;
//        y->left = T2;
//
//        // Update heights after rotation (bottom-up)
//        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
//        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//
//        return x; // x is the new root of the rotated subtree
//    }
//
//    // Left rotation for balancing (used in RR and RL cases)
//    Node* leftRotate(Node* x)
//    {
//        Node* y = x->right;
//        Node* T2 = y->left;
//
//        y->left = x;
//        x->right = T2;
//
//        // Update heights after rotation (bottom-up)
//        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
//
//        return y; // y is the new root of the rotated subtree
//    }
//
//    // Recursive insertion function (maintains AVL property)
//    Node* insert(Node* node, int patientId)
//    {
//        // 1. Perform standard BST insertion
//        if (node == NULL)
//        {
//            return new Node(patientId); // Create new node with patient ID
//        }
//
//        if (patientId < node->data) // Compare patient IDs
//        {
//            node->left = insert(node->left, patientId);
//        }
//        else if (patientId > node->data) // Compare patient IDs
//        {
//            node->right = insert(node->right, patientId);
//        }
//        else // Patient ID already exists (no duplicates allowed)
//        {
//            cout << "Patient ID " << patientId << " already exists." << endl;
//            return node;
//        }
//
//        // 2. Update height of the current node after insertion in subtree
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//
//        // 3. Get balance factor to check for imbalance
//        int balance = getBalance(node);
//
//        // 4. Perform rotations if necessary to restore AVL balance
//        // Left Left Case
//        if (balance > 1 && patientId < node->left->data)
//        {
//            return rightRotate(node);
//        }
//        // Right Right Case
//        if (balance < -1 && patientId > node->right->data)
//        {
//            return leftRotate(node);
//        }
//        // Left Right Case
//        if (balance > 1 && patientId > node->left->data)
//        {
//            node->left = leftRotate(node->left);
//            return rightRotate(node);
//        }
//        // Right Left Case
//        if (balance < -1 && patientId < node->right->data)
//        {
//            node->right = rightRotate(node->right);
//            return leftRotate(node);
//        }
//
//        return node; // Return the (potentially rebalanced) node
//    }
//
//    // Public function to add a new Patient ID
//    void AddPatient(int patientId)
//    {
//        root = insert(root, patientId);
//        cout << "Attempted to add Patient ID: " << patientId << endl;
//    }
//
//    // Helper to find the node with minimum value in a subtree (used in deletion)
//    Node* findMinNode(Node* node) {
//        Node* current = node;
//        while (current->left != NULL) {
//            current = current->left;
//        }
//        return current;
//    }
//
//    // Recursive deletion function (maintains AVL property)
//    Node* deleteNode(Node* node, int patientId) {
//        // 1. Perform standard BST deletion
//        if (node == NULL) {
//            return node; // Patient ID not found
//        }
//
//        if (patientId < node->data) {
//            node->left = deleteNode(node->left, patientId);
//        }
//        else if (patientId > node->data) {
//            node->right = deleteNode(node->right, patientId);
//        }
//        else { // Node with matching patientId found
//            // Case 1: Node has no child or only one child
//            if ((node->left == NULL) || (node->right == NULL)) {
//                Node* temp = node->left ? node->left : node->right;
//                if (temp == NULL) { // No child
//                    temp = node;
//                    node = NULL;
//                }
//                else { // One child
//                    *node = *temp; // Copy content of the child to this node
//                }
//                delete temp;
//            }
//            else { // Case 2: Node has two children
//                Node* temp = findMinNode(node->right); // Find in-order successor (min node in right subtree)
//                node->data = temp->data;                // Copy successor's patientId to this node
//                node->right = deleteNode(node->right, temp->data); // Delete the in-order successor
//            }
//        }
//
//        // If the tree had only one node or key not found, return
//        if (node == NULL) {
//            return node;
//        }
//
//        // 2. Update height of the current node after deletion in subtree
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//
//        // 3. Balance the tree (perform rotations if necessary)
//        int balance = getBalance(node);
//
//        // Left Left Case
//        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
//        // Left Right Case
//        if (balance > 1 && getBalance(node->left) < 0) {
//            node->left = leftRotate(node->left);
//            return rightRotate(node);
//        }
//        // Right Right Case
//        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
//        // Right Left Case
//        if (balance < -1 && getBalance(node->right) > 0) {
//            node->right = rightRotate(node->right);
//            return leftRotate(node);
//        }
//
//        return node;
//    }
//
//    // Public function to remove a Patient ID
//    void RemovePatient(int patientId) {
//        cout << "Attempted to remove Patient ID: " << patientId << endl;
//        root = deleteNode(root, patientId);
//    }
//
//    // Public function to check if a Patient ID exists
//    bool SearchPatient(int patientId) {
//        Node* current = root;
//        while (current != NULL) {
//            if (patientId == current->data) {
//                cout << "Patient ID " << patientId << " found." << endl;
//                return true;
//            }
//            else if (patientId < current->data) {
//                current = current->left;
//            }
//            else {
//                current = current->right;
//            }
//        }
//        cout << "Patient ID " << patientId << " not found." << endl;
//        return false;
//    }
//
//    // --- Your 15 Unique and Important Functions, Adapted for Patient IDs ---
//
//    // 1. IsBST()
//    // Checks if the structure maintains the BST property for Patient IDs
//    bool IsBSTree(Node* node, int minVal, int maxVal) {
//        if (node == NULL) return true;
//        if (node->data < minVal || node->data > maxVal) return false;
//        return IsBSTree(node->left, minVal, node->data - 1) &&
//            IsBSTree(node->right, node->data + 1, maxVal);
//    }
//    bool IsBST() {
//        bool result = IsBSTree(root, -2147483647, 2147483647); // Using large int min/max
//        cout << "Is the Patient ID tree a valid Binary Search Tree? " << (result ? "Yes" : "No") << endl;
//        return result;
//    }
//
//    // 2. GetRank(Node* root, int key) - Renamed for clarity in system context
//    // Finds the count of patient IDs less than or equal to a given ID
//    int CountNodes(Node* node) {
//        if (node == NULL) return 0;
//        return 1 + CountNodes(node->left) + CountNodes(node->right);
//    }
//    int GetPatientRank(Node* node, int patientId) {
//        if (node == NULL) return 0;
//        if (patientId < node->data) {
//            return GetPatientRank(node->left, patientId);
//        }
//        else if (patientId > node->data) {
//            return 1 + CountNodes(node->left) + GetPatientRank(node->right, patientId);
//        }
//        else { // patientId == node->data
//            return 1 + CountNodes(node->left);
//        }
//    }
//    void DisplayPatientRank(int patientId) {
//        int rank = GetPatientRank(root, patientId);
//        cout << "Number of patients with ID <= " << patientId << " (Rank): " << rank << endl;
//    }
//
//    // 3. Invert() - Less practical for Patient IDs, but demonstrates tree manipulation
//    // Flips the tree's left and right children
//    void InvertTree(Node* node) {
//        if (node == NULL) return;
//        Node* temp = node->left;
//        node->left = node->right;
//        node->right = temp;
//        InvertTree(node->left);
//        InvertTree(node->right);
//    }
//    void InvertPatientIDTree() {
//        InvertTree(root);
//        cout << "Patient ID tree structure has been inverted. Note: This breaks BST property." << endl;
//    }
//
//    // 4. LowestCommonAncestor(int a, int b) - Finding common ancestral ID in tree structure
//    // Finds the ID of the lowest common ancestor of two patient IDs
//    Node* FindLCA(Node* node, int id1, int id2) {
//        if (node == NULL) return NULL;
//        if (id1 < node->data && id2 < node->data) return FindLCA(node->left, id1, id2);
//        if (id1 > node->data && id2 > node->data) return FindLCA(node->right, id1, id2);
//        return node;
//    }
//    void DisplayLCA(int id1, int id2) {
//        Node* lca_node = FindLCA(root, id1, id2);
//        if (lca_node) {
//            cout << "Lowest Common Ancestor ID for " << id1 << " and " << id2 << " is: " << lca_node->data << endl;
//        }
//        else {
//            cout << "LCA not found (one or both IDs might be missing)." << endl;
//        }
//    }
//
//    // 5. LongestConsecutivePath() - Finding sequences of consecutive patient IDs
//    // Finds the longest sequence of consecutive Patient IDs
//    int getIncreasingPath(Node* node) {
//        if (node == NULL) return 0;
//        int currentPath = 1;
//        int leftPath = (node->left && node->left->data == node->data + 1) ? getIncreasingPath(node->left) : 0;
//        int rightPath = (node->right && node->right->data == node->data + 1) ? getIncreasingPath(node->right) : 0;
//        return currentPath + max(leftPath, rightPath);
//    }
//    int getDecreasingPath(Node* node) {
//        if (node == NULL) return 0;
//        int currentPath = 1;
//        int leftPath = (node->left && node->left->data == node->data - 1) ? getDecreasingPath(node->left) : 0;
//        int rightPath = (node->right && node->right->data == node->data - 1) ? getDecreasingPath(node->right) : 0;
//        return currentPath + max(leftPath, rightPath);
//    }
//    void LongestConsecutivePathUtil(Node* node, int& maxLen) {
//        if (node == NULL) return;
//        maxLen = max(maxLen, getIncreasingPath(node) + getDecreasingPath(node) - 1);
//        LongestConsecutivePathUtil(node->left, maxLen);
//        LongestConsecutivePathUtil(node->right, maxLen);
//    }
//    void FindLongestConsecutivePatientIDs() {
//        int maxLen = 0;
//        LongestConsecutivePathUtil(root, maxLen);
//        cout << "Longest consecutive sequence of Patient IDs: " << maxLen << endl;
//    }
//
//    // 6. GetCousins(int key) - Finding patient IDs at the same structural level
//    // Finds patient IDs at the same tree level but with different parents
//    int GetLevel(Node* node, int patientId, int level) {
//        if (node == NULL) return -1;
//        if (node->data == patientId) return level;
//        int left = GetLevel(node->left, patientId, level + 1);
//        if (left != -1) return left;
//        return GetLevel(node->right, patientId, level + 1);
//    }
//    Node* FindParent(Node* node, int patientId, Node* parent_node) {
//        if (node == NULL) return NULL;
//        if (node->data == patientId) return parent_node;
//        Node* left_parent = FindParent(node->left, patientId, node);
//        if (left_parent) return left_parent;
//        return FindParent(node->right, patientId, node);
//    }
//    Node* FindParentOfNode(int patientId) { // Public helper for PrintCousins' internal use
//        return FindParent(root, patientId, NULL);
//    }
//    void PrintCousins(Node* node, int targetPatientId, Node* parentOfTarget, int currentLevel, int targetLevel) {
//        if (node == NULL) return;
//        if (currentLevel == targetLevel) {
//            if (node->data != targetPatientId) { // Exclude the target node itself
//                Node* currentNodesParent = FindParent(root, node->data, NULL);
//                // Ensure current node's parent is different from target's parent
//                if (currentNodesParent != parentOfTarget) {
//                    cout << node->data << " ";
//                }
//            }
//        }
//        PrintCousins(node->left, targetPatientId, parentOfTarget, currentLevel + 1, targetLevel);
//        PrintCousins(node->right, targetPatientId, parentOfTarget, currentLevel + 1, targetLevel);
//    }
//    void DisplayCousins(int patientId) {
//        int targetLevel = GetLevel(root, patientId, 0);
//        Node* parent = FindParent(root, patientId, NULL);
//        if (targetLevel == -1) {
//            cout << "Patient ID " << patientId << " not found to find cousins." << endl;
//            return;
//        }
//        cout << "Cousin Patient IDs of " << patientId << ": ";
//        PrintCousins(root, patientId, parent, 0, targetLevel);
//        cout << endl;
//    }
//
//    // 7. LevelOrderTraversal(Node* root) - Viewing patient IDs level by level
//    // Prints Patient IDs level by level (Breadth-First Search)
//    void LevelOrderTraversal(Node* node) {
//        if (node == NULL) return;
//        // Using a simple array as a queue for demonstration, safer with std::queue for dynamic size
//        Node* queue[1000]; // Assuming max 1000 nodes for simplicity, use std::queue for production
//        int front = 0;
//        int rear = 0;
//
//        queue[rear++] = node;
//
//        while (front < rear) {
//            Node* current = queue[front++];
//            cout << current->data << " "; // Print patient ID
//
//            if (current->left) queue[rear++] = current->left;
//            if (current->right) queue[rear++] = current->right;
//        }
//    }
//    void DisplayAllPatientIDsByLevel() {
//        cout << "All Patient IDs (Level Order): ";
//        LevelOrderTraversal(root);
//        cout << endl;
//    }
//
//    // 8. IsFullTree(Node* root) - Structural check of the patient ID tree
//    // Checks if the tree structure is a full binary tree (every node has 0 or 2 children)
//    bool IsFullTree(Node* node) {
//        if (node == NULL) return true;
//        if (node->left == NULL && node->right == NULL) return true; // Leaf node
//        if (node->left && node->right) { // Node with two children
//            return IsFullTree(node->left) && IsFullTree(node->right);
//        }
//        return false; // Node with only one child
//    }
//    void CheckIfPatientIDTreeIsFull() {
//        cout << "Is the Patient ID tree a Full Binary Tree? " << (IsFullTree(root) ? "Yes" : "No") << endl;
//    }
//
//    // 9. Merge(AVLTree& otherTree) - Combining patient ID lists from different sources
//    // Merges patient IDs from another AVL tree into this one
//    void StoreInOrder(Node* node, vector<int>& arr) {
//        if (node == NULL) return;
//        StoreInOrder(node->left, arr);
//        arr.push_back(node->data);
//        StoreInOrder(node->right, arr);
//    }
//    void MergeVectors(const vector<int>& arr1, const vector<int>& arr2, vector<int>& merged) {
//        merged.clear();
//        merged.reserve(arr1.size() + arr2.size());
//        int i = 0, j = 0;
//        while (i < arr1.size() && j < arr2.size()) {
//            if (arr1[i] < arr2[j]) merged.push_back(arr1[i++]);
//            else if (arr2[j] < arr1[i]) merged.push_back(arr2[j++]);
//            else { // Handle duplicates (if IDs are truly unique, this branch means one ID existed in both)
//                merged.push_back(arr1[i++]);
//                j++;
//            }
//        }
//        while (i < arr1.size()) merged.push_back(arr1[i++]);
//        while (j < arr2.size()) merged.push_back(arr2[j++]);
//    }
//    Node* SortedArrayToAVL(const vector<int>& arr, int start, int end) {
//        if (start > end) return NULL;
//        int mid = start + (end - start) / 2;
//        Node* newNode = new Node(arr[mid]); // Create node with Patient ID
//        newNode->left = SortedArrayToAVL(arr, start, mid - 1);
//        newNode->right = SortedArrayToAVL(arr, mid + 1, end);
//        newNode->height = 1 + max(getHeight(newNode->left), getHeight(newNode->right));
//        return newNode;
//    }
//    void MergePatientIDSystems(AVLTree& otherTree) {
//        vector<int> arr1_vec, arr2_vec, merged_vec;
//        StoreInOrder(this->root, arr1_vec);
//        StoreInOrder(otherTree.root, arr2_vec);
//        MergeVectors(arr1_vec, arr2_vec, merged_vec);
//        DeleteSubtree(this->root); // Clear current tree
//        this->root = SortedArrayToAVL(merged_vec, 0, merged_vec.size() - 1); // Build new tree
//        cout << "Merged Patient IDs from another system." << endl;
//    }
//
//    // 10. DeleteNodesGreaterThan(int value) - Archiving/filtering patient IDs
//    // Deletes all patient IDs greater than a specified threshold ID
//    Node* DeleteGreaterThanHelper(Node* node, int thresholdId) {
//        if (node == NULL) return NULL;
//
//        node->left = DeleteGreaterThanHelper(node->left, thresholdId);
//        // Important: Only process right child if the current node's data is NOT greater than threshold
//        // If node->data > threshold, its entire right subtree will also be > threshold
//        if (node->data <= thresholdId) {
//            node->right = DeleteGreaterThanHelper(node->right, thresholdId);
//        }
//
//        if (node->data > thresholdId) {
//            // This node and everything in its right subtree should be deleted.
//            // We return its left child to its parent, essentially "cutting off" this branch.
//            Node* temp = node->left;
//            delete node;
//            return temp;
//        }
//        else {
//            // This node remains. Re-calculate height and balance if children were modified.
//            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//            int balance = getBalance(node);
//
//            // Rebalance after potential deletions in subtrees
//            if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
//            if (balance > 1 && getBalance(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
//            if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
//            if (balance < -1 && getBalance(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
//            return node;
//        }
//    }
//    void ArchivePatientIDsGreaterThan(int thresholdId) {
//        cout << "Archiving Patient IDs greater than: " << thresholdId << endl;
//        root = DeleteGreaterThanHelper(root, thresholdId);
//    }
//
//    // 11. ContainsIdenticalSubtrees() - Detecting duplicate ID patterns (less common for random IDs)
//    // Checks if the patient ID tree contains identical structural subtrees (e.g., a repeated pattern of assigned IDs)
//    string serializeSubtree(Node* node) {
//        if (node == NULL) return "#";
//        string s = to_string(node->data);
//        s += serializeSubtree(node->left);
//        s += serializeSubtree(node->right);
//        return s;
//    }
//    bool CheckIdenticalSubtrees(Node* node, vector<string>& subtrees) {
//        if (node == NULL) return false;
//        if (CheckIdenticalSubtrees(node->left, subtrees)) return true;
//        if (CheckIdenticalSubtrees(node->right, subtrees)) return true;
//
//        string currentSubtreeString = serializeSubtree(node);
//
//        for (int i = 0; i < subtrees.size(); i++) {
//            if (subtrees[i] == currentSubtreeString) {
//                return true; // Found a duplicate subtree string
//            }
//        }
//        subtrees.push_back(currentSubtreeString); // Add to list for future comparison
//        return false;
//    }
//    void CheckForDuplicateIDPatterns() {
//        vector<string> subtrees;
//        cout << "Does the Patient ID tree contain identical subtree patterns? " << (CheckIdenticalSubtrees(root, subtrees) ? "Yes" : "No") << endl;
//    }
//
//    // 12. PruneTree(int maxDepth) - Limiting tree depth for specific access
//    // Deletes patient IDs beyond a specified depth in the tree structure
//    Node* PruneTreeHelper(Node* node, int currentDepth, int maxDepth) {
//        if (node == NULL) return NULL;
//        if (currentDepth == maxDepth) {
//            DeleteSubtree(node->left); node->left = NULL; // Delete left subtree
//            DeleteSubtree(node->right); node->right = NULL; // Delete right subtree
//            node->height = 1; // It's now a leaf
//            return node;
//        }
//        node->left = PruneTreeHelper(node->left, currentDepth + 1, maxDepth);
//        node->right = PruneTreeHelper(node->right, currentDepth + 1, maxDepth);
//
//        // Re-calculate height and balance after pruning children
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//        int balance = getBalance(node);
//
//        // Rebalance after potential pruning
//        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
//        if (balance > 1 && getBalance(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
//        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
//        if (balance < -1 && getBalance(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
//        return node;
//    }
//    void PrunePatientIDTreeByDepth(int maxDepth) {
//        cout << "Pruning Patient ID tree to max depth: " << maxDepth << endl;
//        root = PruneTreeHelper(root, 0, maxDepth);
//    }
//
//    // 13. FindNthInTraversalOrder(int n, int orderType) - Finding patient IDs by order
//    // Finds the Nth patient ID when traversed in a specific order (e.g., sorted order via IN_ORDER)
//    void FindNthInOrder(Node* node, int n, int& count, int& result) {
//        if (node == NULL || count >= n) return;
//        FindNthInOrder(node->left, n, count, result);
//        if (count < n) {
//            count++;
//            if (count == n) { result = node->data; return; }
//        }
//        FindNthInOrder(node->right, n, count, result);
//    }
//    void FindNthPreOrder(Node* node, int n, int& count, int& result) {
//        if (node == NULL || count >= n) return;
//        if (count < n) {
//            count++;
//            if (count == n) { result = node->data; return; }
//        }
//        FindNthPreOrder(node->left, n, count, result);
//        FindNthPreOrder(node->right, n, count, result);
//    }
//    void FindNthPostOrder(Node* node, int n, int& count, int& result) {
//        if (node == NULL || count >= n) return;
//        FindNthPostOrder(node->left, n, count, result);
//        FindNthPostOrder(node->right, n, count, result);
//        if (count < n) {
//            count++;
//            if (count == n) { result = node->data; return; }
//        }
//    }
//    void DisplayNthPatientID(int n, int orderType) {
//        int count = 0;
//        int result = -1;
//        string orderName;
//
//        if (orderType == IN_ORDER) { FindNthInOrder(root, n, count, result); orderName = "In-Order"; }
//        else if (orderType == PRE_ORDER) { FindNthPreOrder(root, n, count, result); orderName = "Pre-Order"; }
//        else if (orderType == POST_ORDER) { FindNthPostOrder(root, n, count, result); orderName = "Post-Order"; }
//
//        if (result != -1) {
//            cout << n << "th Patient ID in " << orderName << " traversal: " << result << endl;
//        }
//        else {
//            cout << "Could not find " << n << "th Patient ID in " << orderName << " traversal (tree too small or invalid n)." << endl;
//        }
//    }
//
//    // 14. FindParentOfNode(int key) - Finding the parent ID in the tree hierarchy
//    // Finds the parent ID of a given patient ID in the tree structure
//    Node* FindParentHelper(Node* current, Node* parent, int patientId) {
//        if (current == NULL) return NULL;
//        if (current->data == patientId) return parent; // Found the node, return its parent
//        if (patientId < current->data) {
//            return FindParentHelper(current->left, current, patientId);
//        }
//        else {
//            return FindParentHelper(current->right, current, patientId);
//        }
//    }
//    void DisplayParentOfPatientID(int patientId) {
//        Node* parent = FindParentHelper(root, NULL, patientId); // NULL for root's parent
//        if (parent) {
//            cout << "Parent ID of Patient ID " << patientId << ": " << parent->data << endl;
//        }
//        else if (SearchPatient(patientId)) { // Check if it's the root itself
//            cout << "Patient ID " << patientId << " is the root of the tree (no parent)." << endl;
//        }
//        else {
//            cout << "Patient ID " << patientId << " not found to determine parent." << endl;
//        }
//    }
//
//    // 15. GetTreeSkewType() - Analyzing structural balance beyond AVL's strict height balance
//    // Determines if the patient ID tree is globally left-skewed, right-skewed, or balanced by node count
//    string GetTreeSkewType() {
//        if (root == NULL) return "BALANCED";
//
//        int leftCount = CountNodes(root->left);
//        int rightCount = CountNodes(root->right);
//
//        int diff = (leftCount > rightCount) ? (leftCount - rightCount) : (rightCount - leftCount);
//        int total = leftCount + rightCount;
//
//        if (total == 0) return "BALANCED"; // Single root node or empty tree after root.
//
//        // If difference is more than 20% of total nodes, consider it skewed
//        if (static_cast<double>(diff) / total > 0.20) {
//            if (leftCount > rightCount) return "LEFT_SKEWED (by node count)";
//            else return "RIGHT_SKEWED (by node count)";
//        }
//        return "BALANCED (by node count)";
//    }
//    void DisplayTreeSkew() {
//        cout << "Patient ID Tree Skew Type: " << GetTreeSkewType() << endl;
//    }
//};
//
//// Main function to demonstrate the Patient Record ID Management System
//int main()
//{
//    AVLTree patientIDSystem; // Our AVL tree to manage Patient IDs
//
//    cout << "--- Patient Record ID Management System ---" << endl;
//
//    // Add some initial patient IDs
//    patientIDSystem.AddPatient(100);
//    patientIDSystem.AddPatient(50);
//    patientIDSystem.AddPatient(150);
//    patientIDSystem.AddPatient(25);
//    patientIDSystem.AddPatient(75);
//    patientIDSystem.AddPatient(125);
//    patientIDSystem.AddPatient(175);
//    patientIDSystem.AddPatient(60);
//    patientIDSystem.AddPatient(90);
//    patientIDSystem.AddPatient(30); // Add a patient ID that creates a balance scenario
//
//    cout << "\n--- Initial Patient ID Tree ---" << endl;
//    patientIDSystem.DisplayAllPatientIDsByLevel(); // Level-order traversal of IDs
//    patientIDSystem.IsBST(); // Check if the patient ID tree is a valid BST
//
//    // Demonstrate various functions in the context of patient IDs
//    cout << "\n--- Patient ID Searches and Rankings ---" << endl;
//    patientIDSystem.SearchPatient(75); // Search for an existing patient ID
//    patientIDSystem.SearchPatient(99); // Search for a non-existing patient ID
//    patientIDSystem.DisplayPatientRank(60); // Rank of a specific patient ID
//    patientIDSystem.DisplayPatientRank(110); // Rank for an ID not necessarily present
//
//    cout << "\n--- Tree Structural Analysis ---" << endl;
//    patientIDSystem.DisplayLCA(60, 90); // Find LCA for two patient IDs
//    patientIDSystem.DisplayLCA(25, 175); // Find LCA for IDs in different subtrees
//    patientIDSystem.FindLongestConsecutivePatientIDs(); // Check for consecutive ID patterns
//    patientIDSystem.DisplayCousins(75); // Find cousins of a patient ID
//    patientIDSystem.CheckIfPatientIDTreeIsFull(); // Check if the ID tree structure is full
//    patientIDSystem.DisplayTreeSkew(); // Check global skew of the ID tree
//
//    // Demonstrate modifications to the patient ID tree
//    cout << "\n--- Patient ID Tree Modifications ---" << endl;
//    patientIDSystem.RemovePatient(150); // Remove an existing patient ID
//    patientIDSystem.DisplayAllPatientIDsByLevel();
//
//    // Example of merging with another clinic's patient IDs
//    AVLTree otherClinicIDs;
//    otherClinicIDs.AddPatient(200);
//    otherClinicIDs.AddPatient(10);
//    otherClinicIDs.AddPatient(160);
//    cout << "\n--- Merging Patient IDs from Another Clinic ---" << endl;
//    patientIDSystem.MergePatientIDSystems(otherClinicIDs);
//    patientIDSystem.DisplayAllPatientIDsByLevel();
//
//    // Demonstrate archiving older patient IDs (deletion of IDs > threshold)
//    cout << "\n--- Archiving Patient IDs > 100 ---" << endl;
//    patientIDSystem.ArchivePatientIDsGreaterThan(100);
//    patientIDSystem.DisplayAllPatientIDsByLevel();
//
//    // Check for duplicate ID patterns again after modifications
//    cout << "\n--- Re-checking for Duplicate ID Patterns ---" << endl;
//    patientIDSystem.CheckForDuplicateIDPatterns(); // Less likely with random IDs unless specifically inserted
//
//    // Demonstrate pruning the tree for quick access/simplified view
//    cout << "\n--- Pruning Patient ID Tree to Depth 2 ---" << endl;
//    patientIDSystem.PrunePatientIDTreeByDepth(2);
//    patientIDSystem.DisplayAllPatientIDsByLevel();
//
//
//    // Demonstrate finding Nth Patient ID in various orders
//    cout << "\n--- Finding Nth Patient IDs ---" << endl;
//    patientIDSystem.DisplayNthPatientID(3, IN_ORDER); // 3rd smallest patient ID
//    patientIDSystem.DisplayNthPatientID(2, PRE_ORDER); // 2nd ID in pre-order traversal
//    patientIDSystem.DisplayNthPatientID(1, POST_ORDER); // 1st ID in post-order traversal
//
//    patientIDSystem.DisplayParentOfPatientID(50); // Find parent of an ID
//    patientIDSystem.DisplayParentOfPatientID(10); // Find parent of a leaf ID
//    patientIDSystem.DisplayParentOfPatientID(200); // Try to find parent of a non-existent ID
//    patientIDSystem.DisplayParentOfPatientID(patientIDSystem.root->data); // Check parent of root
//
//
//    cout << "\n--- System Demonstration Complete ---" << endl;
//    return 0;
//}
