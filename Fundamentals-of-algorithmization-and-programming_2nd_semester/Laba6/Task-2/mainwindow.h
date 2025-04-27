#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>

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
    void OnEnterParagraph();
    void OnReadParagraph();
    void OnEnterArray();
    void OnExit();

   private:
    Ui::MainWindow* ui;
    QTextEdit* text_edit_output_;
};
#endif	// MAINWINDOW_H
