#ifndef RANDOMDITHERING_H
#define RANDOMDITHERING_H

#include "idither.h"
#include <random>

class RandomDithering : public IDither {
private:
    int colour_depth;
    float threshold;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;

public:
    RandomDithering();
    RandomDithering(int w, int h, float b, float c, bool col, bool inv, int depth, float thresh);
    ~RandomDithering() override = default;

    QImage ditherImage(const QImage& image) override;
    const QString& getDitherName() override;
    DitheringType getDitherType() override;

    int getColorDepth() const { return colour_depth; }
    void setColorDepth(int d) { colour_depth = d; }

    float getThreshold() const { return threshold; }
    void setThreshold(float t) { threshold = t; }

    IDither* copy() const override;
};

#endif
