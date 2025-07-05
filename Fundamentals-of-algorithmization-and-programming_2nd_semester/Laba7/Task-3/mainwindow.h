#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include "variant_solver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnSolveClicked();

private:
    void SetupUi();

    QPushButton* btn_solve_;
    QPlainTextEdit* memo_;
    VariantSolver solver_;
};
#endif // MAINWINDOW_H
