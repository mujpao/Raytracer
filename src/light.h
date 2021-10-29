#ifndef LIGHT_H
#define LIGHT_H

#include "math/vec.h"

class Light {
public:
    Light(const Vec& light_color);

    virtual ~Light() = default;
    Light(const Light&) = default;
    Light(Light&&) = default;
    Light& operator=(const Light&) = default;
    Light& operator=(Light&&) = default;

    inline const Vec& light_color() const { return m_light_color; }

private:
    Vec m_light_color;
};

class PointLight : public Light {
public:
    PointLight(
        const Vec& attenuation, const Vec& light_color, const Vec& position);

    inline const Vec& position() const { return m_position; }

    Vec calc_attenuation(double distance) const;

private:
    Vec m_position;

    double m_atten_const = 1.0, m_atten_lin = 0.0, m_atten_quad = 0.0;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(const Vec& light_color, const Vec& direction);

    inline const Vec& direction() const { return m_direction; }

private:
    Vec m_direction;
};

#endif
