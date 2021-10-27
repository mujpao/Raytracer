#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
public:
    ThreadPool(unsigned int num_threads);

    void execute(std::function<void()> f);

    void join();

private:
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_terminate = false;
    std::mutex m_mtx;
    std::queue<std::function<void()>> m_tasks;
};

#endif
