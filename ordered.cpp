#include "orderedDithering.h"
#include <QDebug>

QImage OrderedDithering::ditherImage(const QImage& image)
{
    const int level = matrix.getLevel();

    if (!level)
    {
        return QImage{};
    }

    QImage result = image.convertToFormat(QImage::Format_ARGB32).scaled(res_width, res_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    const int bits = qBound(1, colour_depth, 8);
    const int levels = 1 << bits;

    const float bright = (res_brightness - 1.0f) * 255.0f;
    const float contrast_center = 127.5f;

    const bool hasAlpha = result.hasAlphaChannel();

    for (int y = 0; y < result.height(); y++)
    {
        const int matrix_y = y % level;
        float* matrix_row = matrix[matrix_y];

        for (int x = 0; x < result.width(); x++)
        {
            const QRgb pixel = result.pixel(x, y);
            const float thres = threshold * matrix_row[x % level] * 255.0f;

            const int alpha = hasAlpha ? qAlpha(pixel) : 255;

            if (colour)
            {
                const int r_orig = inverse ? 255 - qRed(pixel) : qRed(pixel);
                const int g_orig = inverse ? 255 - qGreen(pixel) : qGreen(pixel);
                const int b_orig = inverse ? 255 - qBlue(pixel) : qBlue(pixel);

                float r = (r_orig - contrast_center) * res_contrast + contrast_center + bright + thres;
                float g = (g_orig - contrast_center) * res_contrast + contrast_center + bright + thres;
                float b = (b_orig - contrast_center) * res_contrast + contrast_center + bright + thres;

                int r_final = qBound(0, static_cast<int>(r + 0.5f), 255);
                int g_final = qBound(0, static_cast<int>(g + 0.5f), 255);
                int b_final = qBound(0, static_cast<int>(b + 0.5f), 255);

                if (levels > 1)
                {
                    r_final = qRound(r_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                    g_final = qRound(g_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                    b_final = qRound(b_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                }


                if (hasAlpha)
                    result.setPixel(x, y, qRgba(r_final, g_final, b_final, alpha));
                else
                    result.setPixel(x, y, qRgb(r_final, g_final, b_final));
            }
            else
            {

                const int gray_orig = inverse ? 255 - qGray(pixel) : qGray(pixel);
                float gray = (gray_orig - contrast_center) * res_contrast + contrast_center + bright + thres;

                int gray_final = qBound(0, static_cast<int>(gray + 0.5f), 255);

                if (levels > 1)
                {
                    gray_final = qRound(gray_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                }

                if (hasAlpha)
                    result.setPixel(x, y, qRgba(gray_final, gray_final, gray_final, alpha));
                else
                    result.setPixel(x, y, qRgb(gray_final, gray_final, gray_final));
            }
        }
    }

    qDebug() << result.width() << "x" << result.height();

    return result;
}

OrderedDithering::OrderedDithering() :
    IDither(),
    colour_depth(0),
    threshold(1.0f),
    matrix()
{

}

OrderedDithering::OrderedDithering(
    int res_width,
    int res_height,
    float res_brightness,
    float res_contrast,
    bool colour,
    bool inverse,
    int colour_depth,
    float threshold,
    int level)
    : IDither(res_width, res_height, res_brightness, res_contrast, colour, inverse),
    colour_depth(colour_depth),
    threshold(threshold),
    matrix(level)
{

}

OrderedDithering::~OrderedDithering()
{

}

OrderedDithering::OrderedDithering(const OrderedDithering& other)
    : IDither(other),
    colour_depth(other.colour_depth),
    threshold(other.threshold),
    matrix(other.matrix)
{}

OrderedDithering::OrderedDithering(OrderedDithering&& other) noexcept
    : IDither(std::move(other)),
    colour_depth(other.colour_depth),
    threshold(other.threshold),
    matrix(std::move(other.matrix))
{}

OrderedDithering& OrderedDithering::operator=(const OrderedDithering& other) {

    if (this == &other)
        return *this;

    IDither::operator=(other);

    colour_depth = other.colour_depth;

    threshold = other.threshold;

    matrix = other.matrix;

    return *this;
}

OrderedDithering& OrderedDithering::operator=(OrderedDithering&& other) noexcept {
    if (this == &other)
        return *this;

    IDither::operator=(std::move(other));
    colour_depth = other.colour_depth;
    threshold = other.threshold;
    matrix = std::move(other.matrix);

    return *this;
}


const QString& OrderedDithering::getDitherName() {
    static const QString ditherName = "ordered";
    return ditherName;
}

DitheringType OrderedDithering::getDitherType() {
    return DITHERING_ORDERED;
}

int OrderedDithering::getColorDepth() const { return colour_depth; }
void OrderedDithering::setColorDepth(int d) { colour_depth = d; }

float OrderedDithering::getThreshold() const { return threshold; }
void OrderedDithering::setThreshold(float t) { threshold = t; }

int OrderedDithering::getLevel() const { return matrix.getLevel(); }
void OrderedDithering::setLevel(int level) { matrix.setLevel(level); }

IDither* OrderedDithering::copy() const
{
    return static_cast<IDither*>(new OrderedDithering(*this));

}
