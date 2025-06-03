#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentSolutionIndex(-1), solutionSet(nullptr)
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // 创建棋盘
    QWidget* boardWidget = new QWidget;
    boardLayout = new QGridLayout(boardWidget);
    initializeBoard();
    mainLayout->addWidget(boardWidget);

    // 创建求解按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QPushButton* dfsButton = new QPushButton("深度优先搜索", this);
    QPushButton* bfsButton = new QPushButton("广度优先搜索", this);
    QPushButton* backtrackButton = new QPushButton("回溯法", this);

    buttonLayout->addWidget(dfsButton);
    buttonLayout->addWidget(bfsButton);
    buttonLayout->addWidget(backtrackButton);

    mainLayout->addLayout(buttonLayout);

    // 创建导航按钮
    QHBoxLayout* navLayout = new QHBoxLayout;
    QPushButton* prevButton = new QPushButton("上一个", this);
    QPushButton* nextButton = new QPushButton("下一个", this);
    
    prevButton->setObjectName("prevButton");
    nextButton->setObjectName("nextButton");
    
    prevButton->setEnabled(false);
    nextButton->setEnabled(false);

    navLayout->addWidget(prevButton);
    navLayout->addWidget(nextButton);
    mainLayout->addLayout(navLayout);

    // 状态标签
    statusLabel = new QLabel("准备就绪", this);
    mainLayout->addWidget(statusLabel);

    // 连接信号和槽
    connect(dfsButton, &QPushButton::clicked, this, &MainWindow::solveDFS);
    connect(bfsButton, &QPushButton::clicked, this, &MainWindow::solveBFS);
    connect(backtrackButton, &QPushButton::clicked, this, &MainWindow::solveBacktrack);
    connect(prevButton, &QPushButton::clicked, this, &MainWindow::showPrevSolution);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::showNextSolution);

    setWindowTitle("八皇后问题求解器");
    resize(600, 600);
}

MainWindow::~MainWindow()
{
    if (solutionSet) {
        freeSolutionSet(solutionSet);
    }
}

void MainWindow::initializeBoard()
{
    boardLabels.clear();
    for (int i = 0; i < QUEENS_BOARD_SIZE; ++i) {
        for (int j = 0; j < QUEENS_BOARD_SIZE; ++j) {
            QLabel* label = new QLabel;
            label->setFixedSize(60, 60);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet(QString("QLabel { background-color: %1; border: 1px solid black; }")
                               .arg((i + j) % 2 == 0 ? "#B22222" : "#000000"));
            boardLayout->addWidget(label, i, j);
            boardLabels.push_back(label);
        }
    }
}

void MainWindow::clearBoard()
{
    for (auto label : boardLabels) {
        label->setText("");
    }
}

void MainWindow::displaySolution(int* solution)
{
    clearBoard();
    for (int i = 0; i < QUEENS_BOARD_SIZE; ++i) {
        int col = solution[i];
        int index = i * QUEENS_BOARD_SIZE + col;
        if (index >= 0 && index < boardLabels.size()) {
            boardLabels[index]->setText("♛");
            boardLabels[index]->setStyleSheet(QString("QLabel { background-color: %1; border: 1px solid black; color: white; font-size: 40px; }")
                                           .arg((i + col) % 2 == 0 ? "#B22222" : "#000000"));
        }
    }
}

void MainWindow::solveDFS()
{
    if (solutionSet) {
        freeSolutionSet(solutionSet);
    }
    solutionSet = createSolutionSet(100);
    int* board = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        board[i] = -1;
    }
    
    dfs(0, board, solutionSet);
    free(board);
    
    currentSolutionIndex = 0;
    if (solutionSet->size > 0) {
        displaySolution(getSolution(solutionSet, 0));
        statusLabel->setText(QString("深度优先搜索完成，共找到 %1 个解").arg(solutionSet->size));
    } else {
        statusLabel->setText("未找到解决方案");
    }
    updateNavigationButtons();
}

void MainWindow::solveBFS()
{
    if (solutionSet) {
        freeSolutionSet(solutionSet);
    }
    solutionSet = createSolutionSet(100);
    
    bfs(solutionSet);
    
    currentSolutionIndex = 0;
    if (solutionSet->size > 0) {
        displaySolution(getSolution(solutionSet, 0));
        statusLabel->setText(QString("广度优先搜索完成，共找到 %1 个解").arg(solutionSet->size));
    } else {
        statusLabel->setText("未找到解决方案");
    }
    updateNavigationButtons();
}

void MainWindow::solveBacktrack()
{
    if (solutionSet) {
        freeSolutionSet(solutionSet);
    }
    solutionSet = createSolutionSet(100);
    int* board = (int*)malloc(QUEENS_BOARD_SIZE * sizeof(int));
    for (int i = 0; i < QUEENS_BOARD_SIZE; i++) {
        board[i] = -1;
    }
    
    backtrack(0, board, solutionSet);
    free(board);
    
    currentSolutionIndex = 0;
    if (solutionSet->size > 0) {
        displaySolution(getSolution(solutionSet, 0));
        statusLabel->setText(QString("回溯法完成，共找到 %1 个解").arg(solutionSet->size));
    } else {
        statusLabel->setText("未找到解决方案");
    }
    updateNavigationButtons();
}

void MainWindow::showNextSolution()
{
    if (solutionSet && currentSolutionIndex < solutionSet->size - 1) {
        currentSolutionIndex++;
        displaySolution(getSolution(solutionSet, currentSolutionIndex));
        statusLabel->setText(QString("显示第 %1/%2 个解").arg(currentSolutionIndex + 1).arg(solutionSet->size));
        updateNavigationButtons();
    }
}

void MainWindow::showPrevSolution()
{
    if (solutionSet && currentSolutionIndex > 0) {
        currentSolutionIndex--;
        displaySolution(getSolution(solutionSet, currentSolutionIndex));
        statusLabel->setText(QString("显示第 %1/%2 个解").arg(currentSolutionIndex + 1).arg(solutionSet->size));
        updateNavigationButtons();
    }
}

void MainWindow::updateNavigationButtons()
{
    QPushButton* prevButton = findChild<QPushButton*>("prevButton");
    QPushButton* nextButton = findChild<QPushButton*>("nextButton");
    
    if (prevButton && nextButton && solutionSet) {
        prevButton->setEnabled(currentSolutionIndex > 0);
        nextButton->setEnabled(currentSolutionIndex < solutionSet->size - 1);
    }
} 
