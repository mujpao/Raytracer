#ifndef FLATCOLORTEXTURE_H
#define FLATCOLORTEXTURE_H

#include "math/vec.h"
#include "textures/texture.h"

class FlatColorTexture : public Texture {
public:
    FlatColorTexture(const Vec& color);

    Vec sample(double u, double v, const Vec& p) const override;

private:
    Vec m_color;
};

#endif
