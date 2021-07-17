#ifndef TEXTURE_H
#define TEXTURE_H

class Vec;

class Texture {
public:
    virtual ~Texture() = default;

    virtual Vec sample(double u, double v, const Vec& p) const = 0;
};

#endif
