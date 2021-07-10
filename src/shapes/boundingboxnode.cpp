#include "shapes/boundingboxnode.h"

#include "boundingbox.h"
#include "intersectioninfo.h"
#include "shapes/shapelist.h"
#include "utils.h"

#include <algorithm>

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

    if (end - start == 1) {
        left = shapes[start];
        m_box = left->box();
        return;
    }

    int axis = Utils::random_int(0, 2);

    auto comp = [axis](const auto& a, const auto& b) {
        return a->box().min()[axis] < b->box().min()[axis];
    };

    if (end - start == 2) {
        if (comp(shapes[start], shapes[start + 1])) {
            left = shapes[start];
            right = shapes[start + 1];
        } else {
            left = shapes[start + 1];
            right = shapes[start];
        }

    } else {
        std::sort(shapes.begin() + start, shapes.begin() + end, comp);

        int mid = (end - start) / 2 + start;

        left = std::make_shared<BoundingBoxNode>(shapes, start, mid);
        right = std::make_shared<BoundingBoxNode>(shapes, mid, end);
    }

    m_box = BoundingBox::combine(left->box(), right->box());
}

// std::ostream& operator<<(std::ostream& os, const BoundingBoxNode& b) {
//     // TODO remove
//     os << "node: " << b.box().min() << ", " << b.box().max() << '\n';
//     os << "(";
//     if (b.left) {
//         if (auto left = dynamic_cast<BoundingBoxNode*>(b.left.get())) {
//             os << *left;
//         } else {
//             os << "leaf";
//         }
//     }
//     if (b.right) {
//         if (auto right = dynamic_cast<BoundingBoxNode*>(b.right.get())) {
//             os << *right;
//         } else {
//             os << "leaf";
//         }
//     }
//     os << ")";

//     return os;
// }
