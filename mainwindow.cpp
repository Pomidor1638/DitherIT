#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QRandomGenerator>
#include <vector>
#include <QMessageBox>

std::vector<std::vector<int>> generateBayerMatrix(int size) {
    if (size == 1) {
        return {{0}};
    }

    int half = size / 2;
    auto smaller = generateBayerMatrix(half);

    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));

    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            int val = smaller[i][j];
            matrix[i][j] = 4 * val;
            matrix[i][j + half] = 4 * val + 2;
            matrix[i + half][j] = 4 * val + 3;
            matrix[i + half][j + half] = 4 * val + 1;
        }
    }

    return matrix;
}

bool isPowerOfTwo(int n) {
    return (n & (n - 1)) == 0 && n > 0;
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




std::vector<std::vector<int>> createBayerMatrix(int n, float bright = 1.0f) {
    int size = 1 << n; // 2^n
    auto result = generateBayerMatrix(size);
    int max_val = size * size;

    for (auto& row : result) {
        for (auto& val : row) {
            val = (val * 255 * bright) / max_val; // Правильное округление
        }
    }
    return result;
}

QImage MainWindow::orderedDither(QImage image, bool color) {
    image = color ? image.convertToFormat(QImage::Format_ARGB32)
                 : image.convertToFormat(QImage::Format_Grayscale8);

    int width = image.width();
    int height = image.height();
    int matrixPower = qBound(0, ui->MatrixNInput->value(), 8);
    auto bayerMatrix = createBayerMatrix(matrixPower, 1);
    int matrixSize = bayerMatrix.size();

    float bright = ui->brightInput->value() / 100.0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRgb pixel = image.pixel(x, y);
            int threshold = bayerMatrix[y % matrixSize][x % matrixSize];

            if (color) {
                int r = (qRed(pixel)   * bright > threshold) ? 255 : 0;
                int g = (qGreen(pixel) * bright > threshold) ? 255 : 0;
                int b = (qBlue(pixel)  * bright > threshold) ? 255 : 0;
                image.setPixel(x, y, qRgb(r, g, b));
            } else {
                int gray = (qGray(pixel) * bright > threshold) ? 255 : 0;
                image.setPixel(x, y, qRgb(gray, gray, gray));
            }
        }

        // Обновляем прогресс 1 раз на строку
        if (y % 10 == 0) {
            ui->progressBar->setValue(100 * y / height);
            QApplication::processEvents();
        }
    }

    return image;
}

void MainWindow::on_browseInput_clicked() {
    inputPath = QFileDialog::getOpenFileName(
        this,
        "Выберите изображение",
        "",
        "Изображения (*.png *.jpg *.jpeg *.bmp)"
    );
    ui->inputPath->setText(inputPath);
    image.load(inputPath);

    ui->DitherIT->setEnabled(!image.isNull());
    ui->widthInput->setValue(image.isNull() ? 0 : image.width());
    ui->heightInput->setValue(image.isNull() ? 0 : image.height());
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





void MainWindow::on_DitherIT_clicked() {
    if (inputPath.isEmpty() || outputPath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите входной и выходной файлы");
        return;
    }

    if (!image.load(inputPath)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить изображение");
        ui->progressBar->setValue(100);
        inputPath.clear();
        return;
    }

    ui->DitherIT->setEnabled(false);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    QApplication::processEvents();

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
}


void MainWindow::on_inputPath_editingFinished() {

}


void MainWindow::on_outputPath_editingFinished() {

}

