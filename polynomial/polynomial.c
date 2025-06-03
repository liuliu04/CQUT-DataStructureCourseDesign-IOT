#include "polynomial.h"

// 创建新的多项式
Polynomial* createPolynomial() {
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    if (poly == NULL) {
        return NULL;
    }
    poly->head = (Term*)malloc(sizeof(Term));  // 创建头结点
    if (poly->head == NULL) {
        free(poly);
        return NULL;
    }
    poly->head->next = NULL;
    poly->size = 0;
    return poly;
}

// 销毁多项式
void destroyPolynomial(Polynomial* poly) {
    if (poly == NULL) return;
    
    Term* current = poly->head;
    while (current != NULL) {
        Term* temp = current;
        current = current->next;
        free(temp);
    }
    free(poly);
}

// 插入新项
void insertTerm(Polynomial* poly, double coefficient, int exponent) {
    if (poly == NULL || coefficient == 0) return;
    
    Term* newTerm = (Term*)malloc(sizeof(Term));
    if (newTerm == NULL) return;
    
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    
    // 找到合适的插入位置（按指数降序）
    Term* current = poly->head;
    while (current->next != NULL && current->next->exponent > exponent) {
        current = current->next;
    }
    
    // 如果指数相同，合并同类项
    if (current->next != NULL && current->next->exponent == exponent) {
        current->next->coefficient += coefficient;
        if (current->next->coefficient == 0) {
            Term* temp = current->next;
            current->next = temp->next;
            free(temp);
            poly->size--;
        }
        free(newTerm);
    } else {
        newTerm->next = current->next;
        current->next = newTerm;
        poly->size++;
    }
}

// 打印多项式
void printPolynomial(Polynomial* poly) {
    if (poly == NULL || poly->size == 0) {
        printf("0\n");
        return;
    }
    
    printf("%d", poly->size);
    Term* current = poly->head->next;
    while (current != NULL) {
        printf(",%g,%d", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

// 多项式加法
Polynomial* addPolynomials(Polynomial* a, Polynomial* b) {
    if (a == NULL || b == NULL) return NULL;
    
    Polynomial* result = createPolynomial();
    if (result == NULL) return NULL;
    
    Term* currentA = a->head->next;
    Term* currentB = b->head->next;
    
    while (currentA != NULL || currentB != NULL) {
        if (currentA == NULL) {
            insertTerm(result, currentB->coefficient, currentB->exponent);
            currentB = currentB->next;
        } else if (currentB == NULL) {
            insertTerm(result, currentA->coefficient, currentA->exponent);
            currentA = currentA->next;
        } else if (currentA->exponent > currentB->exponent) {
            insertTerm(result, currentA->coefficient, currentA->exponent);
            currentA = currentA->next;
        } else if (currentA->exponent < currentB->exponent) {
            insertTerm(result, currentB->coefficient, currentB->exponent);
            currentB = currentB->next;
        } else {
            double sum = currentA->coefficient + currentB->coefficient;
            if (sum != 0) {
                insertTerm(result, sum, currentA->exponent);
            }
            currentA = currentA->next;
            currentB = currentB->next;
        }
    }
    
    return result;
}

// 多项式减法
Polynomial* subtractPolynomials(Polynomial* a, Polynomial* b) {
    if (a == NULL || b == NULL) return NULL;
    
    Polynomial* result = createPolynomial();
    if (result == NULL) return NULL;
    
    Term* currentA = a->head->next;
    Term* currentB = b->head->next;
    
    while (currentA != NULL || currentB != NULL) {
        if (currentA == NULL) {
            insertTerm(result, -currentB->coefficient, currentB->exponent);
            currentB = currentB->next;
        } else if (currentB == NULL) {
            insertTerm(result, currentA->coefficient, currentA->exponent);
            currentA = currentA->next;
        } else if (currentA->exponent > currentB->exponent) {
            insertTerm(result, currentA->coefficient, currentA->exponent);
            currentA = currentA->next;
        } else if (currentA->exponent < currentB->exponent) {
            insertTerm(result, -currentB->coefficient, currentB->exponent);
            currentB = currentB->next;
        } else {
            double diff = currentA->coefficient - currentB->coefficient;
            if (diff != 0) {
                insertTerm(result, diff, currentA->exponent);
            }
            currentA = currentA->next;
            currentB = currentB->next;
        }
    }
    
    return result;
}

// 计算多项式在x处的值
double evaluatePolynomial(Polynomial* poly, double x) {
    if (poly == NULL) return 0;
    
    double result = 0;
    Term* current = poly->head->next;
    
    while (current != NULL) {
        result += current->coefficient * pow(x, current->exponent);
        current = current->next;
    }
    
    return result;
}

// 对多项式按指数降序排序
void sortPolynomial(Polynomial* poly) {
    if (poly == NULL || poly->size <= 1) return;
    
    Term* current = poly->head->next;
    while (current != NULL) {
        Term* next = current->next;
        while (next != NULL) {
            if (current->exponent < next->exponent) {
                // 交换系数和指数
                double tempCoeff = current->coefficient;
                int tempExp = current->exponent;
                current->coefficient = next->coefficient;
                current->exponent = next->exponent;
                next->coefficient = tempCoeff;
                next->exponent = tempExp;
            }
            next = next->next;
        }
        current = current->next;
    }
} 