#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void selectDir();

   private:
    QLineEdit* pathLineEdit_;
    QPushButton* selectButton_;
    QTextEdit* resultTextEdit_;

    int dfsForFolders(int& subFolders, int& files, int& tempDepth,
                      const QString& filePath);
};

#endif	// MAINWINDOW_H
