#ifndef SHAPE_H
#define SHAPE_H

#include "shapes/abstractshape.h"

#include <memory>

class Material;

class Shape : public AbstractShape {
public:
    Shape(std::shared_ptr<Material> material);

protected:
    std::shared_ptr<Material> m_material;
};

#endif
