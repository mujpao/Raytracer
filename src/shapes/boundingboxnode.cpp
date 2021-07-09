#include "shapes/boundingboxnode.h"

#include "boundingbox.h"
#include "intersectioninfo.h"
#include "shapes/shapelist.h"

#include <algorithm>
#include <iostream>

BoundingBoxNode::BoundingBoxNode(std::shared_ptr<ShapeList> shape_list)
    : m_start(0), m_end(shape_list->shapes().size()) {
    auto vec = shape_list->shapes();
    build_tree(vec, 0, vec.size());
}

bool BoundingBoxNode::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    if (m_box.intersect(ray, t_min, t_max)) {
        bool hit_left = left
            ? left->intersect(ray, t_min, t_max, intersection_info)
            : false;

        if (hit_left) {
            t_max = std::min(t_max, intersection_info.t_hit);
        }

        bool hit_right = right
            ? right->intersect(ray, t_min, t_max, intersection_info)
            : false;

        if (hit_left || hit_right) {
            return true;
        }
    }
    return false;
}

BoundingBoxNode::BoundingBoxNode(
    std::vector<std::shared_ptr<AbstractShape>>& shapes, std::size_t start,
    std::size_t end)
    : m_start(start), m_end(end) {
    build_tree(shapes, m_start, m_end);
}

void BoundingBoxNode::build_tree(
    std::vector<std::shared_ptr<AbstractShape>>& shapes, std::size_t start,
    std::size_t end) {
    std::cout << "start: " << start << ", end: " << end << std::endl;
    if (end - start == 1) {
        left = *(shapes.begin() + start);
        m_box = left->box();
        return;
    } else if (end - start == 2) {
        left = *(shapes.begin() + start);
        right = *(shapes.begin() + end - 1);
        m_box = BoundingBox::combine(left->box(), right->box());
        return;
    }

    auto comp = [](const auto& a, const auto& b) {
        // TODO
        // std::cout << a->box().min()[0] << ", " << b->box().min()[0] << '\n';

        return a->box().min()[0] < b->box().min()[0];
    };
    std::sort(shapes.begin() + start, shapes.begin() + end, comp);

    int mid = (end - start) / 2 + start;
    std::cout << "mid: " << mid << '\n';

    left = std::make_shared<BoundingBoxNode>(shapes, start, mid);
    right = std::make_shared<BoundingBoxNode>(shapes, mid, end);

    m_box = BoundingBox::combine(left->box(), right->box());
}

std::ostream& operator<<(std::ostream& os, const BoundingBoxNode& b) {
    os << "node: " << b.box().min() << ", " << b.box().max() << '\n';
    os << "(";
    if (b.left) {
        if (auto left = dynamic_cast<BoundingBoxNode*>(b.left.get())) {
            os << *left;
        } else {
            os << "leaf";
        }
    }
    if (b.right) {
        if (auto right = dynamic_cast<BoundingBoxNode*>(b.right.get())) {
            os << *right;
        } else {
            os << "leaf";
        }
    }
    os << ")";

    return os;
}
