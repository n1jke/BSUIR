#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <memory>
#include "AVLTree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButtonBuild_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonFind_clicked();
    void on_pushButtonSwapMinMax_clicked();
    void on_pushButtonTraversals_clicked();

private:
    Ui::MainWindow* ui;
    // Используем shared_ptr для удобства управления
    std::shared_ptr<sml::AVLTree<int, QString>> tree_;

    void refreshTreeWidget();
    void addNodeItems(QTreeWidgetItem* parentItem, const typename sml::AVLTree<int, QString>::Node* node);
    const typename sml::AVLTree<int, QString>::Node* findMinNode() const;
    const typename sml::AVLTree<int, QString>::Node* findMaxNode() const;
};

#endif // MAINWINDOW_H