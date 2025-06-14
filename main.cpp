#include "mainwindow.h"
#include <QApplication>
#include <QImageReader>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
// 1. Настройка путей к плагинам перед созданием QApplication
#ifdef Q_OS_WIN
    QCoreApplication::addLibraryPath("./bin");
#endif

    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("DitherIT");
    w.show();

    return a.exec();
}
