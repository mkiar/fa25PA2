//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output

    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations

// Implements the Huffman encoding tree using MinHeap
// Returns the index of the root node
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap;
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);
    }
    while (heap.size > 1) {
        // - Pop two smallest nodes
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);
        int parent = nextFree;
        nextFree++;

        //    - Create a new parent node with combined weight
        weightArr[parent] = weightArr[left] + weightArr[right];
        // - Set left/right pointers
        leftArr[parent] = left;
        rightArr[parent] = right;
        charArr[parent] = '-'; // added this due to problems for generateCodes because of empty char arr

        //    - Push new parent index back into the heap
        heap.push(parent, weightArr);
    }
    // 4. Return the index of the last remaining node (root)
    return heap.pop(weightArr);;
}

// Step 4: Use an STL stack to generate codes

// Performs a DFS traversal of the encoded tree using a stack
// creates binary codes for each character until it reaches a leaf node
// Dumps the binary code into the codes array
void generateCodes(int root, string codes[]) {
    // TODO:
    if (root == -1) {
        return;
    }
    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> codesStack;
    codesStack.push({root, ""}); // to ensure stack isnt empty


    while (!codesStack.empty()) {
        pair<int, string> top = codesStack.top();
        int node = top.first;
        string code = top.second;
        codesStack.pop();

        if (leftArr[node] == -1 && rightArr[node] == -1) {
            int index = charArr[node] - 'a';
            codes[index] = code;
        } else {
            // Left edge adds '0', right edge adds '1'.
            if (leftArr[node] != -1) {
                codesStack.push({leftArr[node], code + "0"});
            }
            if (rightArr[node] != -1) {
                codesStack.push({rightArr[node], code + "1"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}