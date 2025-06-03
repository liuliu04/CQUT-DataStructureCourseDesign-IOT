#include "huffman.h"

void initializeHuffmanTree() {
    int n;
    printf("�������ַ�����С: ");
    scanf("%d", &n);
    getchar(); // ���Ļ��з�

    unsigned char* data = (unsigned char*)malloc(n * sizeof(unsigned char));
    int* freq = (int*)malloc(n * sizeof(int));

    printf("������%d���ַ��Ͷ�Ӧ��Ȩֵ��\n", n);
    for (int i = 0; i < n; i++) {
        printf("�ַ� %d: ", i + 1);
        data[i] = getchar();
        getchar(); // ���Ļ��з�
        printf("Ȩֵ %d: ", i + 1);
        scanf("%d", &freq[i]);
        getchar(); // ���Ļ��з�
    }

    // ������������
    MinHeapNode* root = buildHuffmanTree(data, freq, n);

    // �洢����������
    int arr[MAX_TREE_HT], top = 0;
    HuffmanCode codes[MAX_CHAR] = {0};
    storeHuffmanCodes(root, arr, top, codes);

    // ��������������ļ�
    FILE* file = fopen("huffman", "w");
    if (file) {
        saveHuffmanTree(root, file);
        fclose(file);
    }

    // ��ӡ��������
    printf("\n����������\n");
    printHuffmanTree(root, 0, stdout);

    free(data);
    free(freq);
}

void encode() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("�Ҳ������������ļ�\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    int arr[MAX_TREE_HT], top = 0;
    HuffmanCode codes[MAX_CHAR] = {0};
    storeHuffmanCodes(root, arr, top, codes);

    encodeFile("tobetrans.dat", "codefile", codes);
    printf("������ɣ�����ѱ��浽codefile\n");
}

void decode() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("�Ҳ������������ļ�\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    decodeFile("codefile", "textfile", root);
    printf("������ɣ�����ѱ��浽textfile\n");
}

void printCode() {
    printCodeFile("codefile", "codeprint");
    printf("�����Ѵ�ӡ�����浽codeprint\n");
}

void printTree() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("�Ҳ������������ļ�\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    FILE* outFile = fopen("treeprint", "w");
    if (outFile) {
        printHuffmanTree(root, 0, outFile);
        fclose(outFile);
    }

    printf("���������Ѵ�ӡ�����浽treeprint\n");
}

int main() {
    char choice;
    while (1) {
        printf("\n��ѡ�������\n");
        printf("I - ��ʼ����������\n");
        printf("C - ����\n");
        printf("D - ����\n");
        printf("P - ��ӡ�����ļ�\n");
        printf("T - ��ӡ��������\n");
        printf("Q - �˳�\n");
        printf("������ѡ��: ");
        
        choice = getchar();
        getchar(); // ���Ļ��з�

        switch (choice) {
            case 'I':
            case 'i':
                initializeHuffmanTree();
                break;
            case 'C':
            case 'c':
                encode();
                break;
            case 'D':
            case 'd':
                decode();
                break;
            case 'P':
            case 'p':
                printCode();
                break;
            case 'T':
            case 't':
                printTree();
                break;
            case 'Q':
            case 'q':
                printf("�������˳�\n");
                return 0;
            default:
                printf("��Ч��ѡ��������\n");
        }
    }
    return 0;
} 