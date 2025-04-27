#include <QFileDialog>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>

#include "magic.h"
#include "mainwindow.h"
#include "patientdialog.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
    refreshTable(hospitalData_.getAllPersons());
}

void MainWindow::setupUi() {
    auto* central_widget = new QWidget(this);
    auto* main_layout = new QVBoxLayout(central_widget);

    //table set
    tableWidget_ = new QTableWidget(this);
    tableWidget_->setColumnCount(kTableColumnCount);
    tableWidget_->setHorizontalHeaderLabels(
        {"Фамилия", "Имя", "Отчество", "Пол", "Возраст", "Диагноз", "Палата",
         "Дата поступления", "Дата выписки"});
    tableWidget_->setFixedSize(kTableWidth, kTableHeight);
    tableWidget_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget_->setSelectionBehavior(QAbstractItemView::SelectRows);
    main_layout->addWidget(tableWidget_);

    //botton menu
    auto* bottom_layout = new QHBoxLayout();
    noneButton_ = new QPushButton("Все", this);
    wardsMoreThreeButton_ = new QPushButton("Палаты >3 диагнозов", this);
    notDischargedButton_ = new QPushButton("Невыписанные", this);
    searchWardButton_ = new QPushButton("Поиск по палате", this);
    wardInput_ = new QLineEdit(this);
    wardInput_->setValidator(
        new QIntValidator(kZero, kNineThousandNineHundredNinetyNine, this));
    wardInput_->setMaximumWidth(kFifty);
    searchGenderButton_ = new QPushButton("Поиск по полу", this);
    genderCombo_ = new QComboBox(this);
    genderCombo_->addItems({"Мужской", "Женский"});
    searchDiagnosisButton_ = new QPushButton("Поиск по диагнозу", this);
    diagnosisInput_ = new QLineEdit(this);
    diagnosisInput_->setMaximumWidth(kOneHundred);
    searchSurnameButton_ = new QPushButton("Поиск по фамилии", this);
    surnameInput_ = new QLineEdit(this);
    surnameInput_->setMaximumWidth(kOneHundred);
    searchAgeButton_ = new QPushButton("Поиск по возрасту", this);
    minAgeInput_ = new QLineEdit(this);
    minAgeInput_->setValidator(
        new QIntValidator(kZero, kOneHundredTwenty, this));
    minAgeInput_->setMaximumWidth(kFifty);
    maxAgeInput_ = new QLineEdit(this);
    maxAgeInput_->setValidator(
        new QIntValidator(kZero, kOneHundredTwenty, this));
    maxAgeInput_->setMaximumWidth(kFifty);

    bottom_layout->addWidget(noneButton_, 1);  // stretch factor = 1
    bottom_layout->addWidget(wardsMoreThreeButton_, 1);
    bottom_layout->addWidget(notDischargedButton_, 1);
    bottom_layout->addWidget(searchWardButton_, 1);
    bottom_layout->addWidget(wardInput_, 1);
    bottom_layout->addWidget(searchGenderButton_, 1);
    bottom_layout->addWidget(genderCombo_, 1);
    bottom_layout->addWidget(searchDiagnosisButton_, 1);
    bottom_layout->addWidget(diagnosisInput_, 1);
    bottom_layout->addWidget(searchSurnameButton_, 1);
    bottom_layout->addWidget(surnameInput_, 1);
    bottom_layout->addWidget(searchAgeButton_, 1);
    bottom_layout->addWidget(minAgeInput_, 1);
    bottom_layout->addWidget(maxAgeInput_, 1);
    /*
    //минимальная ширина для bottom_layout
    глянуть чего не работает
    upd: выравнивает по ширине таблицы
    auto* bottom_widget = new QWidget(this);
    bottom_widget->setLayout(bottom_layout);
    bottom_widget->setMinimumWidth(kTableWidth + kOneHundred + kOneHundred);
    main_layout->addWidget(bottom_widget);
    */


    main_layout->addLayout(bottom_layout);

    // Right menu
    auto* right_sidebar = new QWidget(this);
    auto* sidebar_layout = new QVBoxLayout(right_sidebar);
    addButton_ = new QPushButton("Добавить пациента", this);
    //addButton_ = new QPushButton("Добавить пациента", this);
    editButton_ = new QPushButton("Редактировать пациента", this);
    removeButton_ = new QPushButton("Удалить пациента", this);
    saveButton_ = new QPushButton("Сохранить", this);
    loadButton_ = new QPushButton("Загрузить", this);
    editButton_->setEnabled(false);
    removeButton_->setEnabled(false);
    sidebar_layout->addWidget(addButton_);
    sidebar_layout->addWidget(editButton_);
    sidebar_layout->addWidget(removeButton_);
    sidebar_layout->addWidget(saveButton_);
    sidebar_layout->addWidget(loadButton_);
    sidebar_layout->addStretch();

    auto* central_layout = new QHBoxLayout();
    central_layout->addWidget(central_widget);
    central_layout->addWidget(right_sidebar);
    auto* main_widget = new QWidget(this);
    main_widget->setLayout(central_layout);
    setCentralWidget(main_widget);
    setFixedWidth(kTableWidth + kOneHundred + kOneHundred);

    // Connect signals
    connect(addButton_, &QPushButton::clicked, this, &MainWindow::addPatient);
    connect(editButton_, &QPushButton::clicked, this, &MainWindow::editPatient);
    connect(removeButton_, &QPushButton::clicked, this,
            &MainWindow::removePatient);
    connect(saveButton_, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(loadButton_, &QPushButton::clicked, this,
            &MainWindow::loadFromFile);
    connect(noneButton_, &QPushButton::clicked, this, &MainWindow::onNone);
    connect(wardsMoreThreeButton_, &QPushButton::clicked, this,
            &MainWindow::onWardsMoreThree);
    connect(notDischargedButton_, &QPushButton::clicked, this,
            &MainWindow::onNotDischarged);
    connect(searchWardButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchWard);
    connect(searchGenderButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchGender);
    connect(searchDiagnosisButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchDiagnosis);
    connect(searchSurnameButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchSurname);
    connect(searchAgeButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchAge);


    connect(tableWidget_, &QTableWidget::itemSelectionChanged, this,
            [this]() {	// oppotunity to edit select person
                bool row_selected = tableWidget_->currentRow() >= kZero;
                editButton_->setEnabled(row_selected);
                removeButton_->setEnabled(row_selected);
            });
}

void MainWindow::refreshTable(QVector<SickPerson> persons) {
    tableWidget_->setRowCount(kZero);
    for (int i = kZero; i < persons.size(); ++i) {
        SickPerson& person = persons[i];
        tableWidget_->insertRow(i);
        tableWidget_->setItem(i, kSurnameColumn,
                              new QTableWidgetItem(person.getSurname()));
        tableWidget_->setItem(i, kNameColumn,
                              new QTableWidgetItem(person.getName()));
        tableWidget_->setItem(i, kPatronymicColumn,
                              new QTableWidgetItem(person.getPatronymic()));
        tableWidget_->setItem(
            i, kGenderColumn,
            new QTableWidgetItem(person.isMale() ? "Мужской" : "Женский"));
        tableWidget_->setItem(
            i, kAgeColumn,
            new QTableWidgetItem(QString::number(person.getAge())));
        tableWidget_->setItem(i, kDiagnozColumn,
                              new QTableWidgetItem(person.getDiagnoz()));
        tableWidget_->setItem(
            i, kWardColumn,
            new QTableWidgetItem(QString::number(person.getWardNumber())));
        tableWidget_->setItem(
            i, kReceiptDateColumn,
            new QTableWidgetItem(
                person.getReceipDate().toString("yyyy-MM-dd")));
        tableWidget_->setItem(
            i, kDischargeDateColumn,
            new QTableWidgetItem(
                person.getDischargeDate().toString("yyyy-MM-dd")));
    }
}

void MainWindow::addPatient() {
    PatientDialog dialog(this);
    // wit until user accept and we quit
    if (dialog.exec() == QDialog::Accepted) {
        hospitalData_.addPerson(dialog.getPerson());
        refreshTable(hospitalData_.getAllPersons());
    }
}

void MainWindow::editPatient() {
    int row = tableWidget_->currentRow();  // row = -1 if not choose row)


    if (row >= kZero) {
        SickPerson person = hospitalData_.getAllPersons()[row];
        PatientDialog dialog(this, &person);
        if (dialog.exec() == QDialog::Accepted) {
            hospitalData_.updatePerson(row, dialog.getPerson());
            refreshTable(hospitalData_.getAllPersons());
        }
    }
}

void MainWindow::removePatient() {
    int row = tableWidget_->currentRow();


    if (row >= kZero) {
        hospitalData_.removePerson(row);
        refreshTable(hospitalData_.getAllPersons());
    }
}

void MainWindow::saveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "",
                                                    "Data Files (*.txt)");
    if (!filename.isEmpty()) {
        hospitalData_.saveToFileHospital(filename);
    }
}

void MainWindow::loadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Загрузить файл", "",
                                                    "Data Files (*.txt)");

    if (filename.isEmpty()) {
        return;
    }

    hospitalData_.loadFromFileHospital(filename);

    QVector<SickPerson> persons = hospitalData_.getAllPersons();

    if (persons.isEmpty()) {
        QMessageBox::warning(this, "Ошибка загрузки",
                             "Не удалось загрузить данные)");
    } else {
        refreshTable(persons);
        QMessageBox::information(
            this, "Успех",
            QString("Успешно загружено %1 записей.").arg(persons.size()));
    }
}

void MainWindow::onNone() {
    refreshTable(hospitalData_.getAllPersons());
}

void MainWindow::onWardsMoreThree() {
    QSet<unsigned int> wards = hospitalData_.getWardsMoreThreeDiagnoz();
    QString message =
        "Палаты с >=3 диагнозов: " + QString::number(wards.size()) + "\n";


    for (unsigned int ward : wards) {
        message += QString::number(ward) + ", ";
    }
    QMessageBox::information(this, "Палаты с =>3 диагнозов", message);
}

void MainWindow::onNotDischarged() {
    refreshTable(hospitalData_.getNotDischargedSortByReceip());
}

void MainWindow::onSearchWard() {
    bool ok;
    unsigned int ward = wardInput_->text().toUInt(&ok);


    if (ok) {
        refreshTable(hospitalData_.searchByWard(ward));
    } else {
        QMessageBox::warning(this, "Error)", "Введите номер палаты");
    }
}

void MainWindow::onSearchGender() {
    bool is_male = (genderCombo_->currentIndex() == kZero);
    refreshTable(hospitalData_.searchByGender(is_male));
}

void MainWindow::onSearchDiagnosis() {
    QString diag = diagnosisInput_->text();
    if (!diag.isEmpty()) {
        refreshTable(hospitalData_.searchByDiagnoz(diag));
    }
}

void MainWindow::onSearchSurname() {
    QString surname = surnameInput_->text();
    if (!surname.isEmpty()) {
        refreshTable(hospitalData_.searchBySurname(surname));
    }
}

void MainWindow::onSearchAge() {
    bool ok_min, ok_max;
    unsigned int min_age = minAgeInput_->text().toUInt(&ok_min);
    unsigned int max_age = maxAgeInput_->text().toUInt(&ok_max);


    if (ok_min && ok_max) {
        refreshTable(hospitalData_.searchAgeInRange(min_age, max_age));
    } else {
        QMessageBox::warning(this, "Error)", "Введите корректный возраст.");
    }
}
