#pragma once

#include <atomic>

template <typename T>
class AtomicPingPong
{
public:
    T items[2];
    std::atomic<int> current = 0; // only least significant bit is used
    T& swap();
    const T& swap();

    T& operator()();
    const T& operator()() const;

    T& get();
    const T& get() const;

    T& other();
    const T& other() const;
};

// implementation:
template <typename T>
T& AtomicPingPong<T>::swap()
{
    // xor with 1 will toggle between 0 and 1
    return items[current.fetch_xor(1)];
}

template <typename T>
const T& AtomicPingPong<T>::swap()
{
    // xor with 1 will toggle between 0 and 1
    return items[current.fetch_xor(1)];
}

template <typename T>
T& AtomicPingPong<T>::operator()()
{
    return items[current & 1];
}

template <typename T>
const T& AtomicPingPong<T>::operator()() const
{
    return items[current & 1];
}

template <typename T>
T& AtomicPingPong<T>::get()
{
    return items[current & 1];
}

template <typename T>
const T& AtomicPingPong<T>::get() const
{
    return items[current & 1];
}

template <typename T>
T& AtomicPingPong<T>::other()
{
    return items[1-(current & 1)];
}

template <typename T>
const T& AtomicPingPong<T>::other() const
{
    return items[1-(current & 1)];
}
