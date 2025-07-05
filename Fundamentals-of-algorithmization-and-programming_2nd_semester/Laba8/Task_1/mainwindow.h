#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include "tree.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onFindClicked();
    void onTraverseClicked();
    void onLCAClicked();
    void onInsertSubtreeClicked();
    void onRemoveSubtreeClicked();
    void onInsertBranchClicked();
    void onRemoveBranchClicked();
    void onInsertAtPositionClicked();

   private:
    using Node = typename sml::AVLTree<int, QString>::Node;

    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    QLineEdit* valueEdit;
    QTextEdit* resultText;
    QComboBox* traverseTypeCombo;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* findButton;
    QPushButton* traverseButton;
    QPushButton* lcaButton;
    QPushButton* insertSubtreeButton;
    QPushButton* removeSubtreeButton;
    QPushButton* insertBranchButton;
    QPushButton* removeBranchButton;
    QPushButton* insertAtPositionButton;

    sml::AVLTree<int, QString> bst;

    void setupUI();
    void clearScene();
    void drawTree(Node* node, int x, int y, int hGap);
    void updateTreeVisualization();
};

#endif	// MAINWINDOW_H
