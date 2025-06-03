#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define MAX_CHAR 256

// 哈夫曼树节点结构
typedef struct MinHeapNode {
    unsigned char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// 最小堆结构
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode** array;
} MinHeap;

// 哈夫曼编码结构
typedef struct {
    unsigned char character;
    char* code;
} HuffmanCode;

// 函数声明
MinHeapNode* newNode(unsigned char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isSizeOne(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode);
void buildMinHeap(MinHeap* minHeap);
void printArr(int arr[], int n);
int isLeaf(MinHeapNode* root);
MinHeap* createAndBuildMinHeap(unsigned char data[], int freq[], int size);
MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size);
void storeHuffmanCodes(MinHeapNode* root, int arr[], int top, HuffmanCode* codes);
void saveHuffmanTree(MinHeapNode* root, FILE* file);
MinHeapNode* loadHuffmanTree(FILE* file);
void printHuffmanTree(MinHeapNode* root, int level, FILE* file);
void encodeFile(const char* inputFile, const char* outputFile, HuffmanCode* codes);
void decodeFile(const char* inputFile, const char* outputFile, MinHeapNode* root);
void printCodeFile(const char* inputFile, const char* outputFile);

#endif 