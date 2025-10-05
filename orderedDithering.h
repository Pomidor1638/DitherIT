#ifndef _ORDEREDDITHERING_H_
#define _ORDEREDDITHERING_H_

#include "IDither.h"

class BayerMatrix final {
private:
    int level;
    float* matrix_ptr;

public:
    BayerMatrix();
    explicit BayerMatrix(int l);
    ~BayerMatrix();

    BayerMatrix(const BayerMatrix& other);
    BayerMatrix(BayerMatrix&& other) noexcept;

    BayerMatrix& operator=(const BayerMatrix& other);
    BayerMatrix& operator=(BayerMatrix&& other) noexcept;

    void setLevel(int l);
    int getLevel() const;
    float* operator[](int k) const;
};

class OrderedDithering : public IDither {
private:
    int colour_depth;
    float threshold;
    bool invert;
    BayerMatrix matrix;

public:
    OrderedDithering();
    OrderedDithering(int res_width, int res_height, float res_brightness, float res_contrast,
                     bool colour, bool inverse, int colour_depth, float threshold, bool invert, int level);
    ~OrderedDithering();

    OrderedDithering(const OrderedDithering& other);
    OrderedDithering(OrderedDithering&& other) noexcept;

    OrderedDithering& operator=(const OrderedDithering& other);
    OrderedDithering& operator=(OrderedDithering&& other) noexcept;

    QImage ditherImage(const QImage& image) override;

    const QString& getDitherName() override;
    DitheringType getDitherType() override;

    int getColorDepth() const;
    void setColorDepth(int d);

    float getThreshold() const;
    void setThreshold(float t);

    int getLevel() const;
    void setLevel(int level);

    bool getInvert() const;
    void setInvert(bool i);

    IDither* copy() const override;
};

#endif // ORDEREDDITHERING_H
