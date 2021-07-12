#include "textures/flatcolortexture.h"

FlatColorTexture::FlatColorTexture(const Vec& color) : m_color(color) {}

Vec FlatColorTexture::sample(double, double, const Vec&) const {
    return m_color;
}
