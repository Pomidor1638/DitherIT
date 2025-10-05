#include "dither_item.h"
#include <QHBoxLayout>
#include <QFileInfo>

DitherItemWidget::DitherItemWidget(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(2,2,2,2);
    layout->setSpacing(4);

    displayLabel = new QLabel(this);
    displayLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(displayLabel);

    QFontMetrics metrics(displayLabel->font());
    int h = metrics.height(); // небольшой padding сверху/снизу
    displayLabel->setFixedHeight(h);
    setFixedHeight(h);
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

