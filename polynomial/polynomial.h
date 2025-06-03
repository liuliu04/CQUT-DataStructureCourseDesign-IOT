#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 多项式项的结构体
typedef struct Term {
    double coefficient;  // 系数
    int exponent;       // 指数
    struct Term* next;  // 指向下一项的指针
} Term;

// 多项式的结构体（带头结点的单链表）
typedef struct {
    Term* head;         // 头结点
    int size;          // 项数
} Polynomial;

// 函数声明
Polynomial* createPolynomial();
void destroyPolynomial(Polynomial* poly);
void insertTerm(Polynomial* poly, double coefficient, int exponent);
void printPolynomial(Polynomial* poly);
Polynomial* addPolynomials(Polynomial* a, Polynomial* b);
Polynomial* subtractPolynomials(Polynomial* a, Polynomial* b);
double evaluatePolynomial(Polynomial* poly, double x);
void sortPolynomial(Polynomial* poly);

#endif // POLYNOMIAL_H 