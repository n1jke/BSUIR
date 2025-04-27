#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

#include "hospitaldata.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() {};

   private:
    HospitalData hospitalData_;
    QTableWidget* tableWidget_;

    //person work buttons
    QPushButton* addButton_;
    QPushButton* editButton_;
    QPushButton* removeButton_;
    QPushButton* saveButton_;
    QPushButton* loadButton_;

    //menu buttons and editline
    QPushButton* noneButton_;
    QPushButton* wardsMoreThreeButton_;
    QPushButton* notDischargedButton_;
    QPushButton* searchWardButton_;
    QLineEdit* wardInput_;
    QPushButton* searchGenderButton_;
    QComboBox* genderCombo_;
    QPushButton* searchDiagnosisButton_;
    QLineEdit* diagnosisInput_;
    QPushButton* searchSurnameButton_;
    QLineEdit* surnameInput_;
    QPushButton* searchAgeButton_;
    QLineEdit* minAgeInput_;
    QLineEdit* maxAgeInput_;

    void setupUi();
    void refreshTable(QVector<SickPerson> persons);

   private slots:
    void addPatient();
    void editPatient();
    void removePatient();
    void saveToFile();
    void loadFromFile();
    void onNone();
    void onWardsMoreThree();
    void onNotDischarged();
    void onSearchWard();
    void onSearchGender();
    void onSearchDiagnosis();
    void onSearchSurname();
    void onSearchAge();
};

#endif	// MAINWINDOW_H
