#include "polynomial.h"

void printMenu() {
    printf("\n一元稀疏多项式计算器\n");
    printf("1. 输入多项式\n");
    printf("2. 显示多项式\n");
    printf("3. 多项式加法\n");
    printf("4. 多项式减法\n");
    printf("5. 计算多项式在x处的值\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}

void inputPolynomial(Polynomial* poly) {
    int n;
    printf("请输入多项式的项数: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        double coeff;
        int exp;
        printf("请输入第%d项的系数和指数: ", i + 1);
        scanf("%lf %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

int main() {
    Polynomial* poly1 = createPolynomial();
    Polynomial* poly2 = createPolynomial();
    Polynomial* result = NULL;
    int choice;
    double x;
    
    while (1) {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 0:
                destroyPolynomial(poly1);
                destroyPolynomial(poly2);
                if (result) destroyPolynomial(result);
                return 0;
                
            case 1:
                printf("选择要输入的多项式(1或2): ");
                int polyChoice;
                scanf("%d", &polyChoice);
                if (polyChoice == 1) {
                    destroyPolynomial(poly1);
                    poly1 = createPolynomial();
                    inputPolynomial(poly1);
                } else if (polyChoice == 2) {
                    destroyPolynomial(poly2);
                    poly2 = createPolynomial();
                    inputPolynomial(poly2);
                }
                break;
                
            case 2:
                printf("选择要显示的多项式(1或2): ");
                scanf("%d", &polyChoice);
                if (polyChoice == 1) {
                    printf("多项式1: ");
                    printPolynomial(poly1);
                } else if (polyChoice == 2) {
                    printf("多项式2: ");
                    printPolynomial(poly2);
                }
                break;
                
            case 3:
                if (result) destroyPolynomial(result);
                result = addPolynomials(poly1, poly2);
                printf("多项式1 + 多项式2 = ");
                printPolynomial(result);
                break;
                
            case 4:
                if (result) destroyPolynomial(result);
                result = subtractPolynomials(poly1, poly2);
                printf("多项式1 - 多项式2 = ");
                printPolynomial(result);
                break;
                
            case 5:
                printf("选择要计算的多项式(1或2): ");
                scanf("%d", &polyChoice);
                printf("请输入x的值: ");
                scanf("%lf", &x);
                if (polyChoice == 1) {
                    printf("多项式1在x=%g处的值: %g\n", x, evaluatePolynomial(poly1, x));
                } else if (polyChoice == 2) {
                    printf("多项式2在x=%g处的值: %g\n", x, evaluatePolynomial(poly2, x));
                }
                break;
                
            default:
                printf("无效的选择，请重试\n");
        }
    }
    
    return 0;
} 