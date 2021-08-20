//
// Created by System Administrator on 2021/8/20.
//

#ifndef QUEUE_RACE_SPIN_H
#define QUEUE_RACE_SPIN_H

#include <libkern/OSAtomic.h>
#include <cerrno>

typedef OSSpinLock pthread_spinlock_t;

static __inline__
int pthread_spin_init(pthread_spinlock_t *lock, int pshared) {
    __asm__ __volatile__ ("" ::: "memory"); /* this does not hurt to keep it */
    *lock = 0;
    return 0;
}

static __inline__
int pthread_spin_destroy(pthread_spinlock_t *lock) {
    return 0;            /* Nothing to do, just an int */
}

static __inline__
int pthread_spin_lock(pthread_spinlock_t *lock) {
    OSSpinLockLock(lock);
    return 0;
}

static __inline__
int pthread_spin_trylock(pthread_spinlock_t *lock) {
    if (OSSpinLockTry(lock)) return 0; /* OSSpinLockTry return true on success, and pthread_spin_trylock 0 */
    else return EBUSY;
}

static __inline__
int pthread_spin_unlock(pthread_spinlock_t *lock) {
    OSSpinLockUnlock(lock);
    return 0;
}
#endif //QUEUE_RACE_SPIN_H
