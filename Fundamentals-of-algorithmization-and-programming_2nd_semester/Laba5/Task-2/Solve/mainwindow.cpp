#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QMessageBox>
#include "stringg.h"

// Constructor
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    // --- init UI Setup ---

    // Set reasonable ranges/defaults for SpinBoxes
    const int max_reasonable_size = 1024;  // Avoid huge allocations
    ui_->spinBoxMemcpyN->setRange(0, max_reasonable_size);
    ui_->spinBoxMemmoveN->setRange(0, max_reasonable_size);
    ui_->spinBoxMemsetN->setRange(0, max_reasonable_size);
    ui_->spinBoxMemsetChar->setRange(std::numeric_limits<unsigned char>::min(),
                                     std::numeric_limits<unsigned char>::max());
    ui_->spinBoxStrncpyN->setRange(0, max_reasonable_size);
    ui_->spinBoxStrncatN->setRange(0, max_reasonable_size);
    ui_->spinBoxMemcmpN->setRange(0, max_reasonable_size);
    ui_->spinBoxStrncmpN->setRange(0, max_reasonable_size);

    const int ten = 10;
    const int nine = 9;
    const int six = 6;
    const int five = 5;
    const int four = 4;
    // init example value
    ui_->lineEditMemcpySrc->setText("Hello World");
    ui_->spinBoxMemcpyN->setValue(five);
    ui_->lineEditMemmoveSrc->setText("abcdefghi");
    ui_->spinBoxMemmoveN->setValue(four);
    ui_->spinBoxMemsetChar->setValue(int('*'));
    ui_->spinBoxMemsetN->setValue(ten);
    ui_->lineEditStrcpySrc->setText("Copy This");
    ui_->lineEditStrncpySrc->setText("Copy Only Part");
    ui_->spinBoxStrncpyN->setValue(nine);
    ui_->lineEditStrcatDest->setText("First ");
    ui_->lineEditStrcatSrc->setText("Second");
    ui_->lineEditStrncatDest->setText("FirstN ");
    ui_->lineEditStrncatSrc->setText("SecondLimited");
    ui_->spinBoxStrncatN->setValue(six);
    ui_->lineEditMemcmpS1->setText("abcde");
    ui_->lineEditMemcmpS2->setText("abCde");
    ui_->spinBoxMemcmpN->setValue(five);
    ui_->lineEditStrcmpS1->setText("Test");
    ui_->lineEditStrcmpS2->setText("Test");
    ui_->lineEditStrcollS1->setText("apple");
    ui_->lineEditStrcollS2->setText("banana");
    ui_->lineEditStrncmpS1->setText("String1");
    ui_->lineEditStrncmpS2->setText("String2");
    ui_->spinBoxStrncmpN->setValue(six);
}

MainWindow::~MainWindow() {
    delete ui_;
}

// Helper to show errors
void MainWindow::showError(const QString& message) {
    QMessageBox::critical(this, "Library Error", message);
}

// --- slot implement ---

// --- memory Tab ---
void MainWindow::onBtnMemcpyClicked() {
    try {
        QByteArray src_bytes = ui_->lineEditMemcpySrc->text().toUtf8();
        const char* src = src_bytes.constData();
        size_t n = static_cast<size_t>(ui_->spinBoxMemcpyN->value());


        if (n == 0) {
            ui_->lineEditMemcpyDest->setText("(empty result for n=0)");
            return;
        }

        // allocate destination buffer
        std::vector<char> dest_buffer(n + 1,
                                      '\0');  // init with nulls for saferui_ui_
        sml::stringg::memcpy_sml(dest_buffer.data(), src, n);

        // display result
        ui_->lineEditMemcpyDest->setText(
            QString::fromUtf8(dest_buffer.data(), n));

    } catch (...) {
        showError("unknown error occurred in memcpy_sml.");
    }
}

void MainWindow::onBtnMemmoveClicked() {
    try {
        //memmove, source and dest can overlap
        std::string original_str =
            ui_->lineEditMemmoveSrc->text().toStdString();
        size_t n = static_cast<size_t>(ui_->spinBoxMemmoveN->value());

        if (n == 0 || original_str.empty()) {
            ui_->lineEditMemmoveDest->setText(
                QString::fromStdString(original_str));
            return;
        }

        // buffer with the init string data
        std::vector<char> buffer(original_str.begin(), original_str.end());
        buffer.push_back('\0');


        size_t dest_offset = 0;
        size_t src_offset = 2;

        if (src_offset + n > buffer.size() - 1 ||
            dest_offset + n > buffer.size() - 1) {
            showError(
                "Source or destination range (with n) exceeds buffer bounds "
                "for demo.");
            return;
        }

        char* dest_ptr = buffer.data() + dest_offset;
        const char* src_ptr = buffer.data() + src_offset;

        sml::stringg::memmove_sml(dest_ptr, src_ptr, n);

        // display the modified
        ui_->lineEditMemmoveDest->setText(QString::fromUtf8(buffer.data()));

    } catch (...) {
        showError("unknown error occurred in memmove_sml.");
    }
}

void MainWindow::onBtnMemsetClicked() {
    try {
        int value = ui_->spinBoxMemsetChar->value();
        size_t n = static_cast<size_t>(ui_->spinBoxMemsetN->value());


        if (n == 0) {
            ui_->lineEditMemsetDest->setText("(empty result for n=0)");
            return;
        }

        // allocate buffer
        std::vector<char> dest_buffer(n + 1, '\0');

        sml::stringg::memset_sml(dest_buffer.data(), value, n);

        // display result
        ui_->lineEditMemsetDest->setText(
            QString::fromUtf8(dest_buffer.data(), n));

    } catch (...) {
        showError(" unknown error occurred in memset_sml.");
    }
}

// --- Copy Tab ---
void MainWindow::onBtnStrcpyClicked() {
    try {
        QByteArray src_bytes = ui_->lineEditStrcpySrc->text().toUtf8();
        const char* src = src_bytes.constData();

        size_t src_len = sml::stringg::strlen_sml(src);
        size_t buffer_size = src_len + 1;

        std::vector<char> dest_buffer(buffer_size);

        sml::stringg::strcpy_sml(dest_buffer.data(), src);

        ui_->lineEditStrcpyDest->setText(QString::fromUtf8(dest_buffer.data()));

    } catch (...) {
        showError("unknown error occurred in strcpy_sml.");
    }
}

void MainWindow::onBtnStrncpyClicked() {
    try {
        QByteArray src_bytes = ui_->lineEditStrncpySrc->text().toUtf8();
        const char* src = src_bytes.constData();
        size_t n = static_cast<size_t>(ui_->spinBoxStrncpyN->value());


        if (n == 0) {
            ui_->lineEditStrncpyDest->setText("(empty result for n=0)");
            return;
        }

        // allocate buffer of size n + 1
        std::vector<char> dest_buffer(n + 1, '\0');

        sml::stringg::strncpy_sml(dest_buffer.data(), src, n);

        ui_->lineEditStrncpyDest->setText(
            QString::fromUtf8(dest_buffer.data()));

    } catch (...) {
        showError(" unknown error occurred in strncpy_sml.");
    }
}

// --- Concatenate Tab ---
void MainWindow::onBtnStrcatClicked() {
    try {
        std::string dest_str = ui_->lineEditStrcatDest->text().toStdString();
        QByteArray src_bytes = ui_->lineEditStrcatSrc->text().toUtf8();
        const char* src = src_bytes.constData();

        size_t dest_len = dest_str.length();

        size_t src_len = sml::stringg::strlen_sml(src);
        size_t required_size = dest_len + src_len + 1;

        std::vector<char> buffer(dest_str.begin(), dest_str.end());
        buffer.resize(required_size);

        sml::stringg::strcat_sml(buffer.data(), src);

        ui_->lineEditStrcatResult->setText(QString::fromUtf8(buffer.data()));

    } catch (...) {
        showError(" unknown error occurred in strcat_sml.");
    }
}

void MainWindow::onBtnStrncatClicked() {
    try {
        std::string dest_str = ui_->lineEditStrncatDest->text().toStdString();
        QByteArray src_bytes = ui_->lineEditStrncatSrc->text().toUtf8();
        const char* src = src_bytes.constData();
        size_t n = static_cast<size_t>(ui_->spinBoxStrncatN->value());

        size_t dest_len = dest_str.length();
        size_t src_len = sml::stringg::strlen_sml(src);
        size_t copy_len = (n < src_len) ? n : src_len;
        size_t required_size = dest_len + copy_len + 1;

        // create buffer
        std::vector<char> buffer(dest_str.begin(), dest_str.end());
        buffer.resize(required_size);

        sml::stringg::strncat_sml(buffer.data(), src, n);

        ui_->lineEditStrncatResult->setText(QString::fromUtf8(buffer.data()));

    } catch (...) {
        showError("unknown error occurred in strncat_sml.");
    }
}

// --- Compare Tab ---
void MainWindow::onBMemcmpClicked() {
    try {
        QByteArray s1_bytes = ui_->lineEditMemcmpS1->text().toUtf8();
        QByteArray s2_bytes = ui_->lineEditMemcmpS2->text().toUtf8();
        size_t n = static_cast<size_t>(ui_->spinBoxMemcmpN->value());

        int result = sml::stringg::memcmp_sml(s1_bytes.constData(),
                                              s2_bytes.constData(), n);

        ui_->lineEditMemcmpResult->setText(QString::number(result));

    } catch (...) {
        showError(" unknown error occurred in memcmp_sml.");
    }
}

void MainWindow::onBtnStrcmpClicked() {
    try {
        QByteArray s1_bytes = ui_->lineEditStrcmpS1->text().toUtf8();
        QByteArray s2_bytes = ui_->lineEditStrcmpS2->text().toUtf8();

        int result = sml::stringg::strcmp_sml(s1_bytes.constData(),
                                              s2_bytes.constData());

        ui_->lineEditStrcmpResult->setText(QString::number(result));

    } catch (...) {
        showError(" unknown error occurred in strcmp_sml.");
    }
}

void MainWindow::onBtnStrcollClicked() {
    try {
        QByteArray s1_bytes = ui_->lineEditStrcollS1->text().toUtf8();
        QByteArray s2_bytes = ui_->lineEditStrcollS2->text().toUtf8();


        int result = sml::stringg::strcoll_sml(s1_bytes.constData(),
                                               s2_bytes.constData());

        ui_->lineEditStrcollResult->setText(QString::number(result));

    } catch (...) {
        showError(" unknown error occurred in strcoll_sml.");
    }
}

void MainWindow::onBtnStrncmpClicked() {
    try {
        QByteArray s1_bytes = ui_->lineEditStrncmpS1->text().toUtf8();
        QByteArray s2_bytes = ui_->lineEditStrncmpS2->text().toUtf8();
        size_t n = static_cast<size_t>(ui_->spinBoxStrncmpN->value());

        int result = sml::stringg::strncmp_sml(s1_bytes.constData(),
                                               s2_bytes.constData(), n);

        ui_->lineEditStrncmpResult->setText(QString::number(result));

    } catch (...) {
        showError(" unknown error occurred in strncmp_sml.");
    }
}
