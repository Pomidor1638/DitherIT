/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *palleteMenu;
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QPushButton *browseInput;
    QPushButton *browseOuput;
    QLineEdit *outputPath;
    QLineEdit *inputPath;
    QGraphicsView *graphicsView;
    QProgressBar *progressBar_2;
    QTabWidget *tabWidget;
    QWidget *orderedTab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *inverseFlag;
    QCheckBox *colorFlag;
    QCheckBox *stretchFlag;
    QSpacerItem *verticalSpacer;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *MatrixNInput;
    QSpinBox *heightInput;
    QLabel *label_4;
    QDoubleSpinBox *brightInput;
    QLabel *label_3;
    QSpinBox *widthInput;
    QWidget *tab_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QToolButton *DitherIT;
    QMenuBar *menubar;
    QMenu *toolsMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(495, 467);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(495, 436));
        MainWindow->setMaximumSize(QSize(16384, 16384));
        MainWindow->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setDockOptions(QMainWindow::DockOption::AllowTabbedDocks|QMainWindow::DockOption::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        action = new QAction(MainWindow);
        action->setObjectName("action");
        palleteMenu = new QAction(MainWindow);
        palleteMenu->setObjectName("palleteMenu");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(10, 320, 281, 16));
        progressBar->setValue(0);
        formLayoutWidget_2 = new QWidget(centralwidget);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(10, 370, 471, 61));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        browseInput = new QPushButton(formLayoutWidget_2);
        browseInput->setObjectName("browseInput");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, browseInput);

        browseOuput = new QPushButton(formLayoutWidget_2);
        browseOuput->setObjectName("browseOuput");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, browseOuput);

        outputPath = new QLineEdit(formLayoutWidget_2);
        outputPath->setObjectName("outputPath");
        outputPath->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, outputPath);

        inputPath = new QLineEdit(formLayoutWidget_2);
        inputPath->setObjectName("inputPath");
        inputPath->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, inputPath);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 10, 281, 281));
        graphicsView->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
""));
        progressBar_2 = new QProgressBar(centralwidget);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setEnabled(false);
        progressBar_2->setGeometry(QRect(10, 340, 281, 16));
        progressBar_2->setValue(0);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(300, 10, 181, 281));
        orderedTab = new QWidget();
        orderedTab->setObjectName("orderedTab");
        verticalLayoutWidget = new QWidget(orderedTab);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 140, 161, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        inverseFlag = new QCheckBox(verticalLayoutWidget);
        inverseFlag->setObjectName("inverseFlag");
        inverseFlag->setChecked(false);
        inverseFlag->setAutoRepeat(false);

        verticalLayout->addWidget(inverseFlag);

        colorFlag = new QCheckBox(verticalLayoutWidget);
        colorFlag->setObjectName("colorFlag");
        colorFlag->setChecked(false);
        colorFlag->setAutoRepeat(false);

        verticalLayout->addWidget(colorFlag);

        stretchFlag = new QCheckBox(verticalLayoutWidget);
        stretchFlag->setObjectName("stretchFlag");
        stretchFlag->setChecked(false);
        stretchFlag->setAutoRepeat(false);

        verticalLayout->addWidget(stretchFlag);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        formLayoutWidget = new QWidget(orderedTab);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 10, 161, 121));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        MatrixNInput = new QSpinBox(formLayoutWidget);
        MatrixNInput->setObjectName("MatrixNInput");
        MatrixNInput->setMinimum(0);
        MatrixNInput->setMaximum(11);
        MatrixNInput->setValue(1);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, MatrixNInput);

        heightInput = new QSpinBox(formLayoutWidget);
        heightInput->setObjectName("heightInput");
        heightInput->setMinimum(1);
        heightInput->setMaximum(32768);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, heightInput);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        brightInput = new QDoubleSpinBox(formLayoutWidget);
        brightInput->setObjectName("brightInput");
        brightInput->setMaximum(1000.000000000000000);
        brightInput->setValue(100.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, brightInput);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        widthInput = new QSpinBox(formLayoutWidget);
        widthInput->setObjectName("widthInput");
        widthInput->setMinimum(1);
        widthInput->setMaximum(32768);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, widthInput);

        tabWidget->addTab(orderedTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 300, 281, 20));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setTextFormat(Qt::TextFormat::AutoText);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_5);

        DitherIT = new QToolButton(centralwidget);
        DitherIT->setObjectName("DitherIT");
        DitherIT->setEnabled(true);
        DitherIT->setGeometry(QRect(300, 300, 180, 61));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DitherIT->sizePolicy().hasHeightForWidth());
        DitherIT->setSizePolicy(sizePolicy1);
        DitherIT->setMinimumSize(QSize(180, 50));
        DitherIT->setCheckable(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 495, 21));
        toolsMenu = new QMenu(menubar);
        toolsMenu->setObjectName("toolsMenu");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(toolsMenu->menuAction());
        toolsMenu->addAction(palleteMenu);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DitherIT", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\273\320\270\321\202\321\200\320\260", nullptr));
        palleteMenu->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\273\320\270\321\202\321\200\320\260", nullptr));
        browseInput->setText(QCoreApplication::translate("MainWindow", "input", nullptr));
        browseOuput->setText(QCoreApplication::translate("MainWindow", "ouput", nullptr));
        inverseFlag->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\262\320\265\321\200\321\201\320\270\321\217", nullptr));
        colorFlag->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        stretchFlag->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\202\321\217\320\275\321\203\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\273\320\270\320\275\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\257\321\200\320\272\320\276\321\201\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\275\320\263 ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(orderedTab), QCoreApplication::translate("MainWindow", "Ordered", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        DitherIT->setText(QCoreApplication::translate("MainWindow", "DITHER", nullptr));
        toolsMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
