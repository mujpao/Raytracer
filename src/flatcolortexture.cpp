#include "flatcolortexture.h"

FlatColorTexture::FlatColorTexture(const Vec& color) : m_color(color) {}

Vec FlatColorTexture::sample(double, double) const { return m_color; }
