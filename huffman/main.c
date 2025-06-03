#include "huffman.h"

void initializeHuffmanTree() {
    int n;
    printf("请输入字符集大小: ");
    scanf("%d", &n);
    getchar(); // 消耗换行符

    unsigned char* data = (unsigned char*)malloc(n * sizeof(unsigned char));
    int* freq = (int*)malloc(n * sizeof(int));

    printf("请输入%d个字符和对应的权值：\n", n);
    for (int i = 0; i < n; i++) {
        printf("字符 %d: ", i + 1);
        data[i] = getchar();
        getchar(); // 消耗换行符
        printf("权值 %d: ", i + 1);
        scanf("%d", &freq[i]);
        getchar(); // 消耗换行符
    }

    // 构建哈夫曼树
    MinHeapNode* root = buildHuffmanTree(data, freq, n);

    // 存储哈夫曼编码
    int arr[MAX_TREE_HT], top = 0;
    HuffmanCode codes[MAX_CHAR] = {0};
    storeHuffmanCodes(root, arr, top, codes);

    // 保存哈夫曼树到文件
    FILE* file = fopen("huffman", "w");
    if (file) {
        saveHuffmanTree(root, file);
        fclose(file);
    }

    // 打印哈夫曼树
    printf("\n哈夫曼树：\n");
    printHuffmanTree(root, 0, stdout);

    free(data);
    free(freq);
}

void encode() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("找不到哈夫曼树文件\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    int arr[MAX_TREE_HT], top = 0;
    HuffmanCode codes[MAX_CHAR] = {0};
    storeHuffmanCodes(root, arr, top, codes);

    encodeFile("tobetrans.dat", "codefile", codes);
    printf("编码完成，结果已保存到codefile\n");
}

void decode() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("找不到哈夫曼树文件\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    decodeFile("codefile", "textfile", root);
    printf("解码完成，结果已保存到textfile\n");
}

void printCode() {
    printCodeFile("codefile", "codeprint");
    printf("代码已打印并保存到codeprint\n");
}

void printTree() {
    FILE* file = fopen("huffman", "r");
    if (!file) {
        printf("找不到哈夫曼树文件\n");
        return;
    }

    MinHeapNode* root = loadHuffmanTree(file);
    fclose(file);

    FILE* outFile = fopen("treeprint", "w");
    if (outFile) {
        printHuffmanTree(root, 0, outFile);
        fclose(outFile);
    }

    printf("哈夫曼树已打印并保存到treeprint\n");
}

int main() {
    char choice;
    while (1) {
        printf("\n请选择操作：\n");
        printf("I - 初始化哈夫曼树\n");
        printf("C - 编码\n");
        printf("D - 解码\n");
        printf("P - 打印代码文件\n");
        printf("T - 打印哈夫曼树\n");
        printf("Q - 退出\n");
        printf("请输入选择: ");
        
        choice = getchar();
        getchar(); // 消耗换行符

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
                printf("程序已退出\n");
                return 0;
            default:
                printf("无效的选择，请重试\n");
        }
    }
    return 0;
} 