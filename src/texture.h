#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
    virtual ~Texture() = default;

    virtual Vec sample(double u, double v) const = 0;
};

#endif
