#include "orderedDithering.h"

static float* generateBayerMatrix(int size)
{
    if (size == 1)
    {
        float* ptr = new float[1]{ 0.0f };
        return ptr;
    }

    int half = size / 2;
    float* smaller = generateBayerMatrix(half);
    float* matrix = new float[size * size];

    for (int i = 0; i < half; ++i)
    {
        for (int j = 0; j < half; ++j)
        {
            float v = 4 * smaller[i * half + j];
            matrix[i * size + j] = v;
            matrix[i * size + j + half] = v + 2;
            matrix[(i + half) * size + j] = v + 3;
            matrix[(i + half) * size + j + half] = v + 1;
        }
    }

    delete[] smaller;
    return matrix;
}

BayerMatrix::BayerMatrix()
    : level(0), matrix_ptr(nullptr)
{
    setLevel(0);
}

BayerMatrix::BayerMatrix(int l)
    : level(l), matrix_ptr(nullptr)
{
    setLevel(l);
}

BayerMatrix::~BayerMatrix()
{
    delete[] matrix_ptr;
    matrix_ptr = nullptr;
    level = 0;
}

BayerMatrix::BayerMatrix(const BayerMatrix& other)
    : level(other.level), matrix_ptr(nullptr)
{
    if (other.matrix_ptr && level >= 0)
    {
        int size = 1 << level;
        matrix_ptr = new float[size * size];
        std::copy(other.matrix_ptr, other.matrix_ptr + size * size, matrix_ptr);
    }
}

BayerMatrix::BayerMatrix(BayerMatrix&& other) noexcept
    : level(other.level), matrix_ptr(other.matrix_ptr)
{
    other.matrix_ptr = nullptr;
    other.level = 0;
}

BayerMatrix& BayerMatrix::operator=(const BayerMatrix& other)
{
    if (this == &other) return *this;

    delete[] matrix_ptr;
    matrix_ptr = nullptr;
    level = other.level;

    if (other.matrix_ptr && level >= 0)
    {
        int size = 1 << level;
        matrix_ptr = new float[size * size];
        std::copy(other.matrix_ptr, other.matrix_ptr + size * size, matrix_ptr);
    }

    return *this;
}

BayerMatrix& BayerMatrix::operator=(BayerMatrix&& other) noexcept
{
    if (this == &other) return *this;

    delete[] matrix_ptr;

    level = other.level;
    matrix_ptr = other.matrix_ptr;

    other.matrix_ptr = nullptr;
    other.level = 0;

    return *this;
}

void BayerMatrix::setLevel(int input_level)
{
    delete[] matrix_ptr;
    matrix_ptr = nullptr;

    level = input_level;
    int size = 1 << input_level;

    matrix_ptr = generateBayerMatrix(size);

    if (matrix_ptr)
    {
        float N2 = 2.0f * (size * size - 1.0f);
        if (N2 != 0.0f)
            for (int i = 0; i < size * size; ++i)
                matrix_ptr[i] = matrix_ptr[i] / N2 - 0.25f;
    }
}

int BayerMatrix::getLevel() const
{
    return level;
}

float* BayerMatrix::operator[](int k) const
{
    int size = 1 << level;
    return &matrix_ptr[k * size];
}


