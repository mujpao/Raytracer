#include "progressindicator.h"

#include "utils.h"

#include <cmath>
#include <iostream>

ProgressIndicator::ProgressIndicator(double increment_interval)
    : m_increment_interval(increment_interval) {}

void ProgressIndicator::start() const { std::cout << "[" << std::flush; }

void ProgressIndicator::increment(double percentage) {
    double pct_before = m_percent_finished;
    m_percent_finished = std::min(m_percent_finished + percentage, 1.0);
    if (std::floor(m_percent_finished / m_increment_interval)
        > std::floor(pct_before / m_increment_interval)) {
        std::cout << "=" << std::flush;
    }
    if (Utils::is_gt_equal(m_percent_finished, 1.0)) {
        finish();
    }
}

void ProgressIndicator::finish() const {
    std::cout << "] 100%" << std::endl;
    ;
}
