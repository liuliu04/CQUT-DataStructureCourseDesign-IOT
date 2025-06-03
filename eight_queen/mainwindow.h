#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <vector>

extern "C" {
    #include "queens.h"
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void solveDFS();
    void solveBFS();
    void solveBacktrack();
    void showNextSolution();
    void showPrevSolution();

private:
    void initializeBoard();
    void clearBoard();
    void displaySolution(int* positions);
    void updateNavigationButtons();

    QGridLayout* boardLayout;
    QLabel* statusLabel;
    std::vector<QLabel*> boardLabels;
    int currentSolutionIndex;
    SolutionSet* solutionSet;
};

#endif // MAINWINDOW_H 