/*
 * @Author: LeiJiulong
 * @Date: 2024-12-21 14:03:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-22 17:32:47
 * @Description:
 */
#pragma once
#include <thread>
#include <functional>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>



class NonCopyAble
{
public:
    NonCopyAble(const NonCopyAble &) = delete;
    NonCopyAble &operator=(const NonCopyAble &) = delete;

protected:
    NonCopyAble() = default;
    ~NonCopyAble() = default;
};

struct FutureData
{
    int64_t time_stamp;
    char future_name[128];
};

template <typename T, size_t size = 128>
class DataRing : public NonCopyAble
{
public:
    explicit DataRing()
    {
    }

    ~DataRing() = default;

    bool push(const T &ele)
    {
        if (!is_full())
        {
            memcpy(&data_array_[tail_], &ele, sizeof(T));
            tail_ = (tail_ + 1) % size;
            return true;
        }
        return false;
    }

    T get()
    {
        if (!is_empty())
        {
            size_t t = header_;
            header_ = (header_ + 1) % size;
            return data_array_[t];
        }
        return T{};
    }

    bool is_full()
    {
        if ((tail_ + 1) % size == header_)
            return true;
        return false;
    }

    bool is_empty()
    {
        if (header_ == tail_)
            return true;
        return false;
    }

private:
    T data_array_[size + 1];
    size_t header_{};
    size_t tail_{};
    size_t size_;
};

template <typename T,
          typename CallObj=std::function<void(void)>(),
          size_t size = 128,
          template <class> class Container = DataRing>
class WritePool : public NonCopyAble
{
    using DataRingBuff = DataRing<T, size>;

public:
    static WritePool *GetInstance()
    {
        std::call_once(cflag_, Construct);
        return cptr_self_;
    }

    static void DeleInstance()
    {
        delete cptr_self_;
        cptr_self_ = nullptr;
    }

    void push(const T &ele);
    

private:
    WritePool() : ccurrent_push_buff_(new DataRingBuff()), ccurrent_write_buff_(new DataRingBuff()),cstop_(false),ccallFunc_()
    {
        cthreads_.emplace_back([this]{
            while (true)
            {
                std::unique_lock<std::mutex> lock(cmutex_);
                ccv_.wait(lock,[this]{
                    return !ccurrent_write_buff_->is_empty() || !cwrite_buf_queue_.empty();
                });
                if(!ccurrent_write_buff_->is_empty())
                {
                    auto c = ccurrent_write_buff_->get();
                    ccallFunc_(c);
                    
                }
                else if (!cwrite_buf_queue_.empty())
                {
                    ccurrent_write_buff_ = cwrite_buf_queue_.front();
                    cwrite_buf_queue_.pop();
                    auto c = ccurrent_write_buff_->get();
                    ccallFunc_(c);
                    
                }
                if(cstop_ && ccurrent_write_buff_->is_empty() && cwrite_buf_queue_.empty() && ccurrent_push_buff_->is_empty())
                {
                    std::cout << "write thread stop " << std::endl;
                    return;
                }
            }
            
        });

        cthreads_.emplace_back([this]{
            while(true)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                {
                    std::unique_lock<std::mutex>lock(cmutex_);
                    cwrite_buf_queue_.emplace(ccurrent_push_buff_);
                    ccurrent_push_buff_.reset(new DataRingBuff());
                    ccv_.notify_one();
                }
                if(cstop_ && ccurrent_push_buff_->is_empty())
                {
                    std::cout << "move data thread stop" << std::endl;
                    return;
                }
            }
        });

    }
    ~WritePool()
    {
        {
            std::unique_lock<std::mutex> lock(cmutex_);
            cstop_ = true;
            ccv_.notify_all();
        }
        for(auto& t: cthreads_)
            t.join();
    }

    static void Construct()
    {
        cptr_self_ = new WritePool();
    }

private:
    static std::once_flag cflag_;
    CallObj ccallFunc_;
    std::mutex cmutex_;
    std::condition_variable ccv_;
    bool cstop_;
    static WritePool *cptr_self_;
    std::vector<std::thread> cthreads_;
    std::queue<std::shared_ptr<DataRingBuff>> cwrite_buf_queue_;
    std::shared_ptr<DataRingBuff> ccurrent_push_buff_;
    std::shared_ptr<DataRingBuff> ccurrent_write_buff_;
};

template <typename T,
           typename CallObj,
          size_t size,
          template <class> class Container>
std::once_flag WritePool<T, CallObj, size, Container>::cflag_;

template <typename T,
           typename CallObj,
          size_t size,
          template <class> class Container>
WritePool<T, CallObj, size, Container> *WritePool<T, CallObj, size, Container>::cptr_self_ = nullptr;

template<typename T, typename CallObj, size_t size, template <class> class Container>
void WritePool<T, CallObj, size, Container>::push(const T & ele)
{
    std::lock_guard<std::mutex> lock(cmutex_);
    if(ccurrent_push_buff_->is_full())
    {
        cwrite_buf_queue_.emplace(ccurrent_push_buff_);
        ccurrent_push_buff_.reset(new DataRingBuff());
        ccurrent_push_buff_->push(ele);
        ccv_.notify_one();
        return;
    }
    ccurrent_push_buff_ ->push(ele);
    return;
}
