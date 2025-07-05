#include "mainwindow.h"
#include <QHeaderView>
#include <QPalette>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <QTableWidget>
#include <memory>
#include <numeric>
#include <unordered_set>
#include <vector>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    applyDarkTheme();
    connect(ui->runButton, &QPushButton::clicked, this,
            &MainWindow::on_runButton_clicked);
    connect(ui->resetButton, &QPushButton::clicked, this,
            &MainWindow::on_resetButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::applyDarkTheme() {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}

void MainWindow::on_runButton_clicked() {
    int size = ui->sizeComboBox->currentText().toInt();
    QString hash_type = ui->hashComboBox->currentText();
    QString probing_type = ui->probingComboBox->currentText();

    int num_keys = static_cast<int>(size * 0.7);
    std::unordered_set<KeyType> unique_keys;
    QRandomGenerator rng(QRandomGenerator::global()->generate());
    while (static_cast<int>(unique_keys.size()) < num_keys) {
        unique_keys.insert(rng.bounded(1, size * 100));
    }
    std::vector<KeyType> keys(unique_keys.begin(), unique_keys.end());


    if (hash_type == "Modular") {
        hashTable_.reset(
            new sml::unordered_map<KeyType, ValueType, std::hash<KeyType>,
                                   std::equal_to<KeyType>,
                                   ProbingStrategy::kDoubleHashing>(size));
        for (const auto& k : keys) {
            hashTable_->insert(k, k);
        }
        updateStatsTable();
        updateSummary();
    } else {
        sml::UniversalHash uh(size);
        universalHashTable_.reset(
            new sml::unordered_map<KeyType, ValueType, sml::UniversalHash,
                                   std::equal_to<KeyType>,
                                   ProbingStrategy::kDoubleHashing>(size, uh));
        for (const auto& k : keys) {
            universalHashTable_->insert(k, k);
        }
        updateStatsTable();
        updateSummary();
    }
}

void MainWindow::on_resetButton_clicked() {

    

    if (hashTable_) {
        hashTable_->reset_stats();
    }


    if (universalHashTable_) {
        universalHashTable_->reset_stats();
    }
    ui->statsTableWidget->clearContents();
    ui->statsTableWidget->setRowCount(0);
    ui->summaryLabel->setText("Statistics summary will appear here.");
}

void MainWindow::updateStatsTable() {
    QString hash_type = ui->hashComboBox->currentText();


    if (hash_type == "Modular" && hashTable_) {
        fillStatsTable(hashTable_->get_stats());
    } else if (hash_type == "Universal" && universalHashTable_) {
        fillStatsTable(universalHashTable_->get_stats());
    }
}

void MainWindow::updateSummary() {
    QString hash_type = ui->hashComboBox->currentText();


    if (hash_type == "Modular" && hashTable_) {
        const auto& s = hashTable_->get_stats();
        double avg_probes = 0;
        if (!s.probe_counts.empty()) {
            avg_probes = std::accumulate(s.probe_counts.begin(),
                                        s.probe_counts.end(), 0.0) /
                        s.probe_counts.size();
        }
        double avg_search = 0;
        if (!s.search_times.empty()) {
            avg_search = std::accumulate(s.search_times.begin(),
                                        s.search_times.end(), 0.0) /
                        s.search_times.size();
        }
        QString summary = QString(
                              "Кол-во коллизий: %1\nСреднее число проб: "
                              "%2\nСреднее время поиска: %3 мкс")
                              .arg(s.collisions)
                              .arg(QString::number(avg_probes, 'f', 2))
                              .arg(QString::number(avg_search, 'f', 2));
        ui->summaryLabel->setText(summary);
    } else if (hash_type == "Universal" && universalHashTable_) {
        const auto& s = universalHashTable_->get_stats();
        double avg_probes = 0;
        if (!s.probe_counts.empty()) {
            avg_probes = std::accumulate(s.probe_counts.begin(),
                                        s.probe_counts.end(), 0.0) /
                        s.probe_counts.size();
        }
        double avg_search = 0;
        if (!s.search_times.empty()) {
            avg_search = std::accumulate(s.search_times.begin(),
                                        s.search_times.end(), 0.0) /
                        s.search_times.size();
        }
        QString summary = QString(
                              "Кол-во коллизий: %1\nСреднее число проб: "
                              "%2\nСреднее время поиска: %3 мкс")
                              .arg(s.collisions)
                              .arg(QString::number(avg_probes, 'f', 2))
                              .arg(QString::number(avg_search, 'f', 2));
        ui->summaryLabel->setText(summary);
    } else {
        ui->summaryLabel->setText("Statistics summary will appear here.");
    }
}
