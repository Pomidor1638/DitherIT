#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QColor>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./bin");
    QApplication a(argc, argv);

    // Принудительный стиль виджетов
    a.setStyle(QStyleFactory::create("Windows"));

    // Палитра Steam 2000 / GoldSrc
    QPalette pal;

    // Основные цвета
    pal.setColor(QPalette::Window, QColor(76, 88, 68));
    pal.setColor(QPalette::WindowText, QColor(239, 246, 238));
    pal.setColor(QPalette::Base, QColor(63, 71, 56));
    pal.setColor(QPalette::AlternateBase, QColor(150, 135, 50));
    pal.setColor(QPalette::ToolTipBase, QColor(150, 135, 50));
    pal.setColor(QPalette::ToolTipText, QColor(239, 246, 238));
    pal.setColor(QPalette::Text, QColor(239, 246, 238));
    pal.setColor(QPalette::Button, QColor(63, 71, 56));
    pal.setColor(QPalette::ButtonText, QColor(239, 246, 238));
    pal.setColor(QPalette::BrightText, QColor(255, 0, 0));
    pal.setColor(QPalette::Highlight, QColor(150, 135, 50));
    pal.setColor(QPalette::HighlightedText, QColor(239, 246, 238));
    pal.setColor(QPalette::Link, QColor(0, 255, 255));

    // Disabled состояния
    pal.setColor(QPalette::Disabled, QPalette::WindowText, QColor(160, 160, 160));
    pal.setColor(QPalette::Disabled, QPalette::Text, QColor(160, 160, 160));
    pal.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(160, 160, 160));
    pal.setColor(QPalette::Disabled, QPalette::Highlight, QColor(100, 100, 100));

    a.setPalette(pal);

    // Создаем главное окно
    MainWindow w;
    w.setWindowTitle("DitherIT");
    w.show();

    return a.exec();
}
