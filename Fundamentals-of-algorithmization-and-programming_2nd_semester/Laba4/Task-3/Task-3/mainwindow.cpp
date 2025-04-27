#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      line_edit_(new QLineEdit(this)),
      result_label_(new QLabel(this)),
      calc_button_(new QPushButton("Calc medians", this)) {
    auto* central_widget = new QWidget(this);
    auto* layout = new QVBoxLayout(central_widget);

    auto* validator = new QRegularExpressionValidator(
        QRegularExpression("^\\s*\\d+(\\s*[\\s,]+\\s*\\d+)*\\s*$"), this);
    // template for string with only nums and ','
    line_edit_->setValidator(validator);

    layout->addWidget(line_edit_);
    layout->addWidget(calc_button_);
    layout->addWidget(result_label_);

    setCentralWidget(central_widget);

    connect(calc_button_, &QPushButton::clicked, this,
            &MainWindow::OnCalculateMedian);
}

void MainWindow::OnCalculateMedian() {
    QString input_text = line_edit_->text();
    std::vector<int> sequence = ParseInput(input_text);
    std::vector<int> result = MedianSequence(sequence);

    QString output;


    for (int value : result) {
        output += QString::number(value) + " ";
    }

    result_label_->setText(output.trimmed());
}

std::vector<int> MainWindow::ParseInput(const QString& input) {
    QStringList tokens =
        input.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);
    std::vector<int> result;
    result.reserve(tokens.size());


    for (const QString& token : tokens) {
        result.push_back(token.toInt());
    }
    return result;
}

int MainWindow::min(int a, int b, int c) {
    int min_val = a;


    if (b < min_val) {
        min_val = b;
    }


    if (c < min_val) {
        min_val = c;
    }
    return min_val;
}


int MainWindow::max(int a, int b, int c) {
    int max_val = a;


    if (b > max_val) {
        max_val = b;
    }


    if (c > max_val) {
        max_val = c;
    }
    return max_val;
}


std::vector<int> MainWindow::MedianSequence(std::vector<int>& sequence) {
    std::vector<int> median;
    if (sequence.size() == 0) {
        return median;
    }

    for (size_t i = 0; i <= sequence.size(); i += 3) {


        if (i + 2 < sequence.size()) {
            int temp = sequence[i] + sequence[i + 1] + sequence[i + 2] -
                       max(sequence[i], sequence[i + 1], sequence[i + 2]) -
                       min(sequence[i], sequence[i + 1], sequence[i + 2]);
            median.push_back(temp);
        } else if (i + 1 < sequence.size()) {
            int temp = (sequence[i] + sequence[i + 1]) / 2;
            median.push_back(temp);
        } else {
            median.push_back(sequence[i]);
        }
    }

    return median;
}
