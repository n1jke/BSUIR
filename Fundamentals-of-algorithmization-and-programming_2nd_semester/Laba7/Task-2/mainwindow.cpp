// mainwindow.cpp
#include "mainwindow.h"
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      tree_(std::make_shared<sml::AVLTree<int, QString>>()) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonBuild_clicked() {
    tree_->clear();
    int rows = ui->tableWidgetInput->rowCount();


    for (int i = 0; i < rows; ++i) {
        bool ok;
        int key = ui->tableWidgetInput->item(i, 0)->text().toInt(&ok);
        if (!ok)
            continue;
        QString value = ui->tableWidgetInput->item(i, 1)->text();
        tree_->insert(key, value);
    }
    refreshTreeWidget();
}

void MainWindow::on_pushButtonAdd_clicked() {
    bool ok;
    int key = ui->tableWidgetInput->item(0, 0)->text().toInt(&ok);
    if (!ok)
        return;
    QString value = ui->tableWidgetInput->item(0, 1)->text();
    tree_->insert(key, value);
    refreshTreeWidget();
}

void MainWindow::on_pushButtonDelete_clicked() {
    bool ok;
    int key = ui->tableWidgetInput->item(0, 0)->text().toInt(&ok);
    if (!ok)
        return;
    tree_->erase(key);
    refreshTreeWidget();
}

void MainWindow::on_pushButtonFind_clicked() {
    bool ok;
    int key = ui->tableWidgetInput->item(0, 0)->text().toInt(&ok);
    if (!ok)
        return;
    auto val = tree_->find(key);
    ui->textEditOutput->setText(val ? *val : "Not found");
}

void MainWindow::on_pushButtonSwapMinMax_clicked() {
    auto minNode = const_cast<decltype(tree_->getRoot())>(findMinNode());
    auto maxNode = const_cast<decltype(tree_->getRoot())>(findMaxNode());


    if (minNode && maxNode) {
        std::swap(minNode->value, maxNode->value);
        refreshTreeWidget();
    }
}

void MainWindow::on_pushButtonTraversals_clicked() {
    std::vector<QString> pre;
    tree_->PreOrderTraversal(
        tree_->getRoot(), *reinterpret_cast<std::vector<std::string>*>(&pre));
    ui->textEditOutput->clear();
    ui->textEditOutput->append("Pre-order:\n");


    for (const auto& s : pre) {
        ui->textEditOutput->append(s);
    }
}

void MainWindow::refreshTreeWidget() {
    ui->treeWidget->clear();
    const auto* root = tree_->getRoot();


    if (root) {
        QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget);
        rootItem->setText(0, QString::number(root->key) + ": " + root->value);
        addNodeItems(rootItem, root);
        ui->treeWidget->addTopLevelItem(rootItem);
    }
    ui->treeWidget->expandAll();
}

void MainWindow::addNodeItems(
    QTreeWidgetItem* parentItem,
    const typename sml::AVLTree<int, QString>::Node* node) {
    if (!node)
        return;


    if (node->left) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem();
        leftItem->setText(
            0, QString::number(node->left->key) + ": " + node->left->value);
        parentItem->addChild(leftItem);
        addNodeItems(leftItem, node->left.get());
    }


    if (node->right) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem();
        rightItem->setText(
            0, QString::number(node->right->key) + ": " + node->right->value);
        parentItem->addChild(rightItem);
        addNodeItems(rightItem, node->right.get());
    }
}

const typename sml::AVLTree<int, QString>::Node* MainWindow::findMinNode()
    const {
    auto node = tree_->getRoot();
    while (node && node->left)
        node = node->left.get();
    return node;
}

const typename sml::AVLTree<int, QString>::Node* MainWindow::findMaxNode()
    const {
    auto node = tree_->getRoot();
    while (node && node->right)
        node = node->right.get();
    return node;
}
