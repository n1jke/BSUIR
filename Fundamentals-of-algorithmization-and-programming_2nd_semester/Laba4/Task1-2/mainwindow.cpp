#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <functional>
#include "sortings.h"

// const for array sizes
const int kMaxArraySizeAnimated = 150;
const int kMaxArraySizeNoAnimation = 10000;
const int kDefaultArraySize = 20;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    SetupUI();
}

MainWindow::~MainWindow() {
    // scene_ deleted when graphicsView_ deleted
}

void MainWindow::SetupUI() {
    // central widget and layout
    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    const int mheight = 400;
    // create graph view
    graphicsView_ = new QGraphicsView(central_widget);
    graphicsView_->setMinimumHeight(mheight);
    scene_ = new QGraphicsScene(this);
    graphicsView_->setScene(scene_);
    graphicsView_->setRenderHint(QPainter::Antialiasing);
    graphicsView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    main_layout->addWidget(graphicsView_);

    // controls layout
    QHBoxLayout* controls_layout = new QHBoxLayout();
    main_layout->addLayout(controls_layout);

    // size spinbox
    arraySizeSpinBox_ = new QSpinBox(central_widget);
    arraySizeSpinBox_->setMinimum(1);
    arraySizeSpinBox_->setMaximum(kMaxArraySizeNoAnimation);
    arraySizeSpinBox_->setValue(kDefaultArraySize);
    controls_layout->addWidget(arraySizeSpinBox_);

    // generate button
    generateButton_ = new QPushButton("Generate Array", central_widget);
    controls_layout->addWidget(generateButton_);

    // algorithm combo box
    algorithmComboBox_ = new QComboBox(central_widget);
    algorithmComboBox_->addItem("Heap Sort");
    algorithmComboBox_->addItem("Quick Sort");
    algorithmComboBox_->addItem("Merge Sort");
    algorithmComboBox_->addItem("Interpolation Sort");
    controls_layout->addWidget(algorithmComboBox_);

    // animation checkbox
    animationCheckBox_ = new QCheckBox("Enable Animation", central_widget);
    animationCheckBox_->setChecked(false);
    controls_layout->addWidget(animationCheckBox_);

    // start
    startButton_ = new QPushButton("Start Sorting", central_widget);
    controls_layout->addWidget(startButton_);

    // revert
    revertButton_ = new QPushButton("Revert to Unsorted", central_widget);
    controls_layout->addWidget(revertButton_);

    // search
    searchButton_ = new QPushButton("Search Element", central_widget);
    controls_layout->addWidget(searchButton_);

    // time
    timeLabel_ = new QLabel("Time: 0 ms", central_widget);
    timeLabel_->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(timeLabel_);

    // initial val
    arrsize_ = arraySizeSpinBox_->value();
    curr_algorithm_ = 0;
    is_sorted_ = false;

    // connect signal
    connect(generateButton_, &QPushButton::clicked, this,
            &MainWindow::GenerateArr);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::StartSort);
    connect(revertButton_, &QPushButton::clicked, this,
            &MainWindow::RevertToUnsorted);
    connect(searchButton_, &QPushButton::clicked, this,
            &MainWindow::PerformSearchAndPower);
    connect(animationCheckBox_, &QCheckBox::stateChanged, this,
            &MainWindow::UpdateArraySizeLimit);

    // initial state
    UpdateUiForSortState(false);

    // resize window
    const int length = 1200;
    const int height = 600;
    resize(length, height);
}

void MainWindow::GenerateArr() {
    arrsize_ = arraySizeSpinBox_->value();

    // clearing
    array_.clear();
    original_array_.clear();
    scene_->clear();
    rect_items_.clear();

    const int max = 1000;


    for (int i = 0; i < arrsize_; ++i) {
        array_.push_back(QRandomGenerator::global()->bounded(0, max));
    }
    original_array_ = array_;

    CreateRectang();  // visualization

    UpdateUiForSortState(false);  // reset to unsorted
    timeLabel_->setText("Time: 0 ms");
}

void MainWindow::CreateRectang() {
    if (array_.empty()) {
        return;
    }

    scene_->clear();
    rect_items_.clear();

    const int spacing = 5;
    // calc parameters for rect
    const int rect_width = 5;
    const int scene_width = arrsize_ * (rect_width + spacing);

    // ensure height calculation
    int view_height = graphicsView_->height();
    const int scene_height = (view_height > 20) ? view_height - 20 : 400;

    long long max_value = 1;  // avoid div by zero
    if (!array_.empty()) {
        max_value = *std::max_element(array_.begin(), array_.end());


        if (max_value == 0) {
            max_value = 1;
        }
    }

    const double height_scale =
        (scene_height - 50) / static_cast<double>(max_value);
    scene_->setSceneRect(0, 0, scene_width, scene_height);

    const int max_color_val = 255;


    for (int i = 0; i < arrsize_; ++i) {
        int rect_height = static_cast<int>(array_[i] * height_scale);
        if (rect_height < 1) {
            rect_height = 1;  // ensure min height
        }

        QGraphicsRectItem* rect = scene_->addRect(
            i * (rect_width + spacing), scene_height - rect_height, rect_width,
            rect_height, QPen(Qt::black),
            QBrush(is_sorted_ ? QColor(0, 0, max_color_val)	  // blue - sorted
                              : QColor(max_color_val, 0, 0))  // red - unsorted
        );
        rect_items_.push_back(rect);
    }
}

void MainWindow::StartSort() {
    curr_algorithm_ = algorithmComboBox_->currentIndex();
    bool animate = animationCheckBox_->isChecked();

    // disable controls sort time
    startButton_->setEnabled(false);
    generateButton_->setEnabled(false);
    revertButton_->setEnabled(false);
    searchButton_->setEnabled(false);
    algorithmComboBox_->setEnabled(false);
    arraySizeSpinBox_->setEnabled(false);
    animationCheckBox_->setEnabled(false);

    qint64 total_time = 0;
    double average_time = 0.0;
    const int iterations = 10;	// for non-animated timing


    if (animate) {
        // --- Animated Sort ---
        const int spacing = 5;
        const int rect_width = 5;

        auto on_swap = [&](int index1, int index2) {
            if (index1 >= 0 &&
                static_cast<size_t>(index1) < rect_items_.size() &&
                index2 >= 0 &&
                static_cast<size_t>(index2) < rect_items_.size()) {
                std::swap(rect_items_[index1], rect_items_[index2]);
                qreal x1 = index1 * (rect_width + spacing);
                qreal x2 = index2 * (rect_width + spacing);
                rect_items_[index1]->setX(x1);
                rect_items_[index2]->setX(x2);
                QApplication::processEvents();
            }
        };

        sorting_timer_.start();
        switch (curr_algorithm_) {
            case 0:	 // heap sort
                Sortings::heapSort(array_, on_swap);
                break;
            case 1:	 // quick sort
                Sortings::quickSort(array_, 0, array_.size() - 1, on_swap);
                break;
            case 2:	 // merge sort
                Sortings::mergeSort(array_, 0, array_.size() - 1, on_swap);
                break;
            case 3:	 // interpolation sort
                Sortings::interpolationSort(array_, 0, array_.size() - 1,
                                            on_swap);
                break;
        }
        total_time = sorting_timer_.elapsed();
        timeLabel_->setText(QString("Time: %1 ms").arg(total_time));

    } else {
        // --- Non-Animated Sort ---
        std::vector<long long> temp_array = array_;
        sorting_timer_.start();
        for (int i = 0; i < iterations; ++i) {
            temp_array = array_;  // refresh array before iteration
            switch (curr_algorithm_) {
                case 0:
                    Sortings::heapSort(temp_array, nullptr);
                    break;
                case 1:
                    Sortings::quickSort(temp_array, 0, temp_array.size() - 1,
                                        nullptr);
                    break;
                case 2:
                    Sortings::mergeSort(temp_array, 0, temp_array.size() - 1,
                                        nullptr);
                    break;
                case 3:
                    Sortings::interpolationSort(temp_array, 0,
                                                temp_array.size() - 1, nullptr);
                    break;
            }
        }
        total_time = sorting_timer_.elapsed();
        average_time = static_cast<double>(total_time) / iterations;

        // sort the actual array once for display
        switch (curr_algorithm_) {
            case 0:
                Sortings::heapSort(array_, nullptr);
                break;
            case 1:
                Sortings::quickSort(array_, 0, array_.size() - 1, nullptr);
                break;
            case 2:
                Sortings::mergeSort(array_, 0, array_.size() - 1, nullptr);
                break;
            case 3:
                Sortings::interpolationSort(array_, 0, array_.size() - 1,
                                            nullptr);
                break;
        }

        timeLabel_->setText(
            QString("Avg time: %1 ms").arg(average_time, 0, 'f', 3));
    }

    UpdateUiForSortState(true);
    CreateRectang();  // final redraw with sorted colors
}

void MainWindow::RevertToUnsorted() {


    if (!is_sorted_ && array_ == original_array_) {	 // avoid unnecessary
        return;
    }

    array_ = original_array_;  // restore original

    UpdateUiForSortState(false);
    timeLabel_->setText("Time: 0 ms");
    CreateRectang();
}

void MainWindow::PerformSearchAndPower() {


    if (!is_sorted_) {
        QMessageBox::warning(this, "Search Error", "Array is not sorted yet.");
        return;
    }
    if (array_.empty()) {
        QMessageBox::warning(this, "Search Error", "Array is empty.");
        return;
    }

    const int max = -2147483647;
    const int min = 2147483647;
    bool ok;
    long long num_to_search = QInputDialog::getInt(
        this, "Binary Search", "Enter number to search:", 0, min, max, 1, &ok);


    if (ok) {
        long long index = Sortings::binSearch(array_, num_to_search);

        if (index != -1) {
            // found
            long long array_size_mod = array_.size();
            if (array_size_mod == 0)
                array_size_mod = 1;	 // avoid devide zero

            long long modulus = array_size_mod;	 // using array size as mod
            long long power_result =
                Sortings::binPow(index, array_.size(), modulus);

            QMessageBox::information(this, "Search Result",
                                     QString("Number %1 found at index: %2.\n"
                                             "Index ^ ArraySize (mod %3) = %4")
                                         .arg(num_to_search)
                                         .arg(index)
                                         .arg(modulus)
                                         .arg(power_result));
        } else {
            // not found
            QMessageBox::information(
                this, "Search Result",
                QString("Number %1 not found in the array.")
                    .arg(num_to_search));
        }
    }
}

void MainWindow::UpdateArraySizeLimit() {
    bool animated = animationCheckBox_->isChecked();
    int max_size = animated ? kMaxArraySizeAnimated : kMaxArraySizeNoAnimation;
    arraySizeSpinBox_->setRange(1, max_size);

    // if current value exceeds new max, reset it
    if (arraySizeSpinBox_->value() > max_size) {
        arraySizeSpinBox_->setValue(max_size);
    }
}

void MainWindow::UpdateUiForSortState(bool sorting_finished) {
    is_sorted_ = sorting_finished;
    startButton_->setEnabled(!sorting_finished && !array_.empty());
    generateButton_->setEnabled(true);
    revertButton_->setEnabled(sorting_finished);
    searchButton_->setEnabled(sorting_finished);
    algorithmComboBox_->setEnabled(!sorting_finished);
    arraySizeSpinBox_->setEnabled(!sorting_finished);
    animationCheckBox_->setEnabled(!sorting_finished);
}
