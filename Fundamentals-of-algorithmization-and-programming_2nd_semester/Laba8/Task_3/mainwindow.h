#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "map.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

   private slots:
    void onInsert();
    void onErase();
    void onClear();

   private:
    void drawTree();
    void drawNode(sml::map<int, int>::Node* node, int depth, int xMin,
                  int xMax);

    QGraphicsScene* _scene;
    QLineEdit* _inputKey;
    QPushButton* _btnInsert;
    QPushButton* _btnErase;
    QPushButton* _btnClear;
    QGraphicsView* _view;

    sml::map<int, int> _tree;
};
