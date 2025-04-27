#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include "clothes.h"

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
    void onDirectInitialization();
    void onExplicitInitialization();
    void onUserInputInitialization();
    void onPointerInitialization();
    void onReferenceInitialization();
    void displayClothesInfo(const QString& text);

   private:
    Ui::MainWindow* ui_;
    QTextEdit* textDisplay_;
    QString formatClothes(const Clothes& clothes);
};

#endif	// MAINWINDOW_H
