#include "mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QVBoxLayout>

const int kWindowLenght = 400;
const int kWindowHeight = 300;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    auto* layout = new QVBoxLayout(central_widget);

    pathLineEdit_ = new QLineEdit(this);
    pathLineEdit_->setReadOnly(true);
    pathLineEdit_->setPlaceholderText("Path to folder.");

    selectButton_ = new QPushButton("Choose folder:", this);

    resultTextEdit_ = new QTextEdit(this);
    resultTextEdit_->setReadOnly(true);

    layout->addWidget(pathLineEdit_);
    layout->addWidget(selectButton_);
    layout->addWidget(resultTextEdit_);

    connect(selectButton_, &QPushButton::clicked, this, &MainWindow::selectDir);

    setMinimumSize(kWindowLenght, kWindowHeight);
}

MainWindow::~MainWindow() {}

int MainWindow::dfsForFolders(int& subFolders, int& files, int& tempDepth,
                              const QString& filePath) {
    QDir dir(filePath);
    if (!dir.exists()) {
        return tempDepth;
    }

    QFileInfoList enrties =
        dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    int max_depth = tempDepth;


    for (const auto& entry : enrties) {
        if (entry.isDir()) {
            ++subFolders;
            ++tempDepth;
            max_depth = std::max(dfsForFolders(subFolders, files, tempDepth,
                                               entry.absoluteFilePath()),
                                 max_depth);
            --tempDepth;
        } else {
            ++files;
        }
    }
    return max_depth;
}

void MainWindow::selectDir() {
    QString dir_path =
        QFileDialog::getExistingDirectory(this, "Choose folder", "");
    if (!dir_path.isEmpty()) {
        pathLineEdit_->setText(dir_path);

        int sub_folders = 0;
        int files = 0;
        int temp_depth = 0;
        int max_depth = dfsForFolders(sub_folders, files, temp_depth, dir_path);

        QString result =
            QString("Sub-folders: %1\n Files: %2\n Max folders depth: %3")
                .arg(sub_folders)
                .arg(files)
                .arg(max_depth);
        resultTextEdit_->setText(result);
    }
}
