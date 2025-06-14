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
    void on_browseOuput_clicked();
    void on_DitherIT_clicked();

    void on_inputPath_editingFinished();

    void on_outputPath_editingFinished();

private:
    Ui::MainWindow *ui;
    QImage image{};

    QString inputPath{};
    QString outputPath{};

    QImage orderedDither(QImage image, bool color);

};
#endif // MAINWINDOW_H
