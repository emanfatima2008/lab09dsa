#include <iostream>
using namespace std;

// Binary search tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Creating a new Binary search tree node
Node* createNode(int value) {
    Node* newNode = new Node();

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Inserting into Binary search Tree recursively
Node* insert(Node* root, int value) {

    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder Traversal
void inorder(Node* root) {

    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Recursive Search
bool search(Node* root, int key) {

    if (root == nullptr) {
        return false;
    }

    if (root->data == key) {
        return true;
    }

    if (key < root->data) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Finding Minimum
int findMin(Node* root) {

    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

// Finding Maximum
int findMax(Node* root) {

    while (root->right != nullptr) {
        root = root->right;
    }

    return root->data;
}

// Finding Predecessor
Node* predecessor(Node* root, int key) {

    Node* current = root;
    Node* pred = nullptr;

    while (current != nullptr) {

        if (key > current->data) {
            pred = current;
            current = current->right;
        }
        else if (key < current->data) {
            current = current->left;
        }
        else {

            if (current->left != nullptr) {
                pred = current->left;

                while (pred->right != nullptr) {
                    pred = pred->right;
                }
            }

            break;
        }
    }

    return pred;
}

// Finding Successor
Node* successor(Node* root, int key) {

    Node* current = root;
    Node* succ = nullptr;

    while (current != nullptr) {

        if (key < current->data) {
            succ = current;
            current = current->left;
        }
        else if (key > current->data) {
            current = current->right;
        }
        else {

            if (current->right != nullptr) {
                succ = current->right;

                while (succ->left != nullptr) {
                    succ = succ->left;
                }
            }

            break;
        }
    }

    return succ;
}

// Recursive Range Query
void rangeQueryRecursive(
    Node* root,
    int low,
    int high,
    int& comparisons
) {

    if (root == nullptr) {
        return;
    }
    comparisons++;

    if (root->data < low) {
        rangeQueryRecursive(root->right, low, high, comparisons);
        return;
    }
    comparisons++;

    if (root->data > high) {
        rangeQueryRecursive(root->left, low, high, comparisons);
        return;
    }

    rangeQueryRecursive(root->left, low, high, comparisons);

    cout << root->data << " ";

    rangeQueryRecursive(root->right, low, high, comparisons);
}

// Structure for Stack Data
struct Frame {
    Node* node;
    bool visit;
};

// Stack Node
struct StackNode {
    Frame data;
    StackNode* next;
};

// Custom Stack
class Stack {

private:
    StackNode* top;

public:

    Stack() {
        top = nullptr;
    }

    // Push operation
    void push(Frame value) {

        StackNode* newNode = new StackNode();

        newNode->data = value;
        newNode->next = top;

        top = newNode;
    }

    // Pop operation
    Frame pop() {

        Frame value = top->data;

        StackNode* temp = top;

        top = top->next;

        delete temp;

        return value;
    }

    // Checking whether stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Destructor
    ~Stack() {

        while (!isEmpty()) {
            pop();
        }
    }
};

// Iterative Range Query Using Custom Stack
void rangeQueryIterative(Node* root, int low, int high, int& comparisons) {

    Stack s;

    if (root == nullptr) {
        return;
    }

    Frame first;
    first.node = root;
    first.visit = false;

    s.push(first);

    while (!s.isEmpty()) {

        Frame currentFrame = s.pop();

        Node* current = currentFrame.node;

        if (current == nullptr) {
            continue;
        }

        // If this node is ready to be printed
        if (currentFrame.visit == true) {

            cout << current->data << " ";

            continue;
        }

        comparisons++;

        // Current value is smaller than lower limit
        if (current->data < low) {

            Frame rightFrame;

            rightFrame.node = current->right;
            rightFrame.visit = false;

            s.push(rightFrame);
        }

        // Current value is greater than upper limit
        else {

            comparisons++;

            if (current->data > high) {

                Frame leftFrame;

                leftFrame.node = current->left;
                leftFrame.visit = false;

                s.push(leftFrame);
            }

            // Current value is within range
            else {

                Frame rightFrame;
                rightFrame.node = current->right;
                rightFrame.visit = false;

                Frame visitFrame;
                visitFrame.node = current;
                visitFrame.visit = true;

                Frame leftFrame;
                leftFrame.node = current->left;
                leftFrame.visit = false;

                // Push in reverse inorder order
                s.push(rightFrame);
                s.push(visitFrame);
                s.push(leftFrame);
            }
        }
    }
}

// Main Function
int main() {
    Node* root = nullptr;

    int values[] = {
        50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85
    };

    int n = 11;

    // Insert values into BST
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    cout << "Inorder Traversal: ";
    inorder(root);

    // Search
    int key = 40;

    cout << "\n\nSearching for " << key << ": ";

    if (search(root, key)) {
        cout << "Found";
    }
    else {
        cout << "Not Found";
    }

    // Minimum and Maximum
    cout << "\nMinimum Value: " << findMin(root);
    cout << "\nMaximum Value: " << findMax(root);

    // Predecessor
    Node* pred = predecessor(root, key);

    if (pred != nullptr) {
        cout << "\nPredecessor of " << key << ": " << pred->data;
    }
    else {
        cout << "\nNo predecessor found";
    }

    // Successor
    Node* succ = successor(root, key);

    if (succ != nullptr) {
        cout << "\nSuccessor of " << key << ": " << succ->data;
    }
    else {
        cout << "\nNo successor found";
    }

    // Range Query
    int low = 30;
    int high = 70;

    int recursiveComparisons = 0;

    cout << "\n\nRecursive Range Query: ";

    rangeQueryRecursive(
        root, low, high, recursiveComparisons
    );

    cout << "\nRecursive Comparisons: "
         << recursiveComparisons;

    int iterativeComparisons = 0;

    cout << "\n\nIterative Range Query Using Stack: ";

    rangeQueryIterative(
        root, low, high, iterativeComparisons
    );

    cout << "\nIterative Comparisons: "
         << iterativeComparisons;

    cout << endl;

    return 0;
}