#ifndef BOUNDINGBOXNODE_H
#define BOUNDINGBOXNODE_H

#include "shapes/abstractshape.h"

#include <memory>
#include <vector>

class ShapeList;

class BoundingBoxNode : public AbstractShape {
public:
    // size of shape_list must be at least 1
    BoundingBoxNode(std::shared_ptr<ShapeList> shape_list);

    // TODO make private?
    BoundingBoxNode(std::vector<std::shared_ptr<AbstractShape>>& shapes,
        std::size_t start, std::size_t end);

    bool intersect(const Ray& ray, double& t_hit,
        IntersectionInfo& intersection_info) const override;

    std::shared_ptr<AbstractShape> left;
    std::shared_ptr<AbstractShape> right;

    friend std::ostream& operator<<(std::ostream& os, const BoundingBoxNode& b);

private:
    void build_tree(std::vector<std::shared_ptr<AbstractShape>>& shapes,
        std::size_t start, std::size_t end);

    std::size_t m_start, m_end;
};

#endif
