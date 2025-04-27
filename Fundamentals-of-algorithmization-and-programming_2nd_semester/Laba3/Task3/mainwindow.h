#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void reverseNumberSlot();

   private:
    QLineEdit* inputLineEdit_;
    QLabel* resultLabel_;

    int reverseNumber(int n, int result = 0);
    bool containsZero(int n);
};

#endif	// MAINWINDOW_H
