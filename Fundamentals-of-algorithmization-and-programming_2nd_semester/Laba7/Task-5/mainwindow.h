#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QMainWindow>
#include "deque.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QTimer;

class DequeModel : public QAbstractTableModel {
    Q_OBJECT

   private:
    sml::Deque<int>& deque_;

   public:
    DequeModel(sml::Deque<int>& deque, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void updateView();
};

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void on_pushButton_pushFront_clicked();
    void on_pushButton_pushBack_clicked();
    void on_pushButton_popFront_clicked();
    void on_pushButton_popBack_clicked();
    void on_pushButton_clear_clicked();
    void enableButtons();

   private:
    Ui::MainWindow* ui_;
    sml::Deque<int> deque_;
    DequeModel* dequeModel_;
    // double click problem,
    QTimer* buttonCooldownTimer_;
    bool buttonsEnabled_;

    void updateDequeView();
    void setupButtonConnections();
    void disconnectButtons();
    void disableButtons();
};

#endif	// MAINWINDOW_H
