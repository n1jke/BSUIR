#ifndef SICKPERSON_H
#define SICKPERSON_H
#include <QDate>
#include <QString>

class SickPerson {
   public:
    SickPerson(const QString& surname = "", const QString& name = "",
               const QString& patronymic = "", bool isMale = true,
               unsigned int age = 0, const QString& diagnoz = "",
               unsigned int wardNumber = 0, const QDate& receipDate = QDate(),
               const QDate& dischargeDate = QDate());

    // getters
    QString getName() const;
    QString getSurname() const;
    QString getPatronymic() const;
    bool isMale() const;
    unsigned int getAge() const;
    QString getDiagnoz() const;
    unsigned int getWardNumber() const;
    QDate getReceipDate() const;
    QDate getDischargeDate() const;

    // setters
    void setName(const QString& Name);
    void setSurname(const QString& Surname);
    void setPatronymic(const QString& Patronymic);
    void setIsMale(bool isMale);
    void setAge(unsigned int age);
    void setDiagnoz(const QString& diagnoz);
    void setWardNumber(unsigned int wardNumber);
    void setReceipDate(const QDate& receipDate);
    void setDischargeDate(const QDate& dischargeDate);

   private:
    QString name_;
    QString surname_;
    QString patronymic_;
    bool isMale_;
    unsigned int age_;
    QString diagnoz_;
    unsigned int wardNumber_;
    QDate receipDate_;
    QDate dischargeDate_;
};

#endif	// SICKPERSON_H
