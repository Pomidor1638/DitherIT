#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[])
{

    QCoreApplication::addLibraryPath("./bin");
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("DitherIT");

    w.show();

    a.setStyle(QStyleFactory::create("Windows"));

    return a.exec();
}
