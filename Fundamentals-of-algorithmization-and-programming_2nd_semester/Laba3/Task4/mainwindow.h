#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void solveHanoi();

   private:
    QLineEdit* inputLineEdit_;
    QTextEdit* resultTextEdit_;

    void hanoiRecursion(int count, int prevPeg, int newPeg, QString& steps);
};

#endif	// MAINWINDOW_H
