#include "textures/imagetexture.h"

#include "image.h"
#include "utils.h"

ImageTexture::ImageTexture(std::shared_ptr<Image> image)
    : m_image(std::move(image)) {}

ImageTexture::ImageTexture(const std::string& filename)
    : m_image(std::make_shared<Image>(filename)) {}

Vec ImageTexture::sample(double u, double v, const Vec&) const {
    std::size_t i = (1.0 - Utils::clamp(v, 0.0, 1.0)) * (m_image->height() - 1);
    std::size_t j = Utils::clamp(u, 0.0, 1.0) * (m_image->width() - 1);

    return m_image->pixel_color_vec(i, j);
}
