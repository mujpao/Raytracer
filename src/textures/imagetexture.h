#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "math/vec.h"
#include "textures/texture.h"

#include <memory>

class Image;

class ImageTexture : public Texture {
public:
    ImageTexture(std::shared_ptr<Image> image);

    ImageTexture(const std::string& filename);

    Vec sample(double u, double v, const Vec& p) const override;

private:
    std::shared_ptr<Image> m_image;
};

#endif
