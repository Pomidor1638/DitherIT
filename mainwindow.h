#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsScene>
#include "DitherListWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow* ui;

    DitherListWidget* listWidget = nullptr;
    DitherItemWidget* curItemWidget = nullptr;

    std::shared_ptr<IDither> curDither;

    QGraphicsScene* scene;

    QString outputPath;


private:

    // cur dither things
    void updateCurDitherWidgets();
    void updateCurDither();

    // cur dither params
    void updateCommonParams();

    void updateOrderedPararms();
    void updateRandomPararms();
    //void updateFloydPararms();

    // cur dither get/set
    std::weak_ptr<IDither> getCurDither() const;
    void setCurDither(std::shared_ptr<IDither> dither);

    // outputlabel
    void setOutputPath(const QString& s);
    void clearPathLabel();

    // preview image
    bool setCurImage(const QImage& image);
    bool clearCurImage();

    // init funcs
    void connectSlots();
    void initValues();

    void disableForseWidgets();
    void enableForseWidgets();

private slots:

    void onDitherItemAddError(const QString& input);
    void onItemSelectionChanged();

    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_selectAllButton_clicked();

    void on_DitherIT_clicked();

    void on_forseParamsButton_clicked();
    void on_browseOutput_clicked();
    void on_forseSizeButton_clicked();
};

#endif // MAINWINDOW_H
