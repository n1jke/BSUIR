#ifndef HOSPITALDATA_H
#define HOSPITALDATA_H
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QSet>
#include <QTextStream>
#include <QVector>
#include "sickperson.h"


class HospitalData {
   public:
    HospitalData() {};

    // crud operations
    void addPerson(const SickPerson& newPerson);
    QVector<SickPerson> getAllPersons();
    void updatePerson(unsigned int indx, const SickPerson& updPerson);
    void removePerson(unsigned int indx);

    QSet<unsigned int> getWardsMoreThreeDiagnoz();
    QVector<SickPerson> getNotDischargedSortByReceip();
    QVector<SickPerson> searchByWard(unsigned int wardNumber);
    QVector<SickPerson> searchByGender(bool isMale);
    QVector<SickPerson> searchByDiagnoz(const QString& diagnoz);
    QVector<SickPerson> searchBySurname(const QString& surname);
    QVector<SickPerson> searchAgeInRange(unsigned int minAge,
                                         unsigned int maxAge);

    void loadFromFileHospital(QString& filename);
    void saveToFileHospital(QString& filename);

   private:
    QVector<SickPerson> persons_;
};

#endif	// HOSPITALDATA_H
