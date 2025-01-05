/*
 * @Author: LeiJiulong
 * @Date: 2025-01-05 00:07:50
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-05 00:11:39
 * @Description: 
 */



#include <atomic>
 
/**
 * c++ 自旋锁
 * 自旋锁（spinlock）是一种非阻塞同步机制，它通过原子操作来获取锁，如果锁已经被其他线程持有，
 * 则自旋等待直到锁可用。
 * 自旋锁适用于保护短暂代码块，在等待锁的时间非常短的情况下，自旋锁可以提供更好的性能。
 * 在C++中，自旋锁通常通过原子操作和CPU指令实现，如x86架构下的cmpxchg指令。
 * C++11标准中引入了<atomic>头文件，提供了原子类型和相关操作。
 * 下面是一个简单的自旋锁实现的例子：
 * 
 */
class SpinLock {
public:
    SpinLock() : locked(ATOMIC_VAR_INIT(false)) {}
 
    void lock() {
        while (locked.exchange(true, std::memory_order_acquire)) {
            // 自旋等待锁释放
        }
    }
 
    void unlock() {
        locked.store(false, std::memory_order_release);
    }
 
private:
    std::atomic_bool locked;
};
 

/**使用自旋锁的例子
 * 在这个例子中，SpinLock 类包含一个std::atomic_bool类型的成员变量locked，
 * 它初始化为false表示锁是可用的。lock() 方法在锁可用时将locked设置为true，
 * 如果锁已经被占用，则循环等待直到锁被释放。unlock() 方法则将locked设置为false，
 * 允许其他等待的线程获取锁。
 */
void useSpinLock() {
    SpinLock myLock;
 
    myLock.lock();
    // 临界区代码
    myLock.unlock();
}