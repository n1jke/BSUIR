#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include "SynchronizedSlicePair.h"

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
    void displaySizes();
    void performFirstSliceOperation();

   private:
    void updateTables();
    void setupUI();
    void setupValidators();

    Ui::MainWindow* ui_;

    SynchronizedSlicePair slicePair_;

    QTableWidget* firstSliceTable_;
    QTableWidget* secondSliceTable_;
    QLineEdit* intValueInput_;
    QLineEdit* intPairValueInput_;
    QLineEdit* doublePairValueInput_;
    QLineEdit* indexInput_;
    QLabel* sizesLabel_;
    QPushButton* performFirstOpButton_;
    QPushButton* clearButton_;
};
#endif	// MAINWINDOW_H
