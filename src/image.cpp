#include "image.h"

#include "math/vec.h"
#include "utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"

#include <iostream>

Image::Image(std::size_t width, std::size_t height)
    : m_width(width), m_height(height) {
    m_bytes = new unsigned char[3 * m_width * m_height];
}

Image::Image(const unsigned char* data, std::size_t width, std::size_t height)
    : m_width(width), m_height(height) {
    m_bytes = new unsigned char[3 * m_width * m_height];
    for (std::size_t i = 0; i < 3 * m_width * m_height; ++i) {
        m_bytes[i] = data[i];
    }
}

Image::~Image() {
    delete[] m_bytes;
    m_bytes = 0;
}

Image::Image(const Image& other)
    : m_width(other.m_width), m_height(other.m_height) {
    m_bytes = new unsigned char[3 * m_width * m_height];

    for (std::size_t i = 0; i < 3 * m_width * m_height; ++i) {
        m_bytes[i] = other.m_bytes[i];
    }
}

Image& Image::operator=(const Image& other) {
    if (this == &other)
        return *this;

    delete[] m_bytes;

    m_width = other.m_width;
    m_height = other.m_height;
    m_bytes = new unsigned char[3 * m_width * m_height];

    for (std::size_t i = 0; i < 3 * m_width * m_height; ++i) {
        m_bytes[i] = other.m_bytes[i];
    }

    return *this;
}

Image::Image(Image&& other)
    : m_width(std::move(other.m_width)), m_height(std::move(other.m_height)) {
    m_bytes = other.m_bytes;

    other.m_bytes = 0;
    other.m_width = 0;
    other.m_height = 0;
}

Image& Image::operator=(Image&& other) {
    if (this == &other)
        return *this;

    delete[] m_bytes;

    m_bytes = other.m_bytes;
    m_width = std::move(other.m_width);
    m_height = std::move(other.m_height);

    other.m_bytes = 0;
    other.m_width = 0;
    other.m_height = 0;

    return *this;
}

void Image::save(const std::string& file) const {
    std::cout << "Saving to file: " << file << '\n';
    stbi_write_png(
        file.c_str(), m_width, m_height, 3, (const void*)m_bytes, m_width * 3);
}

void Image::set_pixel_color(
    std::size_t i, std::size_t j, const Vec& color, bool gamma_corrected) {
    // TODO check indices

    unsigned char new_color[3];
    for (int k = 0; k < 3; ++k) {
        double col = gamma_corrected ? std::sqrt(color[k]) : color[k];
        col = Utils::clamp(col * 255.0, 0.0, 255.0);
        new_color[k] = static_cast<unsigned char>(col);
    }

    std::size_t starting_byte = 3 * (i * m_width + j);

    for (std::size_t idx = 0; idx < 3; ++idx) {
        m_bytes[starting_byte + idx] = new_color[idx];
    }
}

std::array<unsigned char, 3> Image::pixel_color(
    std::size_t i, std::size_t j) const {
    // TODO check indices
    std::size_t starting_byte = 3 * (i * m_width + j);
    std::array<unsigned char, 3> result;
    for (std::size_t idx = 0; idx < 3; ++idx) {
        result[idx] = m_bytes[starting_byte + idx];
    }
    return result;
}
