#include "image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"


Image::Image(unsigned int width, unsigned int height)
: m_width(width), m_height(height)
{
	m_bytes = new unsigned char[3 * m_width * m_height]; // 3 bytes for each pixel
}

Image::Image(const unsigned char *data, unsigned int width, unsigned int height)
: m_width(width), m_height(height)
{
	m_bytes = new unsigned char[3 * m_width * m_height];
	for (std::size_t i = 0; i < 3 * m_width * m_height; ++i) {
		m_bytes[i] = data[i];
	}
}

Image::~Image() {
	delete[] m_bytes;
	m_bytes = 0;
}

Image::Image(const Image &other)
: m_width(other.m_width), m_height(other.m_height)
{
	m_bytes = new unsigned char[3 * m_width * m_height];

	for (std::size_t i = 0; i < 3 * m_width * m_height; ++i) {
		m_bytes[i] = other.m_bytes[i];
	}
}

Image& Image::operator=(const Image &other) {
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

Image::Image(Image &&other)
: m_width(std::move(other.m_width)), m_height(std::move(other.m_height))
{
	m_bytes = other.m_bytes;
	
	other.m_bytes = 0;
	other.m_width = 0;
	other.m_height = 0;
}

Image& Image::operator=(Image &&other) {
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

void Image::save(const std::string &file) const {
	stbi_write_png(file.c_str(), m_width, m_height, 3, (const void *)m_bytes, m_width * 3);
}

void Image::set_pixel_color(unsigned int i, unsigned int j, const unsigned char color[]) {
	// TODO check indices
	std::size_t starting_byte = (std::size_t)3 * ((std::size_t)i * m_width + j);

	for (std::size_t idx = 0; idx < 3; ++idx) {
		m_bytes[starting_byte + idx] = color[idx];
	}
}

std::vector<unsigned char> Image::pixel_color(unsigned int i, unsigned int j) const {
	// TODO check indices
	std::size_t starting_byte = (std::size_t)3 * ((std::size_t)i * m_width + j);
	std::vector<unsigned char> result(3, 0);
	for (std::size_t idx = 0; idx < 3; ++idx) {
		result[idx] = m_bytes[starting_byte + idx];
	}
	return result;
}
