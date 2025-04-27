#include "patientdialog.h"
#include <QDialogButtonBox>
#include <QFormLayout>
#include "magic.h"

PatientDialog::PatientDialog(QWidget* parent, SickPerson* person)
    : QDialog(parent) {
    auto* layout = new QFormLayout(this);
    surnameEdit_ = new QLineEdit(this);
    nameEdit_ = new QLineEdit(this);
    patronymicEdit_ = new QLineEdit(this);
    genderBox_ = new QComboBox(this);
    genderBox_->addItems({"Мужской", "Женский"});
    ageBox_ = new QSpinBox(this);
    ageBox_->setRange(kZero, kOneHundredTwenty);
    diagnozEdit_ = new QLineEdit(this);
    wardBox_ = new QSpinBox(this);
    wardBox_->setRange(kZero, kNineThousandNineHundredNinetyNine);
    receipEdit_ = new QDateEdit(this);
    receipEdit_->setCalendarPopup(true);
    dischargeEdit_ = new QDateEdit(this);
    dischargeEdit_->setCalendarPopup(true);

    layout->addRow("Фамилия:", surnameEdit_);
    layout->addRow("Имя:", nameEdit_);
    layout->addRow("Отчество:", patronymicEdit_);
    layout->addRow("Пол:", genderBox_);
    layout->addRow("Возраст:", ageBox_);
    layout->addRow("Диагноз:", diagnozEdit_);
    layout->addRow("Номер палаты:", wardBox_);
    layout->addRow("Дата поступления:", receipEdit_);
    layout->addRow("Дата выписки:", dischargeEdit_);


    if (person) {
        surnameEdit_->setText(person->getSurname());
        nameEdit_->setText(person->getName());
        patronymicEdit_->setText(person->getPatronymic());
        genderBox_->setCurrentIndex(person->isMale() ? kZero : kOne);
        ageBox_->setValue(person->getAge());
        diagnozEdit_->setText(person->getDiagnoz());
        wardBox_->setValue(person->getWardNumber());
        receipEdit_->setDate(person->getReceipDate());
        dischargeEdit_->setDate(person->getDischargeDate());
    }

    auto* button_box = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(button_box);
}

SickPerson PatientDialog::getPerson() {
    return SickPerson(surnameEdit_->text(), nameEdit_->text(),
                      patronymicEdit_->text(),
                      genderBox_->currentIndex() == kZero, ageBox_->value(),
                      diagnozEdit_->text(), wardBox_->value(),
                      receipEdit_->date(), dischargeEdit_->date());
}
