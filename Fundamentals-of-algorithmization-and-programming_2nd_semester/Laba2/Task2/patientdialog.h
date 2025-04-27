#ifndef PATIENTDIALOG_H
#define PATIENTDIALOG_H
#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include "sickperson.h"

class PatientDialog : public QDialog {
   public:
    PatientDialog(QWidget* parent = nullptr, SickPerson* person = nullptr);

    SickPerson getPerson();

   private:
    QLineEdit* surnameEdit_;
    QLineEdit* nameEdit_;
    QLineEdit* patronymicEdit_;
    QComboBox* genderBox_;
    QSpinBox* ageBox_;
    QLineEdit* diagnozEdit_;
    QSpinBox* wardBox_;
    QDateEdit* receipEdit_;
    QDateEdit* dischargeEdit_;
};

#endif	// PATIENTDIALOG_H
