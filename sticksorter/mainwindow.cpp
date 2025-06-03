#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init_sticks(sticks, &stickCount);
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // 创建输入区域
    QHBoxLayout *inputLayout = new QHBoxLayout();
    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setRange(1, 1000);
    weightSpinBox = new QSpinBox(this);
    weightSpinBox->setRange(1, 1000);
    addButton = new QPushButton("添加木棒", this);
    
    inputLayout->addWidget(new QLabel("长度:", this));
    inputLayout->addWidget(lengthSpinBox);
    inputLayout->addWidget(new QLabel("重量:", this));
    inputLayout->addWidget(weightSpinBox);
    inputLayout->addWidget(addButton);
    
    // 创建表格
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"序号", "长度", "重量"});
    
    // 创建按钮区域
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    calculateButton = new QPushButton("计算最优顺序", this);
    clearButton = new QPushButton("清空", this);
    buttonLayout->addWidget(calculateButton);
    buttonLayout->addWidget(clearButton);
    
    // 创建结果显示区域
    resultLabel = new QLabel(this);
    
    // 添加所有组件到主布局
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(resultLabel);
    
    // 连接信号和槽
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addStick);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateOrder);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearAll);
    
    resize(600, 400);
}

void MainWindow::addStick()
{
    int length = lengthSpinBox->value();
    int weight = weightSpinBox->value();
    
    add_stick(sticks, &stickCount, length, weight);
    
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sticks[stickCount-1].index)));
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(sticks[stickCount-1].length)));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(sticks[stickCount-1].weight)));
}

void MainWindow::calculateOrder()
{
    if (stickCount == 0) {
        QMessageBox::warning(this, "警告", "请先添加木棒！");
        return;
    }
    
    SortResult result = calculate_min_time(sticks, stickCount);
    
    QString resultText = QString("最少准备时间: %1 分钟\n").arg(result.total_time);
    resultText += "加工顺序: ";
    for (int i = 0; i < result.order_size; ++i) {
        resultText += QString::number(result.order[i]);
        if (i < result.order_size - 1) {
            resultText += " -> ";
        }
    }
    
    resultLabel->setText(resultText);
    free_sort_result(&result);
}

void MainWindow::clearAll()
{
    init_sticks(sticks, &stickCount);
    tableWidget->setRowCount(0);
    resultLabel->clear();
} 