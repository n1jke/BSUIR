#include "mainwindow.h"

#include <QApplication>

#include <QDir>
#include <QFileInfo>
#include <QString>


int dfsForFolders(int& subFolders, int& files, int& tempDepth,
                  const QString& filePath) {
    QDir dir(filePath);
    if (!dir.exists()) {
        return tempDepth;
    }

    QFileInfoList enrties = dir.entryInfoList(QDir::Dirs | QDir::Files);
    int max_depth = tempDepth;


    for (const auto& entry : enrties) {
        if (entry.isDir()) {
            ++subFolders;
            ++tempDepth;
            max_depth = std::max(dfsForFolders(subFolders, files, tempDepth,
                                               entry.absoluteFilePath()),
                                 max_depth);
            --tempDepth;
        } else {
            ++files;
        }
    }
    return max_depth;
}


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
/*
смотри мне надо в qt c++  сделать слот чтобы принимать папку на подобие брать ее для ввода типа открывать файл но брать просто папку
*/
