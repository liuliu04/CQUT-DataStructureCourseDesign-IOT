#include "huffman.h"

// �����½ڵ�
MinHeapNode* newNode(unsigned char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// ������С��
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// ����������С�ѽڵ�
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// ��С�ѻ�
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// ���Ѵ�С�Ƿ�Ϊ1
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// ��ȡ��Сֵ�ڵ�
MinHeapNode* extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// �����½ڵ㵽��С��
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// ������С��
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// ����Ƿ�ΪҶ�ڵ�
int isLeaf(MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// ������������С��
MinHeap* createAndBuildMinHeap(unsigned char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// ������������
MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// �洢����������
void storeHuffmanCodes(MinHeapNode* root, int arr[], int top, HuffmanCode* codes) {
    if (root->left) {
        arr[top] = 0;
        storeHuffmanCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        storeHuffmanCodes(root->right, arr, top + 1, codes);
    }
    if (isLeaf(root)) {
        codes[root->data].character = root->data;
        codes[root->data].code = (char*)malloc(top + 1);
        for (int i = 0; i < top; ++i)
            codes[root->data].code[i] = arr[i] + '0';
        codes[root->data].code[top] = '\0';
    }
}

// ��������������ļ�
void saveHuffmanTree(MinHeapNode* root, FILE* file) {
    if (root == NULL) {
        fprintf(file, "# ");
        return;
    }
    fprintf(file, "%c %u ", root->data, root->freq);
    saveHuffmanTree(root->left, file);
    saveHuffmanTree(root->right, file);
}

// ���ļ����ع�������
MinHeapNode* loadHuffmanTree(FILE* file) {
    char c;
    unsigned freq;
    if (fscanf(file, "%c", &c) == EOF || c == '#') {
        fscanf(file, " "); // �����ո�
        return NULL;
    }
    fscanf(file, " %u", &freq);
    MinHeapNode* node = newNode(c, freq);
    node->left = loadHuffmanTree(file);
    node->right = loadHuffmanTree(file);
    return node;
}

// ��ӡ��������
void printHuffmanTree(MinHeapNode* root, int level, FILE* file) {
    if (root == NULL)
        return;

    printHuffmanTree(root->right, level + 1, file);

    for (int i = 0; i < level; i++)
        fprintf(file, "    ");
    fprintf(file, "%c:%u\n", root->data, root->freq);

    printHuffmanTree(root->left, level + 1, file);
}

// �����ļ�
void encodeFile(const char* inputFile, const char* outputFile, HuffmanCode* codes) {
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");
    if (!in || !out) {
        printf("�޷����ļ�\n");
        return;
    }

    unsigned char ch;
    while (fread(&ch, 1, 1, in) == 1) {
        if (codes[ch].code != NULL) {
            fputs(codes[ch].code, out);
        }
    }

    fclose(in);
    fclose(out);
}

// �����ļ�
void decodeFile(const char* inputFile, const char* outputFile, MinHeapNode* root) {
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");
    if (!in || !out) {
        printf("�޷����ļ�\n");
        return;
    }

    MinHeapNode* current = root;
    char bit;
    while ((bit = fgetc(in)) != EOF) {
        if (bit == '0')
            current = current->left;
        else if (bit == '1')
            current = current->right;

        if (isLeaf(current)) {
            fputc(current->data, out);
            current = root;
        }
    }

    fclose(in);
    fclose(out);
}

// ��ӡ�����ļ�
void printCodeFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("�޷����ļ�\n");
        return;
    }

    char bit;
    int count = 0;
    while ((bit = fgetc(in)) != EOF) {
        putchar(bit);
        fputc(bit, out);
        count++;
        if (count == 50) {
            printf("\n");
            fputc('\n', out);
            count = 0;
        }
    }
    printf("\n");

    fclose(in);
    fclose(out);
} 