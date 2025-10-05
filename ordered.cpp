#include "orderedDithering.h"

// Конструктор по умолчанию
OrderedDithering::OrderedDithering()
    : IDither(),
    colour_depth(0),
    threshold(1.0f),
    matrix(),
    invert(false)
{}

// Конструктор с параметрами
OrderedDithering::OrderedDithering(
    int res_width,
    int res_height,
    float res_brightness,
    float res_contrast,
    bool colour,
    bool inverse,
    int colour_depth,
    float threshold,
    bool invert,
    int level)
    : IDither(res_width, res_height, res_brightness, res_contrast, colour, inverse),
    colour_depth(colour_depth),
    threshold(threshold),
    matrix(level),
    invert(invert)
{}

// Деструктор
OrderedDithering::~OrderedDithering() {}

// Конструктор копирования (глубокое копирование matrix)
OrderedDithering::OrderedDithering(const OrderedDithering& other)
    : IDither(other),
    colour_depth(other.colour_depth),
    threshold(other.threshold),
    matrix(other.matrix), // matrix должен корректно копировать данные
    invert(other.invert)
{}

// Конструктор перемещения
OrderedDithering::OrderedDithering(OrderedDithering&& other) noexcept
    : IDither(std::move(other)),
    colour_depth(other.colour_depth),
    threshold(other.threshold),
    matrix(std::move(other.matrix)),
    invert(other.invert)
{}

// Оператор присваивания копированием
OrderedDithering& OrderedDithering::operator=(const OrderedDithering& other) {
    if (this == &other) return *this;

    IDither::operator=(other);
    colour_depth = other.colour_depth;
    threshold = other.threshold;
    matrix = other.matrix; // matrix должен корректно копировать данные
    invert = other.invert;

    return *this;
}

// Оператор присваивания перемещением
OrderedDithering& OrderedDithering::operator=(OrderedDithering&& other) noexcept {
    if (this == &other) return *this;

    IDither::operator=(std::move(other));
    colour_depth = other.colour_depth;
    threshold = other.threshold;
    matrix = std::move(other.matrix);
    invert = other.invert;

    return *this;
}

// Имя дизеринга
const QString& OrderedDithering::getDitherName() {
    static const QString ditherName = "ordered";
    return ditherName;
}

// Тип дизеринга
DitheringType OrderedDithering::getDitherType() {
    return DITHERING_ORDERED;
}

// Геттеры/Сеттеры
int OrderedDithering::getColorDepth() const { return colour_depth; }
void OrderedDithering::setColorDepth(int d) { colour_depth = d; }

float OrderedDithering::getThreshold() const { return threshold; }
void OrderedDithering::setThreshold(float t) { threshold = t; }

int OrderedDithering::getLevel() const { return matrix.getLevel(); }
void OrderedDithering::setLevel(int level) { matrix.setLevel(level); }

bool OrderedDithering::getInvert() const { return invert; }
void OrderedDithering::setInvert(bool i) { invert = i; }

// Метод копирования (создаёт полноценную копию)
IDither* OrderedDithering::copy() const {
    return new OrderedDithering(*this);
}

// Основной метод дизеринга
QImage OrderedDithering::ditherImage(const QImage& image) {
    const int size = 1 << matrix.getLevel();
    QImage result = image.convertToFormat(QImage::Format_ARGB32)
                        .scaled(res_width, res_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    const int bits = qBound(1, colour_depth, 8);
    const int levels = 1 << bits;
    const float bright = (res_brightness - 1.0f) * 255.0f;
    const float contrast_center = 127.5f;
    const bool hasAlpha = result.hasAlphaChannel();

#ifdef _DEBUG_
    qDebug() << "invert: " << invert;
#endif

    for (int y = 0; y < result.height(); y++) {
        const int matrix_y = y % size;
        float* matrix_row = matrix[matrix_y];

        for (int x = 0; x < result.width(); x++) {
            const QRgb pixel = result.pixel(x, y);
            const float thres = (invert ? -1.0f : 1.0f) * threshold * matrix_row[x % size] * 255.0f;
            const int alpha = hasAlpha ? qAlpha(pixel) : 255;

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

#ifdef _DEBUG_
    qDebug() << result.width() << "x" << result.height();
#endif
    return result;
}
