#include "palletedialog.h"
#include "ui_palletedialog.h"

PalleteDialog::PalleteDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PalleteDialog)
{
    ui->setupUi(this);
}

PalleteDialog::~PalleteDialog()
{
    delete ui;
}
