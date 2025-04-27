#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    // memory Tab
    void onBtnMemcpyClicked();
    void onBtnMemmoveClicked();
    void onBtnMemsetClicked();

    // copy Tab
    void onBtnStrcpyClicked();
    void onBtnStrncpyClicked();

    // concatenate Tab
    void onBtnStrcatClicked();
    void onBtnStrncatClicked();

    // compare Tab
    void onBMemcmpClicked();
    void onBtnStrcmpClicked();
    void onBtnStrcollClicked();
    void onBtnStrncmpClicked();

   private:
    Ui::MainWindow* ui_;
    void showError(const QString& message);
};
#endif	// MAINWINDOW_H
