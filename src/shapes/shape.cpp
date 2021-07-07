#include "shapes/shape.h"

Shape::Shape(std::shared_ptr<Material> material)
    : m_material(std::move(material)) {}
