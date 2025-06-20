/********************************************************************************
** Form generated from reading UI file 'palletedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALLETEDIALOG_H
#define UI_PALLETEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PalleteDialog
{
public:
    QFrame *palleteScreen;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *colorHex;
    QVBoxLayout *verticalLayout;
    QPushButton *saveColorButton;
    QPushButton *deleteColorButton;
    QPushButton *resetPalleteButton;
    QCheckBox *customPalleteFlag;
    QScrollArea *colorsList;
    QWidget *scrollAreaWidgetContents;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *horizontalSlider_2;
    QLabel *label_2;
    QSlider *horizontalSlider;

    void setupUi(QDialog *PalleteDialog)
    {
        if (PalleteDialog->objectName().isEmpty())
            PalleteDialog->setObjectName("PalleteDialog");
        PalleteDialog->resize(430, 258);
        palleteScreen = new QFrame(PalleteDialog);
        palleteScreen->setObjectName("palleteScreen");
        palleteScreen->setGeometry(QRect(10, 10, 191, 171));
        palleteScreen->setFrameShape(QFrame::Shape::StyledPanel);
        palleteScreen->setFrameShadow(QFrame::Shadow::Raised);
        gridLayoutWidget = new QWidget(PalleteDialog);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(210, 10, 211, 171));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(5, 5, 5, 5);
        colorHex = new QLineEdit(gridLayoutWidget);
        colorHex->setObjectName("colorHex");

        gridLayout->addWidget(colorHex, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        saveColorButton = new QPushButton(gridLayoutWidget);
        saveColorButton->setObjectName("saveColorButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(saveColorButton->sizePolicy().hasHeightForWidth());
        saveColorButton->setSizePolicy(sizePolicy);
        saveColorButton->setMaximumSize(QSize(50, 20));

        verticalLayout->addWidget(saveColorButton);

        deleteColorButton = new QPushButton(gridLayoutWidget);
        deleteColorButton->setObjectName("deleteColorButton");
        sizePolicy.setHeightForWidth(deleteColorButton->sizePolicy().hasHeightForWidth());
        deleteColorButton->setSizePolicy(sizePolicy);
        deleteColorButton->setMaximumSize(QSize(50, 20));

        verticalLayout->addWidget(deleteColorButton);

        resetPalleteButton = new QPushButton(gridLayoutWidget);
        resetPalleteButton->setObjectName("resetPalleteButton");
        sizePolicy.setHeightForWidth(resetPalleteButton->sizePolicy().hasHeightForWidth());
        resetPalleteButton->setSizePolicy(sizePolicy);
        resetPalleteButton->setMaximumSize(QSize(50, 20));

        verticalLayout->addWidget(resetPalleteButton);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        customPalleteFlag = new QCheckBox(gridLayoutWidget);
        customPalleteFlag->setObjectName("customPalleteFlag");

        gridLayout->addWidget(customPalleteFlag, 0, 0, 1, 1);

        colorsList = new QScrollArea(gridLayoutWidget);
        colorsList->setObjectName("colorsList");
        colorsList->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 141, 101));
        colorsList->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(colorsList, 1, 0, 1, 1);

        formLayoutWidget = new QWidget(PalleteDialog);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 190, 411, 51));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignmentFlag::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignmentFlag::AlignCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        horizontalSlider_2 = new QSlider(formLayoutWidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setOrientation(Qt::Orientation::Horizontal);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, horizontalSlider_2);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        horizontalSlider = new QSlider(formLayoutWidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, horizontalSlider);


        retranslateUi(PalleteDialog);

        QMetaObject::connectSlotsByName(PalleteDialog);
    } // setupUi

    void retranslateUi(QDialog *PalleteDialog)
    {
        PalleteDialog->setWindowTitle(QCoreApplication::translate("PalleteDialog", "Dialog", nullptr));
        saveColorButton->setText(QCoreApplication::translate("PalleteDialog", "Save", nullptr));
        deleteColorButton->setText(QCoreApplication::translate("PalleteDialog", "Delete", nullptr));
        resetPalleteButton->setText(QCoreApplication::translate("PalleteDialog", "Reset", nullptr));
        customPalleteFlag->setText(QCoreApplication::translate("PalleteDialog", "Custom Pallete", nullptr));
        label->setText(QCoreApplication::translate("PalleteDialog", "Color", nullptr));
        label_2->setText(QCoreApplication::translate("PalleteDialog", "Lumination", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PalleteDialog: public Ui_PalleteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PALLETEDIALOG_H
