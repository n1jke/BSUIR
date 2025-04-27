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
    void convertToBinary();

   private:
    QLineEdit* inputLineEdit_;
    QLabel* resultLabel_;

    QString decimalToBinary(int n);
};

#endif	// MAINWINDOW_H
