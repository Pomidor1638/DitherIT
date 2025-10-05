#ifndef _IDITHER_H_
#define _IDITHER_H_

#include <QImage>
#include <QString>

enum DitheringType
{
    DITHERING_RANDOM = 0,
    DITHERING_ORDERED,
    DITHERING_FLOYD,
};

struct CommonParams {
    int width = 256;
    int height = 256;
    float brightness = 1.0f;
    float contrast = 1.0f;
    bool colour = true;
    bool inverse = false;

    CommonParams() = default;

    CommonParams(int w, int h, float b, float c, bool col, bool inv)
        : width(w), height(h), brightness(b), contrast(c), colour(col), inverse(inv) {}
};

class IDither {
protected:
    int res_width;
    int res_height;
    float res_brightness;
    float res_contrast;
    bool colour;
    bool inverse;

public:
    IDither()
        : res_width(256)
        , res_height(256)
        , res_brightness(1.0f)
        , res_contrast(1.0f)
        , colour(true)
        , inverse(false)
    {

    }

    IDither(int w, int h, float b, float c, bool col, bool inv)
        : res_width(w)
        , res_height(h)
        , res_brightness(b)
        , res_contrast(c)
        , colour(col)
        , inverse(inv)
    {

    }

    virtual ~IDither() = default;

    IDither(const IDither& other)
        : res_width(other.res_width),
        res_height(other.res_height),
        res_brightness(other.res_brightness),
        res_contrast(other.res_contrast),
        colour(other.colour),
        inverse(other.inverse) {}

    IDither(IDither&& other) noexcept
        : res_width(other.res_width),
        res_height(other.res_height),
        res_brightness(other.res_brightness),
        res_contrast(other.res_contrast),
        colour(other.colour),
        inverse(other.inverse) {
        other.res_width = 0;
        other.res_height = 0;
        other.res_brightness = 0;
        other.res_contrast = 0.0f;
        other.colour = true;
        other.inverse = false;
    }

    IDither& operator=(const IDither& other) {
        if (this == &other) return *this;
        res_width = other.res_width;
        res_height = other.res_height;
        res_brightness = other.res_brightness;
        res_contrast = other.res_contrast;
        colour = other.colour;
        inverse = other.inverse;
        return *this;
    }

    IDither& operator=(IDither&& other) noexcept {
        if (this == &other) return *this;
        res_width = other.res_width;
        res_height = other.res_height;
        res_brightness = other.res_brightness;
        res_contrast = other.res_contrast;
        colour = other.colour;
        inverse = other.inverse;

        other.res_width = 0;
        other.res_height = 0;
        other.res_brightness = 0;
        other.res_contrast = 0.0f;
        other.colour = true;
        other.inverse = false;
        return *this;
    }

    virtual QImage ditherImage(const QImage& image) = 0;
    virtual const QString& getDitherName() = 0;
    virtual DitheringType getDitherType() = 0;

    int getWidth() const { return res_width; }
    void setWidth(int w) { res_width = w; }

    int getHeight() const { return res_height; }
    void setHeight(int h) { res_height = h; }

    float getBrightness() const { return res_brightness; }
    void setBrightness(float b) { res_brightness = b; }

    float getContrast() const { return res_contrast; }
    void setContrast(float c) { res_contrast = c; }

    bool isColour() const { return colour; }
    void setColour(bool c) { colour = c; }

    bool isInverse() const { return inverse; }
    void setInverse(bool i) { inverse = i; }

    virtual IDither* copy() const = 0;

    CommonParams getCommonParams() const {
        return CommonParams(res_width, res_height, res_brightness, res_contrast, colour, inverse);
    }

    void setCommonParams(const CommonParams& params) {
        res_width = params.width;
        res_height = params.height;
        res_brightness = params.brightness;
        res_contrast = params.contrast;
        colour = params.colour;
        inverse = params.inverse;
    }

};

#endif
