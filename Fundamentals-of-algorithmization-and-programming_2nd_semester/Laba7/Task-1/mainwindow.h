#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "doublelinkedlist.h"

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
    void onPushFront();
    void onPushBack();
    void onPopFront();
    void onPopBack();
    void onClear();
    void onSwapMinMax();
    void onFindValue();

   private:
    Ui::MainWindow* ui_;
    DoubleLinkedList<int> list_;

    QGraphicsScene* scene_;
    QLabel* statusLabel_;

    const int NODE_RADIUS_ = 30;
    const int NODE_SPACING_ = 100;
    const int MAX_NODES_ = 10;

    void updateScene();
    void drawNode(int x, int y, int value, const QString& addr);
    void drawArrow(int x1, int y1, int x2, int y2, QColor color);
};

#endif	// MAINWINDOW_H
