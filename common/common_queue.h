#ifndef COMMON_QUEUE_H_
#define COMMON_QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <utility>
#include <iostream>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC)
 *
 * Queue is a generic MPMC queue with blocking operations
 * push() and pop().
 *
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 * On a closed queue, any method will raise ClosedQueue.
 *
 * */
template <typename T, class C = std::deque<T> >
class Queue {
private:
    std::queue<T, C> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    Queue(): max_size(UINT_MAX - 1), closed(false) {}
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}


bool try_push(T&& val) {
    std::unique_lock<std::mutex> lck(mtx);

    if (closed) {
        throw ClosedQueue();
    }

    if (q.size() == this->max_size) {
        return false;
    }

    if (q.empty()) {
        is_not_empty.notify_all();
    }

    q.push(std::move(val));
    return true;
}


bool try_pop(T& val) {
    std::unique_lock<std::mutex> lck(mtx);

    if (q.empty()) {
        if (closed) {
            throw ClosedQueue();
        }
        return false;
    }

    if (q.size() == this->max_size) {
        is_not_full.notify_all();
    }

    val = std::move(q.front());
    q.pop();
    return true;
}


 void push(T&& value) {
    std::unique_lock<std::mutex> lck(mtx);
    
    //std::cout << "veo si puedo pushear\n";
    
    if (closed) {
        //std::cout << "cola cerrada\n";
        throw ClosedQueue();
    }
    while (q.size() == this->max_size) {
        //std::cout << "cola llena\n";
        is_not_full.wait(lck);
    }
    if (q.empty()) {
        is_not_empty.notify_all();
    }

    //std::cout << "voy a pushear algo\n";
    q.push(std::move(value));
    //std::cout << "algo pusheado\n";
}


T pop() {
    std::unique_lock<std::mutex> lck(mtx);
    //std::cout << "veo si puedo popear\n";
    while (q.empty()) {
        if (closed) {
            //std::cout << "cola cerrada\n";
            throw ClosedQueue();
        }

        is_not_empty.wait(lck);
    }

    if (q.size() == this->max_size) {
        //std::cout << "tamanio maximo\n";
        is_not_full.notify_all();
    }

    T val = std::move(q.front());
    //std::cout << "voy a popear\n";
    q.pop();
    //std::cout << "algo popeado\n";

    return val;
}


    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

template <>
class Queue<void*> {
private:
    std::queue<void*> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    explicit Queue(const unsigned int max_size): max_size(max_size), closed(false) {}


    bool try_push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw ClosedQueue();
        }

        if (q.size() == this->max_size) {
            return false;
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        return true;
    }

    bool try_pop(void*& val) {
        std::unique_lock<std::mutex> lck(mtx);

        if (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            return false;
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        val = q.front();
        q.pop();
        return true;
    }

    void push(void* const& val) {
        std::unique_lock<std::mutex> lck(mtx);

        //std::cout << "voy a pushear el evento\n";

        if (closed) {
            //std::cout << "cola cerrada\n";
            throw ClosedQueue();
        }

        while (q.size() == this->max_size) {
            is_not_full.wait(lck);
        }

        if (q.empty()) {
            is_not_empty.notify_all();
        }

        q.push(val);
        //std::cout << "evento pusheado\n";
    }


    void* pop() {
        std::unique_lock<std::mutex> lck(mtx);

        while (q.empty()) {
            if (closed) {
                throw ClosedQueue();
            }
            is_not_empty.wait(lck);
        }

        if (q.size() == this->max_size) {
            is_not_full.notify_all();
        }

        void* const val = q.front();
        q.pop();

        return val;
    }

    void close() {
        std::unique_lock<std::mutex> lck(mtx);

        if (closed) {
            throw std::runtime_error("The queue is already closed.");
        }

        closed = true;
        is_not_empty.notify_all();
    }
    // Move constructor
    Queue(Queue&& other) noexcept:
            q(std::move(other.q)), max_size(other.max_size), closed(other.closed) {}

    // Move assignment operator
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            std::lock_guard<std::mutex> lck(mtx);
            q = std::move(other.q);
            closed = other.closed;
            // No need to copy mutex or condition variables
        }
        return *this;
    }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};


template <typename T>
class Queue<T*>: private Queue<void*> {
public:
    explicit Queue(const unsigned int max_size): Queue<void*>(max_size) {}


    bool try_push(T* const& val) { return Queue<void*>::try_push(val); }

    bool try_pop(T*& val) { return Queue<void*>::try_pop((void*&)val); }

    void push(T* const& val) { return Queue<void*>::push(val); }


    T* pop() { return (T*)Queue<void*>::pop(); }

    void close() { return Queue<void*>::close(); }

private:
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

#endif
