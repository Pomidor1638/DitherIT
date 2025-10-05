#include "DitherListWidget.h"


DitherListWidget::DitherListWidget(QWidget* parent)
    : QListWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void setDitherDefaults(IDither* dither, QSize size)
{
    if (!dither)
        return;


    dither->setWidth(size.width());
    dither->setHeight(size.height());
    dither->setBrightness(1.0f);
    dither->setContrast(1.0f);
    dither->setColour(true);
    dither->setInverse(false);

    if (dither->getWidth() == 1 || dither->getHeight() == 1)
    {
        qDebug() << "WARNING: " << __func__ << " - invalid img sizes";
    }

    switch(dither->getDitherType())
    {
    case DITHERING_ORDERED:
    {
        OrderedDithering* od = dynamic_cast<OrderedDithering*>(dither);
        od->setColorDepth(1);
        od->setLevel(1);
        od->setThreshold(1.0f);
        break;
    }

    default:
        break;
    }
}

void DitherListWidget::addDitherItem(const QString& input, IDither* dither) {

    DitherItemWidget* item = new DitherItemWidget();

    item->setInputPath(input);

    if (!item->loadImage()) {
        emit ditherItemAddError(input);
        delete item;
        return;
    }

    if (dither) {
        const QSize& size = item->getImage().size();
        setDitherDefaults(dither, size);
        item->setDither(std::shared_ptr<IDither>(dither));

    }

    QListWidgetItem* listItem = new QListWidgetItem();
    listItem->setSizeHint(item->sizeHint());

    addItem(listItem);
    setItemWidget(listItem, item);
}

DitherItemWidget* DitherListWidget::currentDitherItem() const {

    QListWidgetItem* item = currentItem();

    if (!item)
        return nullptr;

    return qobject_cast<DitherItemWidget*>(itemWidget(item));
}


