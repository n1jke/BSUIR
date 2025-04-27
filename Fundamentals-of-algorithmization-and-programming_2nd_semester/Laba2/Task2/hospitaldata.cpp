#include "hospitaldata.h"
#include "magic.h"

void HospitalData::addPerson(const SickPerson& newPerson) {
    persons_.append(newPerson);
}

QVector<SickPerson> HospitalData::getAllPersons() {
    return persons_;
}

void HospitalData::updatePerson(unsigned int indx,
                                const SickPerson& updPerson) {
    if (indx < persons_.size()) {
        persons_[indx] = updPerson;
    }
}

void HospitalData::removePerson(unsigned int indx) {
    if (indx < persons_.size()) {
        persons_.remove(indx);
    }
}

QSet<unsigned int> HospitalData::getWardsMoreThreeDiagnoz() {
    QMap<unsigned int, QSet<QString>>
        ward_diagnoz;  // key - ward number, val -  diagnoz


    for (auto& person : persons_) {
        ward_diagnoz[person.getWardNumber()].insert(person.getDiagnoz());
    }
    QSet<unsigned int> result;
    for (auto ward = ward_diagnoz.begin(); ward != ward_diagnoz.end(); ++ward) {
        if (ward.value().size() >= 3) {
            result.insert(ward.key());
        }
    }

    return result;	//can make unortered_map && set and get O(n)
}

QVector<SickPerson> HospitalData::getNotDischargedSortByReceip() {
    QVector<SickPerson> not_discharged;


    for (auto& person : persons_) {
        if (person.getDischargeDate().isNull()) {
            not_discharged.append(person);
        }
    }
    std::sort(not_discharged.begin(), not_discharged.end(),
              [](SickPerson& first, SickPerson& second) {
                  return first.getReceipDate() >
                         second.getReceipDate();  // from height to down
              });
    return not_discharged;
}

QVector<SickPerson> HospitalData::searchByWard(unsigned int wardNumber) {
    QVector<SickPerson> search_ward;


    for (auto& person : persons_) {
        if (person.getWardNumber() == wardNumber) {
            search_ward.append(person);
        }
    }

    return search_ward;
}

QVector<SickPerson> HospitalData::searchByGender(bool isMale) {
    QVector<SickPerson> search_gender;


    for (auto& person : persons_) {
        if (person.isMale() == isMale) {
            search_gender.append(person);
        }
    }

    return search_gender;
}

QVector<SickPerson> HospitalData::searchByDiagnoz(const QString& diagnoz) {
    QVector<SickPerson> search_diagnoz;


    for (auto& person : persons_) {
        if (person.getDiagnoz() == diagnoz) {
            search_diagnoz.append(person);
        }
    }

    return search_diagnoz;
}

QVector<SickPerson> HospitalData::searchBySurname(const QString& surname) {
    QVector<SickPerson> search_surname;


    for (auto& person : persons_) {
        if (person.getSurname() == surname) {
            search_surname.append(person);
        }
    }

    return search_surname;
}

QVector<SickPerson> HospitalData::searchAgeInRange(unsigned int minAge,
                                                   unsigned int maxAge) {

    QVector<SickPerson> search_age;


    if (minAge > maxAge) {
        std::swap(minAge, maxAge);
    }


    for (auto& person : persons_) {
        unsigned int age = person.getAge();
        if (age >= minAge && age <= maxAge) {
            search_age.append(person);
        }
    }

    return search_age;
}

void HospitalData::saveToFileHospital(QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly |
                   QIODevice::Text)) {	// if file exist -> we make it empty
        QMessageBox::warning(nullptr, "Error)", "File error)");
        return;
    }

    QTextStream out(&file);


    for (const SickPerson& person : persons_) {
        QStringList fields = {//container include list of strings
                              QString::number(person.getWardNumber()),
                              person.isMale() ? "1" : "0",
                              person.getSurname(),
                              person.getName(),
                              person.getPatronymic(),
                              QString::number(person.getAge()),
                              person.getDiagnoz(),
                              person.getReceipDate().toString("yyyy-MM-dd"),
                              person.getDischargeDate().toString("yyyy-MM-dd")};
        QString line = fields.join(
            ',');  // move comtainer elem to one string with ',' as define object
        out << line << "\n";
    }

    file.close();
}

void HospitalData::loadFromFileHospital(QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error)", "File error)");
        return;
    }

    persons_.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',', Qt::SkipEmptyParts);
        if (fields.size() == kNine) {  // wait 9 poles with ',' as define object
            bool ok1, ok2;
            unsigned int ward_number = fields[0].toUInt(&ok1);
            bool is_male = (fields[kOne] == "1");
            QString surname = fields[kTwo];
            QString name = fields[kThree];
            QString patronymic = fields[kFour];
            unsigned int age = fields[kFive].toUInt(&ok2);
            QString diagnoz = fields[kSix];
            QDate receip_date = QDate::fromString(fields[kSeven], "yyyy-MM-dd");
            QDate discharge_date =
                QDate::fromString(fields[kEight], "yyyy-MM-dd");

            if (!ok1 || !ok2 || !receip_date.isValid() ||
                !discharge_date.isValid()) {
                QMessageBox::warning(nullptr, "Wrong format",
                                     "Check file for  format)");
                continue;
            }

            SickPerson person(surname, name, patronymic, is_male, age, diagnoz,
                              ward_number, receip_date, discharge_date);
            persons_.append(person);
        } else {
            QMessageBox::warning(nullptr, "Wrong format",
                                 "Check string for format)");
        }
    }

    file.close();
}
