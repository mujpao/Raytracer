#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

class ProgressIndicator {
public:
    ProgressIndicator(double increment_interval = 0.01);

    void start() const;
    void increment(double percentage);

private:
    void finish() const;

    double m_percent_finished = 0.0;
    double m_increment_interval;
};

#endif
