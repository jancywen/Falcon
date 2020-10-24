#ifndef _SPIN_LOCK_HPP
#define _SPIN_LOCK_HPP

#include "cpplang.hpp"

BEGIN_NAMESPACE(cpp_study)

class SpinLock final                                // 自旋锁类 禁止继承
{
public:
    using this_type = SpinLock;                     // 类型别名
    using atomic_type = std::atomic_flag;

public:
    SpinLock() = default;                           // 默认构造函数
    ~SpinLock() = default;

    SpinLock(const this_type&) = delete;            // 禁止拷贝
    SpinLock& operator=(const this_type&) = delete;

public:
    void lock() noexcept
    {
        for(;;) {
            if (!m_lock.test_and_set()) {
                return;
            }
            std::this_thread::yield();
        }
    }

    bool try_lock() noexcept
    {
        return !m_lock.test_and_set();
    }

    void unlock() noexcept
    {
        m_lock.clear();
    }

private:
    atomic_type m_lock {false};                     // 成员变量初始化
};


class SpinLockGuard final
{
public:
    using this_type         = SpinLockGuard;
    using spin_lock_type    = SpinLock;
public:
    SpinLockGuard(spin_lock_type& lock) noexcept 
        : m_lock(lock)
    {
        m_lock.lock();
    }

    ~SpinLockGuard() noexcept
    {
        m_lock.unlock();
    }

public:
    SpinLockGuard(const this_type&) = delete;
    SpinLockGuard& operator=(const this_type&) = delete;

private:
    spin_lock_type& m_lock;

};



END_NAMESPACE(cpp_study)

#endif  //_SPIN_LOCK_HPP