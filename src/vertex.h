#ifndef VERTEX_H
#define VERTEX_H

#include "math/vec.h"

#include <utility>

class Vertex {
public:
    Vertex(const Vec& position, std::pair<double, double> uv = { 0.0, 0.0 });

    void set_position(const Vec& position) { m_position = position; }

    Vec position() const { return m_position; }

    double u() const { return m_u; }
    double v() const { return m_v; }

private:
    Vec m_position;

    double m_u, m_v;
};

#endif
