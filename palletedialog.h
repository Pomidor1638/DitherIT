#ifndef PALLETEDIALOG_H
#define PALLETEDIALOG_H

#include <QDialog>

namespace Ui {
class PalleteDialog;
}

class PalleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PalleteDialog(QWidget *parent = nullptr);
    ~PalleteDialog();
private:
    Ui::PalleteDialog *ui;
};

#endif // PALLETEDIALOG_H
