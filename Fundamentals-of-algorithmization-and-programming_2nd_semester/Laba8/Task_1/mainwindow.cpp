#include "mainwindow.h"
#include <QFont>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)) {
    setupUI();
    updateTreeVisualization();
}

MainWindow::~MainWindow() {
    delete scene;
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    graphicsView = new QGraphicsView(this);
    graphicsView->setScene(scene);
    graphicsView->setMinimumSize(600, 400);
    mainLayout->addWidget(graphicsView);

    valueEdit = new QLineEdit(this);
    valueEdit->setPlaceholderText("Введите значение/команду");
    mainLayout->addWidget(valueEdit);

    traverseTypeCombo = new QComboBox(this);
    traverseTypeCombo->addItem("In-order");
    traverseTypeCombo->addItem("Pre-order");
    traverseTypeCombo->addItem("Post-order");
    traverseTypeCombo->addItem("Level-order");
    mainLayout->addWidget(traverseTypeCombo);

    QHBoxLayout* buttonLayout1 = new QHBoxLayout();

    addButton = new QPushButton("Добавить узел", this);
    addButton->setStyleSheet("background-color: #4CAF50; color: white;");
    buttonLayout1->addWidget(addButton);

    removeButton = new QPushButton("Удалить узел", this);
    removeButton->setStyleSheet("background-color: #f44336; color: white;");
    buttonLayout1->addWidget(removeButton);

    findButton = new QPushButton("Найти узел", this);
    findButton->setStyleSheet("background-color: #2196F3; color: white;");
    buttonLayout1->addWidget(findButton);

    traverseButton = new QPushButton("Обход дерева", this);
    traverseButton->setStyleSheet("background-color: #FF9800; color: white;");
    buttonLayout1->addWidget(traverseButton);

    mainLayout->addLayout(buttonLayout1);

    QHBoxLayout* buttonLayout2 = new QHBoxLayout();

    lcaButton = new QPushButton("Найти LCA", this);
    lcaButton->setStyleSheet("background-color: #9C27B0; color: white;");
    buttonLayout2->addWidget(lcaButton);

    insertSubtreeButton = new QPushButton("Вставить поддерево", this);
    insertSubtreeButton->setStyleSheet(
        "background-color: #607D8B; color: white;");
    buttonLayout2->addWidget(insertSubtreeButton);

    removeSubtreeButton = new QPushButton("Удалить поддерево", this);
    removeSubtreeButton->setStyleSheet(
        "background-color: #E91E63; color: white;");
    buttonLayout2->addWidget(removeSubtreeButton);

    mainLayout->addLayout(buttonLayout2);

    QHBoxLayout* buttonLayout3 = new QHBoxLayout();

    insertBranchButton = new QPushButton("Вставить ветвь", this);
    insertBranchButton->setStyleSheet(
        "background-color: #795548; color: white;");
    buttonLayout3->addWidget(insertBranchButton);

    removeBranchButton = new QPushButton("Удалить ветвь", this);
    removeBranchButton->setStyleSheet(
        "background-color: #FF5722; color: white;");
    buttonLayout3->addWidget(removeBranchButton);

    insertAtPositionButton = new QPushButton("Вставить в позицию", this);
    insertAtPositionButton->setStyleSheet(
        "background-color: #00BCD4; color: white;");
    buttonLayout3->addWidget(insertAtPositionButton);

    mainLayout->addLayout(buttonLayout3);

    resultText = new QTextEdit(this);
    resultText->setPlaceholderText("Результаты операций...");
    resultText->setReadOnly(true);
    mainLayout->addWidget(resultText);

    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton, &QPushButton::clicked, this,
            &MainWindow::onRemoveClicked);
    connect(findButton, &QPushButton::clicked, this,
            &MainWindow::onFindClicked);
    connect(traverseButton, &QPushButton::clicked, this,
            &MainWindow::onTraverseClicked);
    connect(lcaButton, &QPushButton::clicked, this, &MainWindow::onLCAClicked);
    connect(insertSubtreeButton, &QPushButton::clicked, this,
            &MainWindow::onInsertSubtreeClicked);
    connect(removeSubtreeButton, &QPushButton::clicked, this,
            &MainWindow::onRemoveSubtreeClicked);
    connect(insertBranchButton, &QPushButton::clicked, this,
            &MainWindow::onInsertBranchClicked);
    connect(removeBranchButton, &QPushButton::clicked, this,
            &MainWindow::onRemoveBranchClicked);
    connect(insertAtPositionButton, &QPushButton::clicked, this,
            &MainWindow::onInsertAtPositionClicked);
}

void MainWindow::clearScene() {
    scene->clear();
}

void MainWindow::drawTree(Node* node, int x, int y, int hGap) {
    if (!node)
        return;

    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 15, y - 15, 30, 30);
    ellipse->setBrush(QBrush(Qt::lightGray));

    QGraphicsTextItem* text = scene->addText(QString::number(node->key));
    text->setDefaultTextColor(Qt::black);
    text->setPos(x - text->boundingRect().width() / 2,
                 y - text->boundingRect().height() / 2);


    if (node->left) {
        scene->addLine(x, y + 15, x - hGap, y + 50, QPen(Qt::black));
        drawTree(node->left.get(), x - hGap, y + 50, hGap / 2);
    }


    if (node->right) {
        scene->addLine(x, y + 15, x + hGap, y + 50, QPen(Qt::black));
        drawTree(node->right.get(), x + hGap, y + 50, hGap / 2);
    }
}

void MainWindow::updateTreeVisualization() {
    clearScene();
    if (bst.getRoot()) {
        drawTree(bst.getRoot(), graphicsView->width() / 2, 50,
                 graphicsView->width() / 4);
    }
}

void MainWindow::onAddClicked() {
    bool ok;
    int key = valueEdit->text().toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число");
        return;
    }
    // Два аргумента: key и строковое значение
    bst.add(key, valueEdit->text());
    updateTreeVisualization();
    resultText->setText(QString("Узел %1 добавлен").arg(key));
}


void MainWindow::onRemoveClicked() {
    bool ok;
    int key = valueEdit->text().toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число");
        return;
    }
    bst.remove(key);
    updateTreeVisualization();
    resultText->setText(QString("Узел %1 удалён").arg(key));
}


void MainWindow::onFindClicked() {
    bool ok;
    int key = valueEdit->text().toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число");
        return;
    }
    resultText->setText(bst.contains(key)
                            ? QString("Узел %1 найден").arg(key)
                            : QString("Узел %1 не найден").arg(key));
}

void MainWindow::onTraverseClicked() {
    auto type = static_cast<decltype(bst)::TraversalType>(
        traverseTypeCombo->currentIndex());
    QString out = bst.traverse(type);
    resultText->setText(QString("Обход (%1): %2")
                            .arg(traverseTypeCombo->currentText())
                            .arg(out));
}

void MainWindow::onLCAClicked() {
    auto parts = valueEdit->text().split(' ', Qt::SkipEmptyParts);
    if (parts.size() != 2) {
        QMessageBox::warning(this, "Ошибка", "Введите два числа через пробел");
        return;
    }
    bool ok1, ok2;
    int a = parts[0].toInt(&ok1), b = parts[1].toInt(&ok2);


    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка", "Неверные числа");
        return;
    }
    int lca = bst.findLCA(a, b);
    resultText->setText(
        (lca || lca == 0)
            ? QString("LCA для %1 и %2: %3").arg(a).arg(b).arg(lca)
            : QString("Общий предок не найден"));
}

void MainWindow::onInsertSubtreeClicked() {
    auto parts = valueEdit->text().split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 3) {
        QMessageBox::warning(this, "Ошибка",
                             "Формат: <parent> <L/R> <значения...>");
        return;
    }
    bool ok;
    int parent = parts[0].toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный parent");
        return;
    }
    bool isLeft = parts[1].toUpper() == "L";

    sml::AVLTree<int, QString> subtree;
    for (int i = 2; i < parts.size(); ++i) {
        int v = parts[i].toInt(&ok);


        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Неверное значение");
            return;
        }
        subtree.add(v, parts[i]);
    }
    bst.insertSubtree(parent, isLeft, subtree);
    updateTreeVisualization();
    resultText->setText(QString("Поддерево вставлено в %1 стороны узла %2")
                            .arg(isLeft ? "L" : "R")
                            .arg(parent));
}

void MainWindow::onRemoveSubtreeClicked() {
    bool ok;
    int rootV = valueEdit->text().toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите число");
        return;
    }
    bst.removeSubtree(rootV);
    updateTreeVisualization();
    resultText->setText(QString("Поддерево с корнем %1 удалено").arg(rootV));
}

void MainWindow::onInsertBranchClicked() {
    auto parts = valueEdit->text().split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 3) {
        QMessageBox::warning(this, "Ошибка",
                             "Формат: <parent> <L/R> <значения...>");
        return;
    }
    bool ok;
    int parent = parts[0].toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный parent");
        return;
    }
    bool isLeft = parts[1].toUpper() == "L";
    sml::AVLTree<int, QString> branch;
    for (int i = 2; i < parts.size(); ++i) {
        int v = parts[i].toInt(&ok);


        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Неверное значение");
            return;
        }
        branch.add(v, parts[i]);
    }
    bst.insertBranch(parent, isLeft, branch);
    updateTreeVisualization();
    resultText->setText(QString("Ветвь вставлена в %1 стороны узла %2")
                            .arg(isLeft ? "L" : "R")
                            .arg(parent));
}

void MainWindow::onRemoveBranchClicked() {
    auto parts = valueEdit->text().split(' ', Qt::SkipEmptyParts);
    if (parts.size() != 2) {
        QMessageBox::warning(this, "Ошибка", "Формат: <parent> <L/R>");
        return;
    }
    bool ok;
    int parent = parts[0].toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный parent");
        return;
    }
    bool isLeft = parts[1].toUpper() == "L";
    bst.removeBranch(parent, isLeft);
    updateTreeVisualization();
    resultText->setText(QString("Ветвь %1 узла %2 удалена")
                            .arg(isLeft ? "L" : "R")
                            .arg(parent));
}

void MainWindow::onInsertAtPositionClicked() {
    auto parts = valueEdit->text().split(' ', Qt::SkipEmptyParts);
    if (parts.size() != 3) {
        QMessageBox::warning(this, "Ошибка", "Формат: <parent> <L/R> <value>");
        return;
    }
    bool ok;
    int parent = parts[0].toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный parent");
        return;
    }
    bool isLeft = parts[1].toUpper() == "L";
    int v = parts[2].toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверное значение");
        return;
    }
    bst.insertAtPosition(parent, isLeft, v, parts[2]);
    updateTreeVisualization();
    resultText->setText(QString("Узел %1 вставлен в %2 стороны узла %3")
                            .arg(v)
                            .arg(isLeft ? "L" : "R")
                            .arg(parent));
}
