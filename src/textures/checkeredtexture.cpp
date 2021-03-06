#include "textures/checkeredtexture.h"

#include "textures/flatcolortexture.h"

#include <cmath>

CheckeredTexture::CheckeredTexture(double amplitude)
    : m_odd(std::make_shared<FlatColorTexture>(Vec(0.0, 0.0, 0.0))),
      m_even(std::make_shared<FlatColorTexture>(Vec(1.0, 1.0, 1.0))),
      m_amplitude(amplitude) {}

CheckeredTexture::CheckeredTexture(
    const Vec& odd, const Vec& even, double amplitude)
    : m_odd(std::make_shared<FlatColorTexture>(odd)),
      m_even(std::make_shared<FlatColorTexture>(even)), m_amplitude(amplitude) {
}

CheckeredTexture::CheckeredTexture(std::shared_ptr<Texture> odd,
    std::shared_ptr<Texture> even, double amplitude)
    : m_odd(std::move(odd)), m_even(std::move(even)), m_amplitude(amplitude) {}

Vec CheckeredTexture::sample(double u, double v, const Vec& p) const {
    double parity = std::sin(m_amplitude * p[0]) * sin(m_amplitude * p[1])
        * sin(m_amplitude * p[2]);

    if (parity < 0.0) {
        return m_odd->sample(u, v, p);
    }
    return m_even->sample(u, v, p);
}
