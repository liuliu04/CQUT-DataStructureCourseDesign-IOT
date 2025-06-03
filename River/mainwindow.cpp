#include "mainwindow.h"
#include <QStyle>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentStep(0), solution(nullptr)
{
    setWindowTitle("农夫过河问题");
    resize(800, 600);
    setupUI();
}

MainWindow::~MainWindow()
{
    if (solution) {
        free_solution(solution);
    }
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建标题
    QLabel *titleLabel = new QLabel("农夫过河问题求解", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // 创建河岸显示区域
    QHBoxLayout *banksLayout = new QHBoxLayout();
    
    // 南岸
    southBank = new QFrame(this);
    southBank->setFrameStyle(QFrame::Box | QFrame::Raised);
    southBank->setMinimumSize(300, 200);
    QVBoxLayout *southLayout = new QVBoxLayout(southBank);
    QLabel *southLabel = new QLabel("南岸", southBank);
    southLabel->setAlignment(Qt::AlignCenter);
    southLayout->addWidget(southLabel);
    banksLayout->addWidget(southBank);

    // 北岸
    northBank = new QFrame(this);
    northBank->setFrameStyle(QFrame::Box | QFrame::Raised);
    northBank->setMinimumSize(300, 200);
    QVBoxLayout *northLayout = new QVBoxLayout(northBank);
    QLabel *northLabel = new QLabel("北岸", northBank);
    northLabel->setAlignment(Qt::AlignCenter);
    northLayout->addWidget(northLabel);
    banksLayout->addWidget(northBank);

    mainLayout->addLayout(banksLayout);

    // 创建角色标签
    farmerLabel = new QLabel("👨‍🌾", this);
    wolfLabel = new QLabel("🐺", this);
    sheepLabel = new QLabel("🐑", this);
    cabbageLabel = new QLabel("🥬", this);

    // 初始位置都在南岸
    QVBoxLayout *southItemsLayout = new QVBoxLayout();
    southItemsLayout->addWidget(farmerLabel);
    southItemsLayout->addWidget(wolfLabel);
    southItemsLayout->addWidget(sheepLabel);
    southItemsLayout->addWidget(cabbageLabel);
    southLayout->addLayout(southItemsLayout);

    // 创建按钮区域
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    solveButton = new QPushButton("求解", this);
    nextButton = new QPushButton("下一步", this);
    prevButton = new QPushButton("上一步", this);
    resetButton = new QPushButton("重置", this);

    nextButton->setEnabled(false);
    prevButton->setEnabled(false);
    resetButton->setEnabled(false);

    buttonLayout->addWidget(solveButton);
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(resetButton);
    mainLayout->addLayout(buttonLayout);

    // 创建结果显示区域
    resultText = new QTextEdit(this);
    resultText->setReadOnly(true);
    resultText->setMaximumHeight(100);
    mainLayout->addWidget(resultText);

    // 连接信号和槽
    connect(solveButton, &QPushButton::clicked, this, &MainWindow::solveProblem);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextStep);
    connect(prevButton, &QPushButton::clicked, this, &MainWindow::prevStep);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::reset);
}

void MainWindow::updateVisualization(int state)
{
    // 清除所有标签的父窗口
    farmerLabel->setParent(nullptr);
    wolfLabel->setParent(nullptr);
    sheepLabel->setParent(nullptr);
    cabbageLabel->setParent(nullptr);

    // 获取南岸和北岸的布局
    QVBoxLayout *southLayout = qobject_cast<QVBoxLayout*>(southBank->layout());
    QVBoxLayout *northLayout = qobject_cast<QVBoxLayout*>(northBank->layout());
    
    // 清除现有布局中的所有项目
    if (southLayout) {
        QLayoutItem* item;
        while ((item = southLayout->takeAt(1)) != nullptr) {  // 从索引1开始，保留标题
            delete item->widget();
            delete item;
        }
    }
    if (northLayout) {
        QLayoutItem* item;
        while ((item = northLayout->takeAt(1)) != nullptr) {  // 从索引1开始，保留标题
            delete item->widget();
            delete item;
        }
    }

    // 根据状态重新放置标签
    RiverState riverState;
    decode_state(state, &riverState);

    if (!riverState.farmer) southLayout->addWidget(farmerLabel);
    else northLayout->addWidget(farmerLabel);

    if (!riverState.wolf) southLayout->addWidget(wolfLabel);
    else northLayout->addWidget(wolfLabel);

    if (!riverState.cabbage) southLayout->addWidget(cabbageLabel);
    else northLayout->addWidget(cabbageLabel);

    if (!riverState.sheep) southLayout->addWidget(sheepLabel);
    else northLayout->addWidget(sheepLabel);

    // 添加弹性空间
    southLayout->addStretch();
    northLayout->addStretch();
}

void MainWindow::nextStep()
{
    if (solution && currentStep < solution->state_count - 1) {
        currentStep++;
        updateVisualization(solution->states[currentStep]);
        resultText->setText(QString("步骤 %1: %2").arg(currentStep).arg(getStateDescription(solution->states[currentStep])));
        prevButton->setEnabled(true);
        nextButton->setEnabled(currentStep < solution->state_count - 1);
    }
}

void MainWindow::prevStep()
{
    if (solution && currentStep > 0) {
        currentStep--;
        updateVisualization(solution->states[currentStep]);
        resultText->setText(QString("步骤 %1: %2").arg(currentStep).arg(getStateDescription(solution->states[currentStep])));
        nextButton->setEnabled(true);
        prevButton->setEnabled(currentStep > 0);
    }
}

void MainWindow::reset()
{
    if (solution) {
        currentStep = 0;
        updateVisualization(solution->states[0]);
        resultText->setText(QString("步骤 %1: %2").arg(currentStep).arg(getStateDescription(solution->states[currentStep])));
        prevButton->setEnabled(false);
        nextButton->setEnabled(solution->state_count > 1);
    }
}

QString MainWindow::getStateDescription(int state)
{
    RiverState riverState;
    decode_state(state, &riverState);
    
    QString desc;
    desc += riverState.farmer ? "农夫在北岸" : "农夫在南岸";
    desc += ", ";
    desc += riverState.wolf ? "狼在北岸" : "狼在南岸";
    desc += ", ";
    desc += riverState.cabbage ? "白菜在北岸" : "白菜在南岸";
    desc += ", ";
    desc += riverState.sheep ? "羊在北岸" : "羊在南岸";
    return desc;
}

void MainWindow::solveProblem()
{
    if (solution) {
        free_solution(solution);
    }
    
    solution = find_solution();
    currentStep = 0;
    updateVisualization(solution->states[0]);
    resultText->setText(QString("步骤 %1: %2").arg(currentStep).arg(getStateDescription(solution->states[currentStep])));
    
    nextButton->setEnabled(solution->state_count > 1);
    prevButton->setEnabled(false);
    resetButton->setEnabled(true);
} 