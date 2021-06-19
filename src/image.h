#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

class Image {
public:
	Image(unsigned int width, unsigned int height);
	Image(const unsigned char *data, unsigned int width, unsigned int height);

	virtual ~Image();

	Image(const Image &other);
	Image& operator=(const Image &other);

	Image(Image &&other);
	Image& operator=(Image &&other);

	inline unsigned int width() const { return m_width; }
	inline unsigned int height() const { return m_height; }

	void save(const std::string &file) const;

	void set_pixel_color(unsigned int i, unsigned int j, const unsigned char color[]);

	// TODO return value?
	std::vector<unsigned char> pixel_color(unsigned int i, unsigned int j) const;

private:
	unsigned int m_width, m_height;
	
	unsigned char * m_bytes; // TODO
};

#endif
