#include "dither_item.h"
#include <QHBoxLayout>
#include <QFileInfo>

DitherItemWidget::DitherItemWidget(QWidget* parent)
    : QWidget(parent)
{

    static const int widget_height = 30;

    QHBoxLayout *layout = new QHBoxLayout(this);
    displayLabel = new QLabel(this);
    layout->addWidget(displayLabel);
    setFixedHeight(widget_height);
}
DitherItemWidget::~DitherItemWidget()
{
    if (displayLabel)
    {
        delete displayLabel;
        displayLabel = nullptr;
    }
}


void DitherItemWidget::setInputPath(const QString& path)
{
    inputPath = path;
    filename = QFileInfo(path).baseName();
}

void DitherItemWidget::setDither(std::shared_ptr<IDither> dither)
{
    this->dither =  dither;
    updateDisplay();
}

void DitherItemWidget::updateDisplay()
{
    if (!displayLabel)
        return;

    QString text;
    text += (dither ? dither->getDitherName() : "No dither") + " | ";
    text += filename;
    displayLabel->setText(text);
}

