#include "random.h"


QImage RandomDithering::ditherImage(const QImage& image)
{
#ifdef _DEBUG_
    qDebug() << "=== RandomDithering Parameters ===";
    qDebug() << "Resolution:" << res_width << "x" << res_height;
    qDebug() << "Brightness:" << res_brightness << "Contrast:" << res_contrast;
    qDebug() << "Colour:" << colour << "Inverse:" << inverse;
    qDebug() << "Colour depth:" << colour_depth << "Threshold:" << threshold;
#endif

    QImage result = image.scaled(res_width, res_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    const int bits = qBound(1, colour_depth, 8);
    const int levels = 1 << bits;

    const float bright = (res_brightness - 1.0f) * 255.0f;
    const float contrast_center = 127.5f;

    const bool hasAlpha = result.hasAlphaChannel();

#ifdef _DEBUG_
    qDebug() << "Bits:" << bits << "Levels:" << levels;
    qDebug() << "Has alpha:" << hasAlpha;
#endif

    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            const QRgb pixel = result.pixel(x, y);

            // ЕДИНСТВЕННОЕ ОТЛИЧИЕ: случайный порог вместо матрицы
            float thres = (dist(rng) - 0.5f) * 2.0f * threshold * 255.0f;

            const int alpha = qAlpha(pixel);

            if (colour) {
                const int r_orig = inverse ? 255 - qRed(pixel) : qRed(pixel);
                const int g_orig = inverse ? 255 - qGreen(pixel) : qGreen(pixel);
                const int b_orig = inverse ? 255 - qBlue(pixel) : qBlue(pixel);

                float r = (r_orig - contrast_center) * res_contrast + contrast_center + bright + thres;
                float g = (g_orig - contrast_center) * res_contrast + contrast_center + bright + thres;
                float b = (b_orig - contrast_center) * res_contrast + contrast_center + bright + thres;

                int r_final = qBound(0, static_cast<int>(r + 0.5f), 255);
                int g_final = qBound(0, static_cast<int>(g + 0.5f), 255);
                int b_final = qBound(0, static_cast<int>(b + 0.5f), 255);

                if (levels > 1) {
                    r_final = qRound(r_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                    g_final = qRound(g_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                    b_final = qRound(b_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                }

                if (hasAlpha)
                    result.setPixel(x, y, qRgba(r_final, g_final, b_final, alpha));
                else
                    result.setPixel(x, y, qRgb(r_final, g_final, b_final));
            } else {
                const int gray_orig = inverse ? 255 - qGray(pixel) : qGray(pixel);
                float gray = (gray_orig - contrast_center) * res_contrast + contrast_center + bright + thres;

                int gray_final = qBound(0, static_cast<int>(gray + 0.5f), 255);

                if (levels > 1) {
                    gray_final = qRound(gray_final * (levels - 1) / 255.0f) * (255 / (levels - 1));
                }

                if (hasAlpha)
                    result.setPixel(x, y, qRgba(gray_final, gray_final, gray_final, alpha));
                else
                    result.setPixel(x, y, qRgb(gray_final, gray_final, gray_final));
            }
        }
    }

    return result;
}

RandomDithering::RandomDithering()
    : IDither()
    , colour_depth(2)
    , threshold(0.1f)
    , rng(std::random_device{}())
    , dist(0.0f, 1.0f)
{
}

RandomDithering::RandomDithering(int w, int h, float b, float c, bool col, bool inv, int depth, float thresh)
    : IDither(w, h, b, c, col, inv)
    , colour_depth(depth)
    , threshold(thresh)
    , rng(std::random_device{}())
    , dist(0.0f, 1.0f)
{
}

const QString& RandomDithering::getDitherName() {
    static const QString ditherName = "random";
    return ditherName;
}

DitheringType RandomDithering::getDitherType() {
    return DITHERING_RANDOM;
}

IDither* RandomDithering::copy() const
{
    return static_cast<IDither*>(new RandomDithering(*this));
}
