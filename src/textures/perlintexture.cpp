#include "textures/perlintexture.h"

#include "math/transform.h"
#include "math/vec.h"
#include "utils.h"

#include <cmath>

PerlinNoise::PerlinNoise() {
    // TODO seed, uniform distribution
    for (std::size_t i = 0; i < m_NUM_POINTS; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            m_gradients[i][j] = Utils::random_double(-1.0, 1.0);
        }

        m_gradients[i] = Vec::normalize(m_gradients[i]);
        m_perm_table[i] = i;
    }

    for (std::size_t i = 0; i < m_NUM_POINTS; ++i) {
        int j = Utils::random_int(0, m_NUM_POINTS - 1);
        std::swap(m_perm_table[i], m_perm_table[j]);
        m_perm_table[i + m_NUM_POINTS] = m_perm_table[i];
    }
}

double PerlinNoise::operator()(const Vec& p) const {
    Vec t;
    std::array<int, 3> pi0;
    std::array<int, 3> pi1;

    for (int i = 0; i < 3; ++i) {
        int pi = static_cast<int>(std::floor(p[i]));
        t[i] = p[i] - pi;

        pi0[i] = pi & m_MASK;
        pi1[i] = (pi0[i] + 1) & m_MASK;
    }

    Vec c000 = m_gradients[hash(pi0[0], pi0[1], pi0[2])];
    Vec c001 = m_gradients[hash(pi0[0], pi0[1], pi1[2])];
    Vec c010 = m_gradients[hash(pi0[0], pi1[1], pi0[2])];
    Vec c011 = m_gradients[hash(pi0[0], pi1[1], pi1[2])];
    Vec c100 = m_gradients[hash(pi1[0], pi0[1], pi0[2])];
    Vec c101 = m_gradients[hash(pi1[0], pi0[1], pi1[2])];
    Vec c110 = m_gradients[hash(pi1[0], pi1[1], pi0[2])];
    Vec c111 = m_gradients[hash(pi1[0], pi1[1], pi1[2])];

    Vec v000 = t - Vec(0.0, 0.0, 0.0);
    Vec v001 = t - Vec(0.0, 0.0, 1.0);
    Vec v010 = t - Vec(0.0, 1.0, 0.0);
    Vec v011 = t - Vec(0.0, 1.0, 1.0);
    Vec v100 = t - Vec(1.0, 0.0, 0.0);
    Vec v101 = t - Vec(1.0, 0.0, 1.0);
    Vec v110 = t - Vec(1.0, 1.0, 0.0);
    Vec v111 = t - Vec(1.0, 1.0, 1.0);

    for (int i = 0; i < 3; ++i) {
        t[i] = smooth_remap(0.0, 1.0, t[i]);
    }

    double a = Utils::lerp(
        Transform::dot(c000, v000), Transform::dot(c100, v100), t[0]);
    double b = Utils::lerp(
        Transform::dot(c010, v010), Transform::dot(c110, v110), t[0]);

    double c = Utils::lerp(
        Transform::dot(c001, v001), Transform::dot(c101, v101), t[0]);
    double d = Utils::lerp(
        Transform::dot(c011, v011), Transform::dot(c111, v111), t[0]);

    double e = Utils::lerp(a, b, t[1]);
    double f = Utils::lerp(c, d, t[1]);

    return Utils::lerp(e, f, t[2]);
}

std::size_t PerlinNoise::hash(int x, int y, int z) const {
    return m_perm_table[m_perm_table[m_perm_table[x] + y] + z];
}

double PerlinNoise::smooth_remap(double a, double b, double t) {
    return Utils::lerp(a, b, t * t * (3 - 2 * t));
}

PerlinTexture::PerlinTexture(double freq, double amp, unsigned int layers,
    double freq_multiplier, double amp_multiplier)
    : m_freq(freq), m_amp(amp), m_freq_mul(freq_multiplier),
      m_amp_mul(amp_multiplier), m_layers(layers) {}

Vec PerlinTexture::sample(double, double, const Vec& p) const {
    return Vec(1.0, 1.0, 1.0) * 0.5 * (calc_noise(p) + 1.0);
}

double PerlinTexture::calc_noise(const Vec& p) const {
    double f = m_freq;
    double a = m_amp;
    double result = 0.0;

    for (unsigned int i = 0; i < m_layers; ++i) {
        result += a * m_noise(f * p);
        f *= m_freq_mul;
        a *= m_amp_mul;
    }

    return result;
}

TurbulentNoiseTexture::TurbulentNoiseTexture(double freq, double amp,
    unsigned int layers, double freq_multiplier, double amp_multiplier)
    : PerlinTexture(freq, amp, layers, freq_multiplier, amp_multiplier) {}

Vec TurbulentNoiseTexture::sample(double, double, const Vec& p) const {
    return Vec(1.0, 1.0, 1.0) * std::abs(calc_noise(p));
}

MarbleTexture::MarbleTexture(double scale, double freq, double amp,
    unsigned int layers, double freq_multiplier, double amp_multiplier)
    : PerlinTexture(freq, amp, layers, freq_multiplier, amp_multiplier),
      m_scale(scale) {}

Vec MarbleTexture::sample(double, double, const Vec& p) const {

    double noise = 0.5
        * (std::sin((95.0 * p[0] + 10.0 * std::abs(calc_noise(p))) * 2
               * Utils::PI * m_scale)
            + 1.0);
    return Vec(1.0, 1.0, 1.0) * noise;
}
