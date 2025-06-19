#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QRandomGenerator>
#include <vector>
#include <QMessageBox>
#include "palletedialog.h"

std::vector<std::vector<double>> generateBayerMatrix(int size) {
    if (size == 1) {
        return {{0}};
    }

    int half = size / 2;
    auto smaller = generateBayerMatrix(half);

    std::vector<std::vector<double>> matrix(size, std::vector<double>(size));

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            double val = smaller[i][j];
            matrix[i][j] = 4 * val;
            matrix[i][j + half] = 4 * val + 2;
            matrix[i + half][j] = 4 * val + 3;
            matrix[i + half][j + half] = 4 * val + 1;
        }
    }

    return matrix;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}




std::vector<std::vector<double>> createBayerMatrix(int n) {
    int size = 1 << n; // 2^n
    auto result = generateBayerMatrix(size);
    int max_val = size * size;
    if (n){
        for (auto& row : result) {
            for (auto& val : row) {
                val /= max_val;
            }
        }
    }
    else{
        result[0][0] = 0.5;
    }

    return result;
}

double colorDistance(QRgb first, QRgb second){

    double r = qRed  (first) - qRed  (second);
    double g = qGreen(first) - qGreen(second);
    double b = qBlue (first) - qBlue (second);

    return r*r + g*g + b*b;
}

QRgb MainWindow::nearestColor(QRgb pixel){

    static const QRgb colors[] = {
        qRgb(  0,   0,   0),
        qRgb(  0,   0, 255),
        qRgb(  0, 255,   0),
        qRgb(  0, 255, 255),
        qRgb(255,   0,   0),
        qRgb(255,   0, 255),
        qRgb(255, 255,   0),
        qRgb(255, 255, 255),
    };


    double score = 65536.0;
    QRgb best = 0;

    for (const auto &x : colors){
        double cur = colorDistance(pixel, x);
        if (cur < score){
            best = x;
            score = cur;
        }
    }
    return best;
}

QImage MainWindow::orderedDither(QImage image, bool color) {
    image = color ? image.convertToFormat(QImage::Format_ARGB32)
                 : image.convertToFormat(QImage::Format_Grayscale8);

    int width = image.width();
    int height = image.height();
    int matrixPower = qBound(0, ui->MatrixNInput->value(), 11);
    const auto bayerMatrix = createBayerMatrix(matrixPower);
    int matrixSize = bayerMatrix.size();

    float bright = ui->brightInput->value() / 100.0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRgb pixel = image.pixel(x, y);
            double threshold = 255 * (bayerMatrix[y % matrixSize][x % matrixSize] - 0.5);
            if (color) {

                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);

                if (ui->inverseFlag->isChecked()) {
                    r = 255 - r;
                    g = 255 - g;
                    b = 255 - b;
                }

                r = qBound(0, static_cast<int>(r * bright + threshold), 255);
                g = qBound(0, static_cast<int>(g * bright + threshold), 255);
                b = qBound(0, static_cast<int>(b * bright + threshold), 255);



                image.setPixel(x, y, nearestColor(qRgb(r, g, b)));

            } else {
                int gray = (qGray(pixel) * bright + threshold > 127) != ui->inverseFlag->isChecked() ? 255 : 0;
                image.setPixel(x, y, qRgb(gray, gray, gray));
            }
        }
        if (y % 10 == 0) {
            ui->progressBar->setValue(100 * y / height);
            QApplication::processEvents();
        }
    }

    return image;
}

void MainWindow::on_browseInput_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выберите изображение",
        "",
        "Изображения (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!fileName.isEmpty()) {
        loadImage(fileName);
    }
}

void MainWindow::loadImage(const QString &path) {

    ui->DitherIT->setEnabled(false);
    ui->widthInput->setValue(0);
    ui->heightInput->setValue(0);
    ui->inputPath->clear();

    if (!image.load(path)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение");
        return;
    }

    inputPath = path;
    ui->inputPath->setText(path);
    ui->widthInput->setValue(image.width());
    ui->heightInput->setValue(image.height());
    ui->DitherIT->setEnabled(true);

    if (ui->graphicsView->scene()) {
        delete ui->graphicsView->scene();
    }

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}


void MainWindow::on_browseOuput_clicked() {
     outputPath = QFileDialog::getSaveFileName(
        this,
        "Сохраните изображение",
        "",
        "Изображения (*.png *.jpg *.jpeg *.bmp)"
    );
    ui->outputPath->setText(outputPath);
}

void MainWindow::on_palleteMenu_triggered(){

    PalleteDialog dialog(this);
    dialog.exec();

}



void MainWindow::on_DitherIT_clicked() {

    //ui->progressBar->setRange(0, 100); // Пока это излишне
    ui->progressBar->setValue(0);
    ui->DitherIT->setEnabled(false);
    QApplication::processEvents(); // Пока не понятно медленная ли эта процедура, но с ней кнопка отключается сразу

    if (inputPath.isEmpty() || outputPath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите входной и выходной файлы");
        ui->DitherIT->setEnabled(true);
        return;
    }

    if (!image.load(inputPath)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить изображение");
        ui->progressBar->setValue(100);
        inputPath.clear();
        ui->DitherIT->setEnabled(true);
        return;
    }

    int targetWidth = ui->widthInput->value();
    int targetHeight = ui->heightInput->value();

    if (targetWidth > 0 && targetHeight > 0) {
        image = image.scaled(targetWidth, targetHeight,
                             Qt::IgnoreAspectRatio,
                             Qt::SmoothTransformation);
    }

    bool useColor = ui->colorFlag->isChecked();

    try {
        image = orderedDither(image, useColor);

        if (!image.save(outputPath)) {
            throw std::runtime_error("Ошибка сохранения файла");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }

    ui->progressBar->setValue(100);
    ui->DitherIT->setEnabled(true);
    QApplication::processEvents(); // Такая же ситуация что и сверху
}


