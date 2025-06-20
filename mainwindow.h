#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseInput_clicked();
    void on_palleteMenu_triggered();
    void on_browseOuput_clicked();
    void on_DitherIT_clicked();

private:
    Ui::MainWindow *ui;
    QImage image{};

    QString inputPath{};
    QString outputPath{};

    QImage orderedDither(QImage image, bool color);
    QRgb nearestColor(QRgb pixel);

    void loadImage(const QString &path);

};
#endif // MAINWINDOW_H
