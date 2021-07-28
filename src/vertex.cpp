#include "vertex.h"

Vertex::Vertex(const Vec& position, std::pair<double, double> uv)
    : m_position(Vec::to_point(position)), m_u(uv.first), m_v(uv.second) {}
