#ifndef IMAGE_H
#define IMAGE_H

#include <array>
#include <string>

class Vec;

class Image {
public:
    Image(std::size_t width, std::size_t height);

    Image(const std::string& filename, bool flip_y = false);

    virtual ~Image();

    Image(const Image& other);
    Image& operator=(const Image& other);

    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;

    inline std::size_t width() const { return m_width; }
    inline std::size_t height() const { return m_height; }

    void save(const std::string& file) const;

    void set_pixel_color(std::size_t i, std::size_t j, const Vec& color,
        bool gamma_corrected = false);

    std::array<unsigned char, 3> pixel_color(
        std::size_t i, std::size_t j) const;

    // Color of row i, column j, starting from top left
    Vec pixel_color_vec(std::size_t i, std::size_t j) const;

private:
    std::size_t m_width, m_height;

    unsigned char* m_bytes;
};

#endif
