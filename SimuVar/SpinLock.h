/**
    File    : SpinLock.h
    Author  : Menashe Rosemberg
    Created : 2018.11.28            Version: 20181128.2

    Spinlock threads

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>

struct SpinLock {
       SpinLock() = default;
      ~SpinLock() = default;

    void lock()   { while (Flag.test_and_set()); }
    void unlock() { Flag.clear(); }

    private:
        std::atomic_flag Flag = ATOMIC_FLAG_INIT;

        SpinLock(const SpinLock&) = delete;
        SpinLock& operator=(const SpinLock&) = delete;
};

#endif

