#include <iostream>
using namespace std;

// Binary Search Tree Node
struct Node {
    char word[50];
    int frequency;
    bool printed;
    Node* left;
    Node* right;
};

// Comparing two words
int compareWords(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {

        if (a[i] < b[i])
            return -1;

        if (a[i] > b[i])
            return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0')
        return 0;

    if (a[i] == '\0')
        return -1;
    return 1;
}

// Copyng a word
void copyWord(char destination[], char source[]) {

    int i = 0;

    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

// Creating a new node
Node* createNode(char word[]) {
    Node* newNode = new Node();

    copyWord(newNode->word, word);

    newNode->frequency = 1;
    newNode->printed = false;

    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Inserting word into BST
Node* insert(Node* root, char word[]) {
    if (root == nullptr) {
        return createNode(word);
    }
    int result = compareWords(word, root->word);

    if (result < 0) {
        root->left = insert(root->left, word);
    }
    else if (result > 0) {
        root->right = insert(root->right, word);
    }
    else {
        root->frequency++;
    }
    return root;
}

// Displaying words alphabetically
void displayAlphabetical(Node* root) {

    if (root == nullptr)
        return;
    displayAlphabetical(root->left);

    cout << root->word << " : "
         << root->frequency << endl;

    displayAlphabetical(root->right);
}

// Counting unique words
int countUniqueWords(Node* root) {

    if (root == nullptr)
        return 0;

    return 1 +
           countUniqueWords(root->left) +
           countUniqueWords(root->right);
}

// Finding maximum frequency
int findMaxFrequency(Node* root) {

    if (root == nullptr)
        return 0;
    int max = root->frequency;

    int leftMax = findMaxFrequency(root->left);
    int rightMax = findMaxFrequency(root->right);

    if (leftMax > max)
        max = leftMax;

    if (rightMax > max)
        max = rightMax;

    return max;
}

// Displaying most frequent words
void displayMostFrequent(Node* root, int maxFrequency) {

    if (root == nullptr)
        return;

    displayMostFrequent(root->left, maxFrequency);

    if (root->frequency == maxFrequency) {
        cout << root->word << " : "
             << root->frequency << endl;
    }

    displayMostFrequent(root->right, maxFrequency);
}

// Finding highest frequency node not printed yet
Node* findNextByFrequency(Node* root) {

    if (root == nullptr)
        return nullptr;

    Node* best = nullptr;

    Node* leftBest = findNextByFrequency(root->left);
    Node* rightBest = findNextByFrequency(root->right);

    if (leftBest != nullptr)
        best = leftBest;

    if (rightBest != nullptr) {

        if (best == nullptr ||
            rightBest->frequency > best->frequency ||
            (rightBest->frequency == best->frequency &&
             compareWords(rightBest->word, best->word) < 0)) {

            best = rightBest;
        }
    }

    if (!root->printed) {

        if (best == nullptr ||
            root->frequency > best->frequency ||
            (root->frequency == best->frequency &&
             compareWords(root->word, best->word) < 0)) {

            best = root;
        }
    }

    return best;
}

// Displaying words sorted by frequency
void displayByFrequency(Node* root, int uniqueWords) {

    cout << "\nWords Sorted By Frequency:\n";

    for (int i = 0; i < uniqueWords; i++) {

        Node* best = findNextByFrequency(root);

        if (best == nullptr)
            break;

        cout << best->word << " : "
             << best->frequency << endl;

        best->printed = true;
    }
}

// Checking whether character is an alphabet
bool isLetter(char ch) {

    return (ch >= 'A' && ch <= 'Z') ||
           (ch >= 'a' && ch <= 'z');
}

// Converting uppercase to lowercase
char toLower(char ch) {

    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;

    return ch;
}

// Main function
int main() {
    Node* root = nullptr;
    char paragraph[] =
        "The quick brown fox jumps over the lazy dog. "
        "The fox is quick and smart.";
    char word[50];
    int j = 0;
    int totalWords = 0;

    // Reading paragraph character by character
    for (int i = 0; ; i++) {

        char ch = paragraph[i];

        if (isLetter(ch)) {

            word[j] = toLower(ch);
            j++;
        }
        else {

            if (j > 0) {

                word[j] = '\0';

                root = insert(root, word);

                totalWords++;

                j = 0;
            }
        }

        if (ch == '\0')
            break;
    }
    int uniqueWords = countUniqueWords(root);
    cout << "Words in Alphabetical Order:\n";
    displayAlphabetical(root);
    displayByFrequency(root, uniqueWords);

    int maxFrequency = findMaxFrequency(root);

    cout << "\nMost Frequent Word(s):\n";

    displayMostFrequent(root, maxFrequency);

    cout << "\nSummary Information:\n";

    cout << "Total Unique Words: "
         << uniqueWords << endl;

    cout << "Total Word Count: "
         << totalWords << endl;

    return 0;
}