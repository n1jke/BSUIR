#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QCheckBox>
#include <QComboBox>
#include <QElapsedTimer>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

   private slots:
    void GenerateArr();
    void StartSort();
    void RevertToUnsorted();
    void PerformSearchAndPower();
    void UpdateArraySizeLimit();

   private:
    void SetupUI();
    void CreateRectang();
    void UpdateUiForSortState(bool sorting_finished);

    // UI components
    QGraphicsView* graphicsView_;
    QGraphicsScene* scene_;
    QSpinBox* arraySizeSpinBox_;
    QPushButton* generateButton_;
    QComboBox* algorithmComboBox_;
    QPushButton* startButton_;
    QPushButton* revertButton_;
    QPushButton* searchButton_;
    QCheckBox* animationCheckBox_;
    QLabel* timeLabel_;

    // data
    QElapsedTimer sorting_timer_;
    std::vector<long long> array_;
    std::vector<long long> original_array_;
    std::vector<QGraphicsRectItem*> rect_items_;

    long long arrsize_;
    long long curr_algorithm_;
    bool is_sorted_;
};

#endif	// MAINWINDOW_H_
