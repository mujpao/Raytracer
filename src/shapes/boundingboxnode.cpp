#include "shapes/boundingboxnode.h"

#include "boundingbox.h"
#include "intersectioninfo.h"
#include "shapes/shapelist.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <sstream>

BoundingBoxNode::BoundingBoxNode(std::shared_ptr<ShapeList> shape_list)
    : m_start(0), m_end(shape_list->shapes().size()) {
    auto vec = shape_list->shapes();
    build_tree(vec, 0, vec.size());
}

bool BoundingBoxNode::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    if (m_box.intersect(ray, t_min, t_max)) {
        bool hit_left = m_left
            ? m_left->intersect(ray, t_min, t_max, intersection_info)
            : false;

        if (hit_left) {
            t_max = std::min(t_max, intersection_info.t_hit);
        }

        bool hit_right = m_right
            ? m_right->intersect(ray, t_min, t_max, intersection_info)
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
        m_left = shapes[start];
        m_box = m_left->box();
        return;
    }

    int axis = Utils::random_int(0, 2);
    std::cout << "axis: " << axis << std::endl;
    auto comp = [axis](const auto& a, const auto& b) {
        return a->box().min()[axis] < b->box().min()[axis];
    };

    if (end - start == 2) {
        if (comp(shapes[start], shapes[start + 1])) {
            m_left = shapes[start];
            m_right = shapes[start + 1];
        } else {
            m_left = shapes[start + 1];
            m_right = shapes[start];
        }

    } else {
        std::sort(shapes.begin() + start, shapes.begin() + end, comp);

        int mid = (end - start) / 2 + start;

        m_left = std::make_shared<BoundingBoxNode>(shapes, start, mid);
        m_right = std::make_shared<BoundingBoxNode>(shapes, mid, end);
    }

    m_box = BoundingBox::combine(m_left->box(), m_right->box());
}

std::ostream& operator<<(std::ostream& os, const BoundingBoxNode& b) {
    os << b.str();

    return os;
}

std::string BoundingBoxNode::str(int depth) const {
    std::ostringstream os;

    os << calc_spaces(depth) << "Node: " << box() << '\n';
    if (m_left) {
        if (auto left = dynamic_cast<BoundingBoxNode*>(m_left.get())) {
            os << left->str(depth + 1);
        } else {
            os << str_leaf(depth + 1, m_left->box());
        }
    }
    if (m_right) {
        if (auto right = dynamic_cast<BoundingBoxNode*>(m_right.get())) {
            os << right->str(depth + 1);
        } else {
            os << str_leaf(depth + 1, m_right->box());
        }
    }

    return os.str();
}

std::string BoundingBoxNode::str_leaf(int depth, const BoundingBox& b) const {
    std::ostringstream os;
    os << calc_spaces(depth) << "Leaf: " << b << '\n';
    return os.str();
}

std::string BoundingBoxNode::calc_spaces(int depth) const {
    std::ostringstream os;
    if (depth > 0) {
        if (depth > 1)
            os << "|    ";
        for (int i = 0; i < depth - 2; ++i) {
            os << "     ";
        }
        os << "|--- ";
    }

    return os.str();
}
