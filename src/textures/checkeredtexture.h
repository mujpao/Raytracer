#ifndef CHECKEREDTEXTURE_H
#define CHECKEREDTEXTURE_H

#include "math/vec.h"
#include "textures/texture.h"

#include <memory>

class CheckeredTexture : public Texture {
public:
    CheckeredTexture(double amplitude = 1.0);

    CheckeredTexture(const Vec& odd, const Vec& even, double amplitude = 1.0);

    CheckeredTexture(std::shared_ptr<Texture> odd,
        std::shared_ptr<Texture> even, double amplitude = 1.0);

    Vec sample(double u, double v, const Vec& p) const override;

private:
    std::shared_ptr<Texture> m_odd, m_even;

    double m_amplitude;
};

#endif
