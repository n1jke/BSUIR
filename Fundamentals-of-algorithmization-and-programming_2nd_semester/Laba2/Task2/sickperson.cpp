#include "sickperson.h"

SickPerson::SickPerson(const QString& surname, const QString& name,
                       const QString& patronymic, bool isMale, unsigned int age,
                       const QString& diagnoz, unsigned int wardNumber,
                       const QDate& receipDate, const QDate& dischargeDate)
    : name_(name),
      surname_(surname),
      patronymic_(patronymic),
      isMale_(isMale),
      age_(age),
      diagnoz_(diagnoz),
      wardNumber_(wardNumber),
      receipDate_(receipDate),


      dischargeDate_(dischargeDate) {};

// getters
QString SickPerson::getSurname() const {
    return surname_;
}
QString SickPerson::getName() const {
    return name_;
}
QString SickPerson::getPatronymic() const {
    return patronymic_;
}
bool SickPerson::isMale() const {
    return isMale_;
}
unsigned int SickPerson::getAge() const {
    return age_;
}
QString SickPerson::getDiagnoz() const {
    return diagnoz_;
}
unsigned int SickPerson::getWardNumber() const {
    return wardNumber_;
}
QDate SickPerson::getReceipDate() const {
    return receipDate_;
}
QDate SickPerson::getDischargeDate() const {
    return dischargeDate_;
}

// setters
void SickPerson::setSurname(const QString& surname) {
    surname_ = surname;
}
void SickPerson::setName(const QString& name) {
    name_ = name;
}
void SickPerson::setPatronymic(const QString& patronymic) {
    patronymic_ = patronymic;
}
void SickPerson::setIsMale(bool isMale) {
    isMale_ = isMale;
}
void SickPerson::setAge(unsigned int age) {
    age_ = age;
}
void SickPerson::setDiagnoz(const QString& diagnoz) {
    diagnoz_ = diagnoz;
}
void SickPerson::setWardNumber(unsigned int wardNumber) {
    wardNumber_ = wardNumber;
}
void SickPerson::setReceipDate(const QDate& receipDate) {
    receipDate_ = receipDate;
}
void SickPerson::setDischargeDate(const QDate& dischargeDate) {
    dischargeDate_ = dischargeDate;
}
