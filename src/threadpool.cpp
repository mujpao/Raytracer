#include "threadpool.h"

ThreadPool::ThreadPool(unsigned int num_threads) {
    for (unsigned int i = 0; i < num_threads; ++i) {
        m_threads.emplace_back(std::thread([this]() {
            while (true) {
                bool has_task = false;
                std::function<void()> task;

                {
                    const std::lock_guard<std::mutex> lock(m_mtx);
                    if (m_tasks.empty() && m_terminate) {
                        return;
                    } else if (!m_tasks.empty()) {
                        task = m_tasks.front();
                        m_tasks.pop();
                        has_task = true;
                    }
                }

                if (has_task) {
                    task();
                }
            }
        }));
    }
}

void ThreadPool::execute(std::function<void()> f) {
    const std::lock_guard<std::mutex> lock(m_mtx);
    m_tasks.push(f);
}

void ThreadPool::join() {
    m_terminate = true;
    for (auto& thread : m_threads) {
        thread.join();
    }
}
