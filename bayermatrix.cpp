#include "orderedDithering.h"

float* generateBayerMatrix(int level)
{
    if (level <= 1) {
        float* ptr = new float[1];
        ptr[0] = 0;
        return ptr;
    }

    if (level == 1)
    {
        float* ptr = new float[1];
        ptr[0] = 0;
        return ptr;
    }

    const int half = level >> 1;
    float* smaller = generateBayerMatrix(half);
    float* matrix = new float[level * level];

    for (int i = 0; i < half; ++i)
    {
        for (int j = 0; j < half; ++j)
        {
            const float v = 4 * smaller[i * half + j];  // Исправлено: i * half + j

            matrix[i * level + j] = v;
            matrix[i * level + j + half] = v + 2;
            matrix[(i + half) * level + j] = v + 3;
            matrix[(i + half) * level + j + half] = v + 1;
        }
    }

    delete[] smaller;  // Не забываем освободить память!
    return matrix;
}

void BayerMatrix::setLevel(int input_level)
{
    // Освобождаем старую память
    delete[] matrix_ptr;

    int matrix_size = 1 << input_level;  // 2^input_level
    this->level = matrix_size;  // Сохраняем реальный размер матрицы
    this->matrix_ptr = generateBayerMatrix(matrix_size);

    if (!matrix_ptr) return;

    float max = matrix_ptr[0];
    for (int i = 1; i < matrix_size * matrix_size; i++) {
        max = std::max(max, matrix_ptr[i]);
    }

    max *= 2;

    for (int i = 0; i < matrix_size * matrix_size; i++) {
        matrix_ptr[i] /= max;
        matrix_ptr[i] -= 0.25f;
    }
}

int BayerMatrix::getLevel() const
{
    return level;
}

float* BayerMatrix::operator[](int k) const
{
    return &matrix_ptr[k*level];
}

BayerMatrix::BayerMatrix() :
    level(0),
    matrix_ptr(nullptr)
{
    setLevel(0);
}

BayerMatrix::BayerMatrix(int l)
    : level(l)
    , matrix_ptr(nullptr)
{
    setLevel(l);
}


BayerMatrix::~BayerMatrix()
{
    if (matrix_ptr)
    {
        delete[] matrix_ptr;
        matrix_ptr = nullptr;
    }
    level = 0;
}

BayerMatrix::BayerMatrix(const BayerMatrix& other)
    : level(other.level)
    , matrix_ptr(nullptr)
{
    if (other.matrix_ptr && level > 0)
    {
        matrix_ptr = new float[level * level];
        std::copy(other.matrix_ptr, other.matrix_ptr + level * level, matrix_ptr);
    }
}

BayerMatrix::BayerMatrix(BayerMatrix&& other) noexcept
    : level(other.level)
    , matrix_ptr(other.matrix_ptr)
{
    other.level = 0;
    other.matrix_ptr = nullptr;
}

BayerMatrix& BayerMatrix::operator=(const BayerMatrix& other)
{

    if (this == &other)
        return *this;

    delete[] matrix_ptr;

    level = other.level;
    matrix_ptr = nullptr;

    if (other.matrix_ptr && level > 0)
    {
        matrix_ptr = new float[level * level];
        std::copy(other.matrix_ptr, other.matrix_ptr + level * level, matrix_ptr);
    }

    return *this;
}

BayerMatrix& BayerMatrix::operator=(BayerMatrix&& other) noexcept
{

    if (this == &other)
        return *this;

    delete[] matrix_ptr;

    level = other.level;
    matrix_ptr = other.matrix_ptr;

    other.level = 0;
    other.matrix_ptr = nullptr;

    return *this;
}
