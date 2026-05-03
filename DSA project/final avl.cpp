#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define IN_ORDER 0
#define PRE_ORDER 1
#define POST_ORDER 2

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int patientId)
    {
        data = patientId;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree()
    {
        root = NULL;
    }

    void DeleteSubtree(Node* node)
    {
        if (node == NULL)
        {
            return;
        }
        DeleteSubtree(node->left);
        DeleteSubtree(node->right);
        delete node;
    }

    ~AVLTree() {
        DeleteSubtree(root);
    }

    int getHeight(Node* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int patientId)
    {
        if (node == NULL)
        {
            return new Node(patientId);
        }

        if (patientId < node->data)
        {
            node->left = insert(node->left, patientId);
        }
        else if (patientId > node->data)
        {
            node->right = insert(node->right, patientId);
        }
        else
        {
            cout << "Patient ID " << patientId << " already exists." << endl;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && patientId < node->left->data)
        {
            return rightRotate(node);
        }
        if (balance < -1 && patientId > node->right->data)
        {
            return leftRotate(node);
        }
        if (balance > 1 && patientId > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && patientId < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void AddPatient(int patientId)
    {
        root = insert(root, patientId);
        cout << "Attempted to add Patient ID: " << patientId << endl;
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int patientId) {
        if (node == NULL) {
            return node;
        }

        if (patientId < node->data) {
            node->left = deleteNode(node->left, patientId);
        }
        else if (patientId > node->data) {
            node->right = deleteNode(node->right, patientId);
        }
        else {
            if ((node->left == NULL) || (node->right == NULL)) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = findMinNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == NULL) {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
        return node;
    }

    void RemovePatient(int patientId) {
        cout << "Attempted to remove Patient ID: " << patientId << endl;
        root = deleteNode(root, patientId);
    }

    bool SearchPatient(int patientId) {
        Node* current = root;
        while (current != NULL) {
            if (patientId == current->data) {
                cout << "Patient ID " << patientId << " found." << endl;
                return true;
            }
            else if (patientId < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        cout << "Patient ID " << patientId << " not found." << endl;
        return false;
    }

    // 1. IsBST()
    bool IsBSTree(Node* node, int minVal, int maxVal) {
        if (node == NULL) return true;
        if (node->data < minVal || node->data > maxVal) return false;
        return IsBSTree(node->left, minVal, node->data - 1) &&
            IsBSTree(node->right, node->data + 1, maxVal);
    }
    bool IsBST() {
        bool result = IsBSTree(root, -2147483647, 2147483647);
        cout << "Is the Patient ID tree a valid Binary Search Tree? " << (result ? "Yes" : "No") << endl;
        return result;
    }

    // 2. GetRank(Node* root, int key)
    int CountNodes(Node* node) {
        if (node == NULL) return 0;
        return 1 + CountNodes(node->left) + CountNodes(node->right);
    }
    int GetPatientRank(Node* node, int patientId) {
        if (node == NULL) return 0;
        if (patientId < node->data) {
            return GetPatientRank(node->left, patientId);
        }
        else if (patientId > node->data) {
            int leftCount = CountNodes(node->left);
            return 1 + leftCount + GetPatientRank(node->right, patientId);
        }
        else {
            return 1 + CountNodes(node->left);
        }
    }
    void DisplayPatientRank(int patientId) {
        int rank = GetPatientRank(root, patientId);
        cout << "Number of patients with ID <= " << patientId << " (Rank): " << rank << endl;
    }

    // 3. Invert()
    void InvertTree(Node* node) {
        if (node == NULL) return;
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        InvertTree(node->left);
        InvertTree(node->right);
    }
    void InvertPatientIDTree() {
        InvertTree(root);
        cout << "Patient ID tree structure has been inverted. Note: This breaks BST property." << endl;
    }

    // 4. LowestCommonAncestor(int a, int b)
    Node* FindLCA(Node* node, int id1, int id2) {
        if (node == NULL) return NULL;
        if (id1 < node->data && id2 < node->data) return FindLCA(node->left, id1, id2);
        if (id1 > node->data && id2 > node->data) return FindLCA(node->right, id1, id2);
        return node;
    }
    void DisplayLCA(int id1, int id2) {
        Node* lca_node = FindLCA(root, id1, id2);
        if (lca_node) {
            cout << "Lowest Common Ancestor ID for " << id1 << " and " << id2 << " is: " << lca_node->data << endl;
        }
        else {
            cout << "LCA not found (one or both IDs might be missing)." << endl;
        }
    }

    // 5. LongestConsecutivePath()
    int getIncreasingPath(Node* node) {
        if (node == NULL) return 0;
        int currentPath = 1;
        int leftPath = (node->left && node->left->data == node->data + 1) ? getIncreasingPath(node->left) : 0;
        int rightPath = (node->right && node->right->data == node->data + 1) ? getIncreasingPath(node->right) : 0;
        return currentPath + max(leftPath, rightPath);
    }
    int getDecreasingPath(Node* node) {
        if (node == NULL) return 0;
        int currentPath = 1;
        int leftPath = (node->left && node->left->data == node->data - 1) ? getDecreasingPath(node->left) : 0;
        int rightPath = (node->right && node->right->data == node->data - 1) ? getDecreasingPath(node->right) : 0;
        return currentPath + max(leftPath, rightPath);
    }
    void LongestConsecutivePathUtil(Node* node, int& maxLen) {
        if (node == NULL) return;
        maxLen = max(maxLen, getIncreasingPath(node) + getDecreasingPath(node) - 1);
        LongestConsecutivePathUtil(node->left, maxLen);
        LongestConsecutivePathUtil(node->right, maxLen);
    }
    void FindLongestConsecutivePatientIDs() {
        int maxLen = 0;
        LongestConsecutivePathUtil(root, maxLen);
        cout << "Longest consecutive sequence of Patient IDs: " << maxLen << endl;
    }

    // 6. GetCousins(int key)
    int GetLevel(Node* node, int patientId, int level) {
        if (node == NULL) return -1;
        if (node->data == patientId) return level;
        int left = GetLevel(node->left, patientId, level + 1);
        if (left != -1) return left;
        return GetLevel(node->right, patientId, level + 1);
    }
    Node* FindParent(Node* node, int patientId, Node* parent_node) {
        if (node == NULL) return NULL;
        if (node->data == patientId) return parent_node;
        Node* left_parent = FindParent(node->left, patientId, node);
        if (left_parent) return left_parent;
        return FindParent(node->right, patientId, node);
    }
    Node* FindParentOfNode(int patientId) {
        return FindParent(root, patientId, NULL);
    }
    void PrintCousins(Node* node, int targetPatientId, Node* parentOfTarget, int currentLevel, int targetLevel) {
        if (node == NULL) return;
        if (currentLevel == targetLevel) {
            if (node->data != targetPatientId) {
                Node* currentNodesParent = FindParent(root, node->data, NULL);
                if (currentNodesParent != parentOfTarget) {
                    cout << node->data << " ";
                }
            }
        }
        PrintCousins(node->left, targetPatientId, parentOfTarget, currentLevel + 1, targetLevel);
        PrintCousins(node->right, targetPatientId, parentOfTarget, currentLevel + 1, targetLevel);
    }
    void DisplayCousins(int patientId) {
        int targetLevel = GetLevel(root, patientId, 0);
        Node* parent = FindParent(root, patientId, NULL);
        if (targetLevel == -1) {
            cout << "Patient ID " << patientId << " not found to find cousins." << endl;
            return;
        }
        cout << "Cousin Patient IDs of " << patientId << ": ";
        PrintCousins(root, patientId, parent, 0, targetLevel);
        cout << endl;
    }

    // 7. LevelOrderTraversal(Node* root)
    void LevelOrderTraversal(Node* node) {
        if (node == NULL) return;
        Node* queue[1000];
        int front = 0;
        int rear = 0;

        queue[rear++] = node;

        while (front < rear) {
            Node* current = queue[front++];
            cout << current->data << " ";

            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
    }
    void DisplayAllPatientIDsByLevel() {
        cout << "All Patient IDs (Level Order): ";
        LevelOrderTraversal(root);
        cout << endl;
    }

    // 8. IsFullTree(Node* root)
    bool IsFullTree(Node* node) {
        if (node == NULL) return true;
        if (node->left == NULL && node->right == NULL) return true;
        if (node->left && node->right) {
            return IsFullTree(node->left) && IsFullTree(node->right);
        }
        return false;
    }
    void CheckIfPatientIDTreeIsFull() {
        cout << "Is the Patient ID tree a Full Binary Tree? " << (IsFullTree(root) ? "Yes" : "No") << endl;
    }

    // 9. Merge(AVLTree& otherTree)
    void StoreInOrder(Node* node, vector<int>& arr) {
        if (node == NULL) return;
        StoreInOrder(node->left, arr);
        arr.push_back(node->data);
        StoreInOrder(node->right, arr);
    }
    void MergeVectors(const vector<int>& arr1, const vector<int>& arr2, vector<int>& merged) {
        merged.clear();
        merged.reserve(arr1.size() + arr2.size());
        int i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i] < arr2[j]) merged.push_back(arr1[i++]);
            else if (arr2[j] < arr1[i]) merged.push_back(arr2[j++]);
            else {
                merged.push_back(arr1[i++]);
                j++;
            }
        }
        while (i < arr1.size()) merged.push_back(arr1[i++]);
        while (j < arr2.size()) merged.push_back(arr2[j++]);
    }
    Node* SortedArrayToAVL(const vector<int>& arr, int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start) / 2;
        Node* newNode = new Node(arr[mid]);
        newNode->left = SortedArrayToAVL(arr, start, mid - 1);
        newNode->right = SortedArrayToAVL(arr, mid + 1, end);
        newNode->height = 1 + max(getHeight(newNode->left), getHeight(newNode->right));
        return newNode;
    }
    void MergePatientIDSystems(AVLTree& otherTree) {
        vector<int> arr1_vec, arr2_vec, merged_vec;
        StoreInOrder(this->root, arr1_vec);
        StoreInOrder(otherTree.root, arr2_vec);
        MergeVectors(arr1_vec, arr2_vec, merged_vec);
        DeleteSubtree(this->root);
        this->root = SortedArrayToAVL(merged_vec, 0, merged_vec.size() - 1);
        cout << "Merged Patient IDs from another system." << endl;
    }

    // 10. DeleteNodesGreaterThan(int value)
    Node* DeleteGreaterThanHelper(Node* node, int thresholdId) {
        if (node == NULL) return NULL;

        node->left = DeleteGreaterThanHelper(node->left, thresholdId);
        if (node->data <= thresholdId) {
            node->right = DeleteGreaterThanHelper(node->right, thresholdId);
        }

        if (node->data > thresholdId) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
            int balance = getBalance(node);

            if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
            if (balance > 1 && getBalance(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
            if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
            if (balance < -1 && getBalance(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
            return node;
        }
    }
    void ArchivePatientIDsGreaterThan(int thresholdId) {
        cout << "Archiving Patient IDs greater than: " << thresholdId << endl;
        root = DeleteGreaterThanHelper(root, thresholdId);
    }

    // 11. ContainsIdenticalSubtrees()
    string serializeSubtree(Node* node) {
        if (node == NULL) return "#";
        string s = to_string(node->data);
        s += serializeSubtree(node->left);
        s += serializeSubtree(node->right);
        return s;
    }
    bool CheckIdenticalSubtrees(Node* node, vector<string>& subtrees) {
        if (node == NULL) return false;
        if (CheckIdenticalSubtrees(node->left, subtrees)) return true;
        if (CheckIdenticalSubtrees(node->right, subtrees)) return true;

        string currentSubtreeString = serializeSubtree(node);

        for (int i = 0; i < subtrees.size(); i++) {
            if (subtrees[i] == currentSubtreeString) {
                return true;
            }
        }
        subtrees.push_back(currentSubtreeString);
        return false;
    }
    void CheckForDuplicateIDPatterns() {
        vector<string> subtrees;
        cout << "Does the Patient ID tree contain identical subtree patterns? " << (CheckIdenticalSubtrees(root, subtrees) ? "Yes" : "No") << endl;
    }

    // 12. PruneTree(int maxDepth)
    Node* PruneTreeHelper(Node* node, int currentDepth, int maxDepth) {
        if (node == NULL) return NULL;
        if (currentDepth == maxDepth) {
            DeleteSubtree(node->left); node->left = NULL;
            DeleteSubtree(node->right); node->right = NULL;
            node->height = 1;
            return node;
        }
        node->left = PruneTreeHelper(node->left, currentDepth + 1, maxDepth);
        node->right = PruneTreeHelper(node->right, currentDepth + 1, maxDepth);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) { node->left = leftRotate(node->left); return rightRotate(node); }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) { node->right = rightRotate(node->right); return leftRotate(node); }
        return node;
    }
    void PrunePatientIDTreeByDepth(int maxDepth) {
        cout << "Pruning Patient ID tree to max depth: " << maxDepth << endl;
        root = PruneTreeHelper(root, 0, maxDepth);
    }

    // 13. FindNthInTraversalOrder(int n, int orderType)
    void FindNthInOrder(Node* node, int n, int& count, int& result) {
        if (node == NULL || count >= n) return;
        FindNthInOrder(node->left, n, count, result);
        if (count < n) {
            count++;
            if (count == n) { result = node->data; return; }
        }
        FindNthInOrder(node->right, n, count, result);
    }
    void FindNthPreOrder(Node* node, int n, int& count, int& result) {
        if (node == NULL || count >= n) return;
        if (count < n) {
            count++;
            if (count == n) { result = node->data; return; }
        }
        FindNthPreOrder(node->left, n, count, result);
        FindNthPreOrder(node->right, n, count, result);
    }
    void FindNthPostOrder(Node* node, int n, int& count, int& result) {
        if (node == NULL || count >= n) return;
        FindNthPostOrder(node->left, n, count, result);
        FindNthPostOrder(node->right, n, count, result);
        if (count < n) {
            count++;
            if (count == n) { result = node->data; return; }
        }
    }
    void DisplayNthPatientID(int n, int orderType) {
        int count = 0;
        int result = -1;
        string orderName;

        if (orderType == IN_ORDER) { FindNthInOrder(root, n, count, result); orderName = "In-Order"; }
        else if (orderType == PRE_ORDER) { FindNthPreOrder(root, n, count, result); orderName = "Pre-Order"; }
        else if (orderType == POST_ORDER) { FindNthPostOrder(root, n, count, result); orderName = "Post-Order"; }

        if (result != -1) {
            cout << n << "th Patient ID in " << orderName << " traversal: " << result << endl;
        }
        else {
            cout << "Could not find " << n << "th Patient ID in " << orderName << " traversal (tree too small or invalid n)." << endl;
        }
    }

    // 14. FindParentOfNode(int key)
    Node* FindParentHelper(Node* current, Node* parent, int patientId) {
        if (current == NULL) return NULL;
        if (current->data == patientId) return parent;
        if (patientId < current->data) {
            return FindParentHelper(current->left, current, patientId);
        }
        else {
            return FindParentHelper(current->right, current, patientId);
        }
    }
    void DisplayParentOfPatientID(int patientId) {
        Node* parent = FindParentHelper(root, NULL, patientId);
        if (parent) {
            cout << "Parent ID of Patient ID " << patientId << ": " << parent->data << endl;
        }
        else if (SearchPatient(patientId)) {
            cout << "Patient ID " << patientId << " is the root of the tree (no parent)." << endl;
        }
        else {
            cout << "Patient ID " << patientId << " not found to determine parent." << endl;
        }
    }

    // 15. GetTreeSkewType()
    string GetTreeSkewType() {
        if (root == NULL) return "BALANCED";

        int leftCount = CountNodes(root->left);
        int rightCount = CountNodes(root->right);

        int diff = (leftCount > rightCount) ? (leftCount - rightCount) : (rightCount - leftCount);
        int total = leftCount + rightCount;

        if (total == 0) return "BALANCED";

        if (static_cast<double>(diff) / total > 0.20) {
            if (leftCount > rightCount) return "LEFT_SKEWED (by node count)";
            else return "RIGHT_SKEWED (by node count)";
        }
        return "BALANCED (by node count)";
    }
    void DisplayTreeSkew() {
        cout << "Patient ID Tree Skew Type: " << GetTreeSkewType() << endl;
    }
};

int main()
{
    AVLTree patientIDSystem;

    cout << "--- Patient Record ID Management System ---" << endl;

    patientIDSystem.AddPatient(100);
    patientIDSystem.AddPatient(50);
    patientIDSystem.AddPatient(150);
    patientIDSystem.AddPatient(25);
    patientIDSystem.AddPatient(75);
    patientIDSystem.AddPatient(125);
    patientIDSystem.AddPatient(175);
    patientIDSystem.AddPatient(60);
    patientIDSystem.AddPatient(90);
    patientIDSystem.AddPatient(30);

    cout << "\n--- Initial Patient ID Tree ---" << endl;
    patientIDSystem.DisplayAllPatientIDsByLevel();
    patientIDSystem.IsBST();

    cout << "\n--- Patient ID Searches and Rankings ---" << endl;
    patientIDSystem.SearchPatient(75);
    patientIDSystem.SearchPatient(99);
    patientIDSystem.DisplayPatientRank(60);
    patientIDSystem.DisplayPatientRank(110);

    cout << "\n--- Tree Structural Analysis ---" << endl;
    patientIDSystem.DisplayLCA(60, 90);
    patientIDSystem.DisplayLCA(25, 175);
    patientIDSystem.FindLongestConsecutivePatientIDs();
    patientIDSystem.DisplayCousins(75);
    patientIDSystem.CheckIfPatientIDTreeIsFull();
    patientIDSystem.DisplayTreeSkew();

    cout << "\n--- Patient ID Tree Modifications ---" << endl;
    patientIDSystem.RemovePatient(150);
    patientIDSystem.DisplayAllPatientIDsByLevel();

    AVLTree otherClinicIDs;
    otherClinicIDs.AddPatient(200);
    otherClinicIDs.AddPatient(10);
    otherClinicIDs.AddPatient(160);
    cout << "\n--- Merging Patient IDs from Another Clinic ---" << endl;
    patientIDSystem.MergePatientIDSystems(otherClinicIDs);
    patientIDSystem.DisplayAllPatientIDsByLevel();

    cout << "\n--- Archiving Patient IDs > 100 ---" << endl;
    patientIDSystem.ArchivePatientIDsGreaterThan(100);
    patientIDSystem.DisplayAllPatientIDsByLevel();

    cout << "\n--- Re-checking for Duplicate ID Patterns ---" << endl;
    patientIDSystem.CheckForDuplicateIDPatterns();

    cout << "\n--- Pruning Patient ID Tree to Depth 2 ---" << endl;
    patientIDSystem.PrunePatientIDTreeByDepth(2);
    patientIDSystem.DisplayAllPatientIDsByLevel();

    cout << "\n--- Finding Nth Patient IDs ---" << endl;
    patientIDSystem.DisplayNthPatientID(3, IN_ORDER);
    patientIDSystem.DisplayNthPatientID(2, PRE_ORDER);
    patientIDSystem.DisplayNthPatientID(1, POST_ORDER);

    patientIDSystem.DisplayParentOfPatientID(50);
    patientIDSystem.DisplayParentOfPatientID(10);
    patientIDSystem.DisplayParentOfPatientID(200);
    patientIDSystem.DisplayParentOfPatientID(patientIDSystem.root->data);


    cout << "\n--- System Demonstration Complete ---" << endl;
    return 0;
}
