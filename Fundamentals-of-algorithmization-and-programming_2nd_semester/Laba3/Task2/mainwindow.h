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
    void calculateAckermann();

   private:
    QLineEdit* mLineEdit_;
    QLineEdit* nLineEdit_;
    QLabel* resultLabel_;

    long long ackermannFunction(int m, int n);
};

#endif	// MAINWINDOW_H
