#ifndef CLOTHES_H
#define CLOTHES_H

#include <qtmetamacros.h>
#include <QString>
#include <utility>

struct DATA {
    QString name;
    int count;
    double price;
    char size;
    bool isAvaliable;
    long long lenght[3];
};

class Clothes {
   public:
    Clothes();

    QString name() const { return data_.name; }

    void setName(QString newName) { data_.name = std::move(newName); }

    int count() const { return data_.count; }

    void setCount(int newCount) { data_.count = newCount; }

    double price() const { return data_.price; }

    void setPrice(double newPrice) { data_.price = newPrice; }

    QChar size() const { return QChar(data_.size); }

    void setSize(QChar newSize) { data_.size = newSize.toLatin1(); }

    bool isAvaliable() const { return data_.isAvaliable; }

    void setAvaliable(bool newAvaliable) { data_.isAvaliable = newAvaliable; }

    long long lenght(long long len = 2) const { return data_.lenght[len]; }

    void setLenght(long long newVal, long long val = 2) {
        data_.lenght[val] = newVal;
    }

   private:
    DATA data_;
};

#endif	// CLOTHES_H
