//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//class Node {
//public:
//    int data;
//    Node* left;
//    Node* right;
//    int height;
//
//    Node(int v)
//    {
//        data = v;
//        left = NULL;
//        right = NULL;
//        height = 1;
//    }
//};
//
//class AVLTree {
//public:
//    Node* root;
//
//    AVLTree()
//    {
//        root = NULL;
//    }
//
//    int getHeight(Node* root)
//    {
//        if (root == NULL)
//        {
//            return 0;
//        }
//        return root->height;
//    }
//
//    int getBalance(Node* root)
//    {
//        if (root == NULL)
//        {
//            return 0;
//        }
//        return getHeight(root->left) - getHeight(root->right);
//    }
//
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
//    Node* rightRotate(Node* y)
//    {
//        Node* x = y->left;
//        Node* T2 = x->right;
//
//        x->right = y;
//        y->left = T2;
//
//        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
//        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//
//        return x;
//    }
//
//    Node* leftRotate(Node* x)
//    {
//        Node* y = x->right;
//        Node* T2 = y->left;
//
//        y->left = x;
//        x->right = T2;
//
//        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
//
//        return y;
//    }
//
//    Node* insert(Node* root, int key)
//    {
//        if (root == NULL)
//        {
//            return new Node(key);
//        }
//
//        if (key < root->data)
//        {
//            root->left = insert(root->left, key);
//        }
//        else if (key > root->data)
//        {
//            root->right = insert(root->right, key);
//        }
//        else
//        {
//            return root;
//        }
//
//        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
//
//        int balance = getBalance(root);
//
//        if (balance > 1 && key < root->left->data)
//        {
//            return rightRotate(root);
//        }
//
//        if (balance < -1 && key > root->right->data)
//        {
//            return leftRotate(root);
//        }
//
//        if (balance > 1 && key > root->left->data)
//        {
//            root->left = leftRotate(root->left);
//            return rightRotate(root);
//        }
//
//        if (balance < -1 && key < root->right->data)
//        {
//            root->right = rightRotate(root->right);
//            return leftRotate(root);
//        }
//
//        return root;
//    }
//
//    void insert(int key)
//    {
//        root = insert(root, key);
//    }
//
//    int CountNodes(Node* root)
//    {
//        if (root == NULL)
//        {
//            return 0;
//        }
//        return 1 + CountNodes(root->left) + CountNodes(root->right);
//    }
//
//    // 1. IsBST()
//    bool IsBST()
//    {
//        return IsBSTree(root, NULL, NULL);
//    }
//
//    bool IsBSTree(Node* root, Node* min, Node* max)
//    {
//        if (root == NULL)
//        {
//            return true;
//        }
//
//        if (min != NULL && root->data <= min->data)
//        {
//            return false;
//        }
//
//        if (max != NULL && root->data >= max->data)
//        {
//            return false;
//        }
//
//        return IsBSTree(root->left, min, root) &&
//            IsBSTree(root->right, root, max);
//    }
//
//    // 2. GetRank(Node* root, int key)
//    int GetRank(Node* root, int key)
//    {
//        if (root == NULL)
//        {
//            return 0;
//        }
//
//        if (key < root->data)
//        {
//            return GetRank(root->left, key);
//        }
//        else if (key > root->data)
//        {
//            int leftCount = CountNodes(root->left);
//            return 1 + leftCount + GetRank(root->right, key);
//        }
//        else
//        {
//            return CountNodes(root->left) + 1;
//        }
//    }
//
//    // 3. Invert()
//    void Invert()
//    {
//        InvertTree(root);
//    }
//
//    void InvertTree(Node* root)
//    {
//        if (root == NULL)
//        {
//            return;
//        }
//
//        Node* temp = root->left;
//        root->left = root->right;
//        root->right = temp;
//
//        InvertTree(root->left);
//        InvertTree(root->right);
//    }
//
//    Node* FindLCA(Node* root, int a, int b)
//    {
//        if (root == NULL)
//        {
//            return NULL;
//        }
//
//        if (a < root->data && b < root->data)
//        {
//            return FindLCA(root->left, a, b);
//        }
//
//        if (a > root->data && b > root->data)
//        {
//            return FindLCA(root->right, a, b);
//        }
//
//        return root;
//    }
//
//    // 4. LowestCommonAncestor(int a, int b)
//    int LowestCommonAncestor(int a, int b)
//    {
//        Node* temp = FindLCA(root, a, b);
//        if (temp)
//        {
//            return temp->data;
//        }
//        else
//        {
//            return -1;
//        }
//    }
//
//    int getIncreasingPath(Node* node) {
//        if (node == NULL) {
//            return 0;
//        }
//        int currentPath = 1;
//        int leftPath = 0;
//        int rightPath = 0;
//
//        if (node->left && node->left->data == node->data + 1) {
//            leftPath = getIncreasingPath(node->left);
//        }
//        if (node->right && node->right->data == node->data + 1) {
//            rightPath = getIncreasingPath(node->right);
//        }
//        return currentPath + max(leftPath, rightPath);
//    }
//
//    int getDecreasingPath(Node* node) {
//        if (node == NULL) {
//            return 0;
//        }
//        int currentPath = 1;
//        int leftPath = 0;
//        int rightPath = 0;
//
//        if (node->left && node->left->data == node->data - 1) {
//            leftPath = getDecreasingPath(node->left);
//        }
//        if (node->right && node->right->data == node->data - 1) {
//            rightPath = getDecreasingPath(node->right);
//        }
//        return currentPath + max(leftPath, rightPath);
//    }
//
//    void LongestConsecutivePathUtil(Node* node, int& maxLen) {
//        if (node == NULL) {
//            return;
//        }
//
//        maxLen = max(maxLen, getIncreasingPath(node) + getDecreasingPath(node) - 1);
//
//        LongestConsecutivePathUtil(node->left, maxLen);
//        LongestConsecutivePathUtil(node->right, maxLen);
//    }
//
//    // 5. LongestConsecutivePath()
//    int LongestConsecutivePath() {
//        int maxLen = 0;
//        LongestConsecutivePathUtil(root, maxLen);
//        return maxLen;
//    }
//
//    // 6. GetCousins(int key)
//    void GetCousins(int key)
//    {
//        int targetLevel = GetLevel(root, key, 0);
//        Node* parent = FindParent(root, key, NULL);
//
//        if (targetLevel == -1)
//        {
//            cout << "Key not found.\n";
//            return;
//        }
//
//        cout << "Cousins of " << key << ": ";
//        PrintCousins(root, key, parent, 0, targetLevel);
//        cout << endl;
//    }
//
//    int GetLevel(Node* root, int key, int level)
//    {
//        if (root == NULL)
//        {
//            return -1;
//        }
//
//        if (root->data == key)
//        {
//            return level;
//        }
//
//        int left = GetLevel(root->left, key, level + 1);
//        if (left != -1)
//        {
//            return left;
//        }
//
//        return GetLevel(root->right, key, level + 1);
//    }
//
//    Node* FindParent(Node* root, int key, Node* parent)
//    {
//        if (root == NULL)
//        {
//            return NULL;
//        }
//
//        if (root->data == key)
//        {
//            return parent;
//        }
//
//        Node* left = FindParent(root->left, key, root);
//        if (left)
//        {
//            return left;
//        }
//
//        return FindParent(root->right, key, root);
//    }
//
//    void PrintCousins(Node* root, int key, Node* parent, int level, int targetLevel)
//    {
//        if (root == NULL)
//        {
//            return;
//        }
//
//        if (level == targetLevel)
//        {
//            if (root->data != key && (parent == NULL || (parent->left != root && parent->right != root)))
//            {
//                Node* currentRootParent = FindParentOfNode(root->data);
//                if (currentRootParent != parent) {
//                    cout << root->data << " ";
//                }
//            }
//        }
//
//        PrintCousins(root->left, key, parent, level + 1, targetLevel);
//        PrintCousins(root->right, key, parent, level + 1, targetLevel);
//    }
//
//    // 7. LevelOrderTraversal(Node* root)
//    void LevelOrderTraversal(Node* root)
//    {
//        if (root == NULL)
//        {
//            return;
//        }
//
//        Node* queue[1000];
//        int front = 0;
//        int rear = 0;
//
//        queue[rear++] = root;
//
//        while (front < rear)
//        {
//            Node* current = queue[front++];
//            cout << current->data << " ";
//
//            if (current->left)
//            {
//                queue[rear++] = current->left;
//            }
//            if (current->right)
//            {
//                queue[rear++] = current->right;
//            }
//        }
//    }
//
//    // 8. IsFullTree(Node* root)
//    bool IsFullTree(Node* root)
//    {
//        if (root == NULL)
//        {
//            return true;
//        }
//
//        if (root->left == NULL && root->right == NULL)
//        {
//            return true;
//        }
//
//        if (root->left && root->right)
//        {
//            return IsFullTree(root->left) && IsFullTree(root->right);
//        }
//
//        return false;
//    }
//
//    void StoreInOrder(Node* root, vector<int>& arr)
//    {
//        if (root == NULL)
//        {
//            return;
//        }
//
//        StoreInOrder(root->left, arr);
//        arr.push_back(root->data);
//        StoreInOrder(root->right, arr);
//    }
//
//    void MergeVectors(const vector<int>& arr1, const vector<int>& arr2, vector<int>& merged)
//    {
//        merged.clear();
//        int totalSize = arr1.size() + arr2.size();
//        merged.reserve(totalSize);
//
//        int i = 0;
//        int j = 0;
//
//        while (i < arr1.size() && j < arr2.size())
//        {
//            if (arr1[i] < arr2[j])
//            {
//                merged.push_back(arr1[i]);
//                i++;
//            }
//            else
//            {
//                merged.push_back(arr2[j]);
//                j++;
//            }
//        }
//
//        while (i < arr1.size())
//        {
//            merged.push_back(arr1[i]);
//            i++;
//        }
//
//        while (j < arr2.size())
//        {
//            merged.push_back(arr2[j]);
//            j++;
//        }
//    }
//
//    Node* SortedArrayToAVL(const vector<int>& arr, int start, int end)
//    {
//        if (start > end)
//        {
//            return NULL;
//        }
//
//        int mid = start + (end - start) / 2;
//        Node* newNode = new Node(arr[mid]);
//
//        newNode->left = SortedArrayToAVL(arr, start, mid - 1);
//        newNode->right = SortedArrayToAVL(arr, mid + 1, end);
//
//        newNode->height = 1 + max(getHeight(newNode->left), getHeight(newNode->right));
//
//        return newNode;
//    }
//
//    // 9. Merge(AVLTree& otherTree)
//    void Merge(AVLTree& otherTree)
//    {
//        vector<int> arr1_vec;
//        vector<int> arr2_vec;
//        vector<int> merged_vec;
//
//        StoreInOrder(this->root, arr1_vec);
//        StoreInOrder(otherTree.root, arr2_vec);
//
//        MergeVectors(arr1_vec, arr2_vec, merged_vec);
//
//        DeleteSubtree(this->root);
//        this->root = SortedArrayToAVL(merged_vec, 0, merged_vec.size() - 1);
//    }
//
//    Node* DeleteGreaterThanHelper(Node* node, int value)
//    {
//        if (node == NULL)
//        {
//            return NULL;
//        }
//
//        node->left = DeleteGreaterThanHelper(node->left, value);
//        node->right = DeleteGreaterThanHelper(node->right, value);
//
//        if (node->data > value)
//        {
//            Node* temp = node->left;
//            delete node;
//            return temp;
//        }
//        else
//        {
//            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//            int balance = getBalance(node);
//
//            if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
//            if (balance > 1 && getBalance(node->left) < 0) {
//                node->left = leftRotate(node->left);
//                return rightRotate(node);
//            }
//            if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
//            if (balance < -1 && getBalance(node->right) > 0) {
//                node->right = rightRotate(node->right);
//                return leftRotate(node);
//            }
//            return node;
//        }
//    }
//
//    // 10. DeleteNodesGreaterThan(int value)
//    void DeleteNodesGreaterThan(int value)
//    {
//        root = DeleteGreaterThanHelper(root, value);
//    }
//
//    string serializeSubtree(Node* node) {
//        if (node == NULL) {
//            return "#";
//        }
//
//        string s = to_string(node->data);
//        s += serializeSubtree(node->left);
//        s += serializeSubtree(node->right);
//        return s;
//    }
//
//    bool CheckIdenticalSubtrees(Node* root, vector<string>& subtrees) {
//        if (root == NULL) {
//            return false;
//        }
//
//        if (CheckIdenticalSubtrees(root->left, subtrees)) {
//            return true;
//        }
//        if (CheckIdenticalSubtrees(root->right, subtrees)) {
//            return true;
//        }
//
//        string currentSubtreeString = serializeSubtree(root);
//
//        for (int i = 0; i < subtrees.size(); i++) {
//            if (subtrees[i] == currentSubtreeString) {
//                return true;
//            }
//        }
//
//        subtrees.push_back(currentSubtreeString);
//        return false;
//    }
//
//    // 11. ContainsIdenticalSubtrees()
//    bool ContainsIdenticalSubtrees()
//    {
//        vector<string> subtrees;
//        return CheckIdenticalSubtrees(root, subtrees);
//    }
//
//    // 12. PruneTree(int maxDepth)
//    void PruneTree(int maxDepth)
//    {
//        root = PruneTreeHelper(root, 0, maxDepth);
//    }
//
//    Node* PruneTreeHelper(Node* root, int currentDepth, int maxDepth)
//    {
//        if (root == NULL)
//        {
//            return NULL;
//        }
//
//        if (currentDepth == maxDepth)
//        {
//            DeleteSubtree(root->left);
//            root->left = NULL;
//            DeleteSubtree(root->right);
//            root->right = NULL;
//
//            root->height = 1;
//
//            return root;
//        }
//
//        root->left = PruneTreeHelper(root->left, currentDepth + 1, maxDepth);
//        root->right = PruneTreeHelper(root->right, currentDepth + 1, maxDepth);
//
//        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
//        int balance = getBalance(root);
//
//        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
//        if (balance > 1 && getBalance(root->left) < 0) {
//            root->left = leftRotate(root->left);
//            return rightRotate(root);
//        }
//        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
//        if (balance < -1 && getBalance(root->right) > 0) {
//            root->right = rightRotate(root->right);
//            return leftRotate(root);
//        }
//
//        return root;
//    }
//
//    void DeleteSubtree(Node* root)
//    {
//        if (root == NULL)
//        {
//            return;
//        }
//
//        DeleteSubtree(root->left);
//        DeleteSubtree(root->right);
//        delete root;
//    }
//
//
//#define IN_ORDER 0
//#define PRE_ORDER 1
//#define POST_ORDER 2
//
//    // 13. FindNthInTraversalOrder(int n, int orderType)
//    int FindNthInTraversalOrder(int n, int orderType)
//    {
//        int count = 0;
//        int result = -1;
//
//        if (orderType == IN_ORDER)
//        {
//            FindNthInOrder(root, n, count, result);
//        }
//        else if (orderType == PRE_ORDER)
//        {
//            FindNthPreOrder(root, n, count, result);
//        }
//        else if (orderType == POST_ORDER)
//        {
//            FindNthPostOrder(root, n, count, result);
//        }
//
//        return result;
//    }
//
//    void FindNthInOrder(Node* root, int n, int& count, int& result)
//    {
//        if (root == NULL || count >= n)
//        {
//            return;
//        }
//
//        FindNthInOrder(root->left, n, count, result);
//
//        if (count < n)
//        {
//            count++;
//            if (count == n)
//            {
//                result = root->data;
//                return;
//            }
//        }
//
//        FindNthInOrder(root->right, n, count, result);
//    }
//
//    void FindNthPreOrder(Node* root, int n, int& count, int& result)
//    {
//        if (root == NULL || count >= n)
//        {
//            return;
//        }
//
//        if (count < n)
//        {
//            count++;
//            if (count == n)
//            {
//                result = root->data;
//                return;
//            }
//        }
//
//        FindNthPreOrder(root->left, n, count, result);
//        FindNthPreOrder(root->right, n, count, result);
//    }
//
//    void FindNthPostOrder(Node* root, int n, int& count, int& result)
//    {
//        if (root == NULL || count >= n)
//        {
//            return;
//        }
//
//        FindNthPostOrder(root->left, n, count, result);
//        FindNthPostOrder(root->right, n, count, result);
//
//        if (count < n)
//        {
//            count++;
//            if (count == n)
//            {
//                result = root->data;
//                return;
//            }
//        }
//    }
//
//    // 14. FindParentOfNode(int key)
//    Node* FindParentOfNode(int key)
//    {
//        return FindParentHelper(root, NULL, key);
//    }
//
//    Node* FindParentHelper(Node* current, Node* parent, int key)
//    {
//        if (current == NULL)
//        {
//            return NULL;
//        }
//
//        if (current->data == key)
//        {
//            return parent;
//        }
//
//        if (key < current->data)
//        {
//            return FindParentHelper(current->left, current, key);
//        }
//        else
//        {
//            return FindParentHelper(current->right, current, key);
//        }
//    }
//
//    // 15. GetTreeSkewType()
//    string GetTreeSkewType()
//    {
//        if (root == NULL)
//        {
//            return "BALANCED";
//        }
//
//        int leftCount = CountNodes(root->left);
//        int rightCount = CountNodes(root->right);
//
//        int diff;
//        if (leftCount > rightCount) {
//            diff = leftCount - rightCount;
//        }
//        else {
//            diff = rightCount - leftCount;
//        }
//
//        int total = leftCount + rightCount;
//
//        if (total == 0)
//        {
//            return "BALANCED";
//        }
//
//        if (static_cast<double>(diff) / total > 0.20)
//        {
//            if (leftCount > rightCount)
//            {
//                return "LEFT_SKEWED";
//            }
//            else
//            {
//                return "RIGHT_SKEWED";
//            }
//        }
//
//        return "BALANCED";
//    }
//
//    ~AVLTree() {
//        DeleteSubtree(root);
//    }
//};
//
//int main()
//{
//    AVLTree AT;
//
//    AT.insert(20);
//    AT.insert(10);
//    AT.insert(30);
//    AT.insert(5);
//    AT.insert(15);
//    AT.insert(25);
//    AT.insert(35);
//    AT.insert(13);
//    AT.insert(17);
//
//
//    cout << "-----LEVEL ORDER TRAVERSAL----- " << endl;
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    cout << "RANK OF 17: " << AT.GetRank(AT.root, 17) << endl;
//    cout << "RANK OF 35: " << AT.GetRank(AT.root, 35) << endl;
//    cout << " " << endl;
//
//    cout << "Is BST: " << (AT.IsBST() ? "Yes" : "No") << endl;
//    cout << " " << endl;
//
//    AT.Invert();
//    cout << "-----LEVEL ORDER OF TREE AFTER INVERTING----- " << endl;
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    AT.Invert();
//    cout << "-----LEVEL ORDER OF TREE AFTER RE-INVERTING (RESTORED)----- " << endl;
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    cout << "LCA OF 13 AND 17 IS " << AT.LowestCommonAncestor(13, 17) << endl;
//    cout << "LCA OF 5 AND 25 IS " << AT.LowestCommonAncestor(5, 25) << endl;
//    cout << " " << endl;
//
//    AT.insert(11);
//    AT.insert(12);
//    AT.insert(14);
//    cout << "LONGEST CONSECTIVE PATH LENGTH IS " << AT.LongestConsecutivePath() << endl;
//    cout << " " << endl;
//
//    AT.GetCousins(13);
//    AT.GetCousins(25);
//    cout << " " << endl;
//
//    cout << "Is Full Tree -> " << (AT.IsFullTree(AT.root) ? "Yes" : "No") << endl;
//    cout << " " << endl;
//
//    AVLTree AT2;
//    AT2.insert(40);
//    AT2.insert(50);
//    AT2.insert(60);
//
//    cout << "-----MERGING TREE2 INTO TREE1-----" << endl;
//    AT.Merge(AT2);
//    cout << "LEVEL ORDER AFTER MERGING : ";
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    AT.DeleteNodesGreaterThan(30);
//    cout << "LEVEL ORDER AFTER DELETING > 30 : ";
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    cout << "CONTAINS IDENTICAL SUBTREES : " << (AT.ContainsIdenticalSubtrees() ? "Yes" : "No") << endl;
//    cout << " " << endl;
//
//    AT.PruneTree(2);
//    cout << "LEVEL ORDER AFTER PRUNING TO DEPTH 2 : ";
//    AT.LevelOrderTraversal(AT.root);
//    cout << endl;
//    cout << " " << endl;
//
//    int nth = 3;
//    cout << nth << "rd ELEMENT IN INORDER : " << AT.FindNthInTraversalOrder(nth, IN_ORDER) << endl;
//    cout << " " << endl;
//
//    cout << "2nd ELEMENT IN PREORDER : " << AT.FindNthInTraversalOrder(2, PRE_ORDER) << endl;
//    cout << " " << endl;
//
//    cout << "1st ELEMENT IN POSTORDER : " << AT.FindNthInTraversalOrder(1, POST_ORDER) << endl;
//    cout << " " << endl;
//
//    Node* parent = AT.FindParentOfNode(20);
//    if (parent)
//    {
//        cout << "PARENT OF 20: " << parent->data << endl;
//    }
//    else
//    {
//        cout << "PARENT OF 20 NOT FOUND or IT'S THE ROOT" << endl;
//    }
//    cout << " " << endl;
//
//    cout << "TREE SKEW TYPE : " << AT.GetTreeSkewType() << endl;
//
//    return 0;
//}
