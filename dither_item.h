#ifndef DITHER_ITEM_H
#define DITHER_ITEM_H

#include "IDither.h"
#include "orderedDithering.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QImage>

class DitherItemWidget : public QWidget {
    Q_OBJECT
public:
    DitherItemWidget(QWidget *parent = nullptr);
    ~DitherItemWidget();

    void setDither(std::shared_ptr<IDither> dither);

    void setInputPath(const QString& path);
    const QString& getInputPath() const { return inputPath; }

    std::weak_ptr<IDither> getDither() const { return dither; }

    bool loadImage() {return image.load(inputPath);}
    const QImage& getImage() const {return image;}

    QString getFilename() const { return filename; }


    void updateDisplay();

private:

    QString inputPath{};
    QString filename;
    QImage image;
    std::shared_ptr<IDither> dither = nullptr;
    QLabel* displayLabel = nullptr;
};

#endif // DITHER_ITEM_H
