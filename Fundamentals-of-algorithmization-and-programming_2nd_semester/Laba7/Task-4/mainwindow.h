#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

#include "ui_mainwindow.h"
#include "unordered_map.h"

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
    void on_runButton_clicked();
    void on_resetButton_clicked();
    void updateStatsTable();
    void updateSummary();

   private:
    Ui::MainWindow* ui;
    using KeyType = int;
    using ValueType = int;
    std::unique_ptr<sml::unordered_map<KeyType, ValueType, std::hash<KeyType>,
                                       std::equal_to<KeyType>,
                                       ProbingStrategy::kDoubleHashing>>
        hashTable_;
    std::unique_ptr<sml::unordered_map<KeyType, ValueType, sml::UniversalHash,
                                       std::equal_to<KeyType>,
                                       ProbingStrategy::kDoubleHashing>>
        universalHashTable_;
    template <typename StatsType>


    void fillStatsTable(const StatsType& stats) {
        int n = static_cast<int>(stats.collision_hashes.size());
        ui->statsTableWidget->setRowCount(n);
        for (int i = 0; i < n; ++i) {
            QTableWidgetItem* num_item =
                new QTableWidgetItem(QString::number(i + 1));
            QTableWidgetItem* hash_item = new QTableWidgetItem(
                QString::number(stats.collision_hashes[i]));
            QTableWidgetItem* probe_item = new QTableWidgetItem(
                i < static_cast<int>(stats.probe_counts.size())
                    ? QString::number(stats.probe_counts[i])
                    : "");
            ui->statsTableWidget->setItem(i, 0, num_item);
            ui->statsTableWidget->setItem(i, 1, hash_item);
            ui->statsTableWidget->setItem(i, 2, probe_item);
        }
        ui->statsTableWidget->horizontalHeader()->setSectionResizeMode(
            QHeaderView::Stretch);
    }
    void applyDarkTheme();
};
#endif	// MAINWINDOW_H
