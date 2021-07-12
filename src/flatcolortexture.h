#ifndef FLATCOLORTEXTURE_H
#define FLATCOLORTEXTURE_H

#include "math/vec.h"
#include "texture.h"

class FlatColorTexture : public Texture {
public:
    FlatColorTexture(const Vec& color);

    Vec sample(double u, double v) const override;

private:
    Vec m_color;
};

#endif
