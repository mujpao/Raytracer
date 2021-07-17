#ifndef PERLINTEXTURE_H
#define PERLINTEXTURE_H

#include "textures/texture.h"

#include <array>

#include "math/vec.h"

class PerlinNoise {
public:
    PerlinNoise();

    double operator()(const Vec& p) const;

private:
    std::size_t hash(int x, int y, int z) const;

    static double smooth_remap(double a, double b, double t);

    const static std::size_t m_NUM_POINTS = 256;
    const static int m_MASK = m_NUM_POINTS - 1;

    std::array<Vec, m_NUM_POINTS> m_gradients;
    std::array<std::size_t, 2 * m_NUM_POINTS> m_perm_table;
};

class PerlinTexture : public Texture {
public:
    PerlinTexture(double freq = 4.0, double amp = 1.0, unsigned int layers = 1,
        double freq_multiplier = 2.0, double amp_multiplier = 0.5);

    Vec sample(double u, double v, const Vec& p) const override;

protected:
    double calc_noise(const Vec& p) const;

private:
    PerlinNoise m_noise; // TODO avoid recalculating every time

    const double m_freq, m_amp, m_freq_mul, m_amp_mul;
    const unsigned int m_layers;
};

class TurbulentNoiseTexture : public PerlinTexture {
public:
    TurbulentNoiseTexture(double freq = 4.0, double amp = 1.0,
        unsigned int layers = 1, double freq_multiplier = 2.0,
        double amp_multiplier = 0.5);

    Vec sample(double u, double v, const Vec& p) const override;
};

class MarbleTexture : public PerlinTexture {
public:
    MarbleTexture(double scale = 0.01, double freq = 4.0, double amp = 1.0,
        unsigned int layers = 1, double freq_multiplier = 2.0,
        double amp_multiplier = 0.5);

    Vec sample(double u, double v, const Vec& p) const override;

private:
    double m_scale;
};

#endif
