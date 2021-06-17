#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

class Image {
public:
	Image(unsigned int width, unsigned int height);
	// Makes a copy of data
	Image(const unsigned char *data, unsigned int width, unsigned int height);
	Image(const Image &other);
	virtual ~Image();

	inline unsigned int width() const { return m_width; }
	inline unsigned int height() const { return m_height; }

	void save(const std::string &file) const;

	void set_pixel_color(unsigned int i, unsigned int j, const unsigned char color[]);
	std::vector<unsigned char> pixel_color(unsigned int i, unsigned int j) const;

private:
	unsigned int m_width, m_height;
	
	unsigned char * m_bytes;
};

#endif
