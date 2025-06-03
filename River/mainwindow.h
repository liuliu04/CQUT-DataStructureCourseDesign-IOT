#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include "river_core.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void solveProblem();
    void nextStep();
    void prevStep();
    void reset();

private:
    QFrame *southBank;
    QFrame *northBank;
    QLabel *farmerLabel;
    QLabel *wolfLabel;
    QLabel *sheepLabel;
    QLabel *cabbageLabel;
    QPushButton *solveButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QPushButton *resetButton;
    QTextEdit *resultText;
    
    Solution* solution;
    int currentStep;
    
    void updateVisualization(int state);
    void setupUI();
    QString getStateDescription(int state);
};

#endif // MAINWINDOW_H 