#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include "stick_sorter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStick();
    void calculateOrder();
    void clearAll();

private:
    QTableWidget *tableWidget;
    QSpinBox *lengthSpinBox;
    QSpinBox *weightSpinBox;
    QPushButton *addButton;
    QPushButton *calculateButton;
    QPushButton *clearButton;
    QLabel *resultLabel;
    
    Stick sticks[MAX_STICKS];
    int stickCount;
    
    void setupUI();
};

#endif // MAINWINDOW_H 