#include "light.h"

Light::Light(const Vec& light_color) : m_light_color(light_color) {}

PointLight::PointLight(
    const Vec& attenuation, const Vec& light_color, const Vec& position)
    : Light(light_color), m_position(position), m_atten_const(attenuation[0]),
      m_atten_lin(attenuation[1]), m_atten_quad(attenuation[2]) {}

Vec PointLight::calc_attenuation(double distance) const {
    return light_color()
        / (m_atten_const + m_atten_lin * distance
            + m_atten_quad * distance * distance);
}

DirectionalLight::DirectionalLight(const Vec& light_color, const Vec& direction)
    : Light(light_color), m_direction(Vec::normalize(direction)) {}
