#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include "date.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:

    void onOpenfilebuttonClicked();

    void onClosefilebuttonClicked();

    void onCreatefilebuttonClicked();

    void onAdddateClicked();

    void onBirthdayClicked();

    void onDatechangeClicked();

   private:
    QVector<Date> days_;
    int index_;
    QString pathToFile_;
    QFile file_;
    Date* dateline_;

    void updateTable();
    void addDate(const QString& date);
    bool checkstr(const QString& date);	 // check string format dd.mm.yyyy
    void FromFiletoarr();
    void EditFile(int index, const QString& edit);

    Ui::MainWindow* ui_;
};
#endif	// MAINWINDOW_H
