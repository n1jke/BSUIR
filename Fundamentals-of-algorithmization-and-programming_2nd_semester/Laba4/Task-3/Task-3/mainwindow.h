#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

   private slots:
    void OnCalculateMedian();

   private:
    QLineEdit* line_edit_;
    QLabel* result_label_;
    QPushButton* calc_button_;

    std::vector<int> ParseInput(const QString& input);
    std::vector<int> MedianSequence(std::vector<int>& sequence);
    int min(int a, int b, int c);
    int max(int a, int b, int c);
};

#endif	// MAINWINDOW_H_
