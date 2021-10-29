#ifndef TEXTURE_H
#define TEXTURE_H

class Vec;

class Texture {
public:
    Texture() = default;

    virtual ~Texture() = default;
    Texture(const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) = default;
    Texture& operator=(Texture&&) = default;

    virtual Vec sample(double u, double v, const Vec& p) const = 0;
};

#endif
