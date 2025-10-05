#include "palletedialog.h"
#include "ui_palletedialog.h"

PalleteDialog::PalleteDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PalleteDialog)
{
    ui->setupUi(this);
}

void PalleteDialog::fillScrollArea(std::vector<uint32_t> &colors) {

    if (ui->colorsList->widget()) {
        ui->colorsList->widget()->deleteLater();
    }

    QWidget *contentWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(contentWidget);

    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    const int columns = 8;
    for (size_t i = 0; i < colors.size(); ++i) {
        QLabel *colorLabel = new QLabel();
        colorLabel->setFixedSize(40, 40);
        colorLabel->setStyleSheet(
            QString("background-color: %1; border: 1px solid #ccc;")
            .arg(QColor(colors[i]).name()));
        gridLayout->addWidget(colorLabel, i / columns, i % columns);
    }

    ui->colorsList->setWidget(contentWidget);
    ui->colorsList->setWidgetResizable(true);
}

PalleteDialog::~PalleteDialog() {
    delete ui;
}
