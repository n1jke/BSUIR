#include "mainwindow.h"
#include "date.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    //data validator dd.mm.yyyy
    QRegularExpression date_reg_exp("^\\d{2}\\.\\d{2}\\.\\d{4}$");
    auto* date_validator = new QRegularExpressionValidator(date_reg_exp, this);
    ui_->adddate_line->setValidator(date_validator);
    ui_->coorectdaydate_line->setValidator(date_validator);
    ui_->dateofbirthday_line->setValidator(date_validator);

    //string validator num
    auto* int_validator = new QIntValidator(1, kTenThousand, this);
    ui_->coorectdaynum_line->setValidator(int_validator);

    connect(ui_->openfile_button, &QPushButton::clicked, this,
            &MainWindow::onOpenfilebuttonClicked);
    connect(ui_->closefile_button, &QPushButton::clicked, this,
            &MainWindow::onClosefilebuttonClicked);
    connect(ui_->createfile_button, &QPushButton::clicked, this,
            &MainWindow::onCreatefilebuttonClicked);
    connect(ui_->adddate_button, &QPushButton::clicked, this,
            &MainWindow::onAdddateClicked);
    connect(ui_->dateofbirthday_button, &QPushButton::clicked, this,
            &MainWindow::onBirthdayClicked);
    connect(ui_->coorectday_button, &QPushButton::clicked, this,
            &MainWindow::onDatechangeClicked);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::addDate(
    const QString& date) {	// create date-object from string
    QStringList parts = date.split(".");
    if (parts.size() != 3) {
        return;
    }
    int day = parts[0].toInt();
    int month = parts[1].toInt();
    int year = parts[2].toInt();
    Date data(day, month, year);
    days_.append(data);
}

void MainWindow::updateTable() {
    ui_->tableWidget->setRowCount(days_.size());

    //if have birhday > parse | else > "N/A"
    bool has_birthday = false;
    Date birthday;
    QString bday_str = ui_->dateofbirthday_line->text();
    if (checkstr(bday_str)) {
        QStringList parts = bday_str.split(".");
        int day = parts[0].toInt();
        int month = parts[1].toInt();
        int year = parts[2].toInt();
        birthday = Date(day, month, year);
        has_birthday = true;
    }

    for (int i = 0; i < days_.size(); i++) {
        Date date = days_[i];
        auto* item_date = new QTableWidgetItem(date.fromDateToString());
        auto* item_leap = new QTableWidgetItem(date.isLeap() ? "Yes" : "No");
        auto* item_next =
            new QTableWidgetItem(date.NextDay().fromDateToString());
        auto* item_prev =
            new QTableWidgetItem(date.PreviousDay().fromDateToString());
        auto* item_week =
            new QTableWidgetItem(QString::number(date.WeekNumber()));
        QString days_to_bday =
            has_birthday ? QString::number(date.daysTillYourBithday(birthday))
                         : "N/A";
        auto* item_bday = new QTableWidgetItem(days_to_bday);

        ui_->tableWidget->setItem(i, 0, item_date);
        ui_->tableWidget->setItem(i, 1, item_leap);
        ui_->tableWidget->setItem(i, 2, item_next);
        ui_->tableWidget->setItem(i, 3, item_prev);
        ui_->tableWidget->setItem(i, 4, item_week);
        ui_->tableWidget->setItem(i, kFive, item_bday);
    }
}

bool MainWindow::checkstr(const QString& date) {
    static QRegularExpression re(
        "^\\d{2}\\.\\d{2}\\.\\d{4}$");	// template of regular expression
    QRegularExpressionMatch match =
        re.match(date);	 //check for string format need template
    return match.hasMatch();
}

void MainWindow::FromFiletoarr() {
    days_.clear();
    ui_->tableWidget->clearContents();
    ui_->tableWidget->setRowCount(0);

    QTextStream in(&file_);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // define string to dates, skip ' ' and tab
        QStringList date_strings = line.split(
            QRegularExpression("\\s+"),
            Qt::SkipEmptyParts);  // find data object and split to strings after push to list


        for (const QString& date_str : date_strings) {
            if (checkstr(date_str)) {
                addDate(date_str);
            } else {
                QMessageBox::warning(this, tr("Invalid date format"),
                                     tr("The date '%1' is not in the correct "
                                        "format (dd.mm.yyyy).")
                                         .arg(date_str));
            }
        }
    }
    updateTable();
}

void MainWindow::EditFile(int index, const QString& edit) {
    //if dont have path or wrong format > quit
    if (pathToFile_.isEmpty() || !checkstr(edit)) {
        return;
    }

    //open file
    QFile file(pathToFile_);
    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    //read all
    QByteArray content = file.readAll();

    // fina the "dd.mm.yyyy"
    static QRegularExpression re(
        "\\d{2}\\.\\d{2}\\.\\d{4}");  // template of regular expression
    QRegularExpressionMatchIterator it = re.globalMatch(
        QString(content));	//check for string format need template
    int current_index = 0;
    int pos_to_edit = -1;

    // find ind data
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();


        if (current_index == index - 1) {
            pos_to_edit = match.capturedStart();
            break;
        }
        ++current_index;
    }

    //not find > quit


    if (pos_to_edit == -1) {
        file.close();
        return;
    }

    //sure that new data size = 10 symbols
    if (edit.size() != kTen) {
        file.close();
        return;
    }

    //goto need pos
    if (!file.seek(pos_to_edit)) {
        file.close();
        return;
    }

    //in-place overwrite
    file.write(edit.toUtf8());
    file.close();
}

void MainWindow::onOpenfilebuttonClicked() {
    QString file_name = QFileDialog::getOpenFileName(
        this, tr("Open Date File"), "",
        tr("Text Files (*.txt)"));	// tr to system language, "" -curr directory, file .txt
    if (!file_name.isEmpty()) {
        pathToFile_ = file_name;
        file_.setFileName(pathToFile_);
        if (file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
            FromFiletoarr();
            file_.close();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        }
    }
}

void MainWindow::onClosefilebuttonClicked() {
    pathToFile_.clear();
    days_.clear();
    ui_->tableWidget->clearContents();
    ui_->tableWidget->setRowCount(0);
    QMessageBox::information(this, tr("File closed"),
                             tr("File has been closed."));
}

void MainWindow::onCreatefilebuttonClicked() {
    QString file_name = QFileDialog::getSaveFileName(
        this, tr("Create Date File"), "", tr("Text Files (*.txt)"));
    if (!file_name.isEmpty()) {
        pathToFile_ = file_name;
        QFile f(pathToFile_);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            f.close();
            QMessageBox::information(this, tr("File created"),
                                     tr("File has been created."));
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Could not create file."));
        }
    }
}

void MainWindow::onAdddateClicked() {
    QString new_date_str = ui_->adddate_line->text();
    if (checkstr(new_date_str)) {
        addDate(new_date_str);
        if (!pathToFile_.isEmpty()) {
            QFile f(pathToFile_);
            if (f.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&f);
                out << " " << new_date_str;
                f.close();
            }
        }
        updateTable();
    } else {
        QMessageBox::warning(this, tr("Invalid date"),
                             tr("Date format must be dd.mm.yyyy"));
    }
}

void MainWindow::onBirthdayClicked() {
    QString bday_str = ui_->dateofbirthday_line->text();
    if (checkstr(bday_str)) {
        updateTable();
    } else {
        QMessageBox::warning(this, tr("Invalid birthday"),
                             tr("Birthday format must be dd.mm.yyyy"));
    }
}

void MainWindow::onDatechangeClicked() {
    bool ok;
    int row = ui_->coorectdaynum_line->text().toInt(&ok);
    --row;
    if (!ok || row < 0 || row >= days_.size()) {
        QMessageBox::warning(this, tr("Invalid row"),
                             tr("Row number is out of range."));
        return;
    }
    QString new_date_str = ui_->coorectdaydate_line->text();
    if (!checkstr(new_date_str)) {
        QMessageBox::warning(this, tr("Invalid date"),
                             tr("Date format must be dd.mm.yyyy"));
        return;
    }
    QStringList parts = new_date_str.split(".");
    int day = parts[0].toInt();
    int month = parts[1].toInt();
    int year = parts[2].toInt();
    // update in vector
    days_[row] = Date(day, month, year);
    updateTable();
    // find in file
    EditFile(row, new_date_str);
}
