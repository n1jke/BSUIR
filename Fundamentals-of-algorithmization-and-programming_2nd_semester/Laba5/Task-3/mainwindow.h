#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include "bitsett.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void updateDisplay();
    void onSetClicked();
    void onSetAllClicked();
    void onResetClicked();
    void onResetAllClicked();
    void onFlipClicked();
    void onFlipAllClicked();
    void onTestClicked();
    void onCheckAllClicked();
    void onCheckAnyClicked();
    void onCheckNoneClicked();
    void onCountClicked();
    void onToStringClicked();
    void onToUlongClicked();
    void onToUllongClicked();
    void onNotClicked();
    void onOrClicked();
    void onInitializeClicked();

   private:
    Ui::MainWindow* ui_;
    static const size_t size = 64;
    Bitsett<size> bitset_;
};
#endif	// MAINWINDOW_H
