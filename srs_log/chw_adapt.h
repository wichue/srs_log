#ifndef CHW_ADAPT_H
#define CHW_ADAPT_H

#include <string>

#define srs_assert(expression) SrsCplxError::srs_assert(expression)
#define srs_min(a, b) (((a) < (b))? (a) : (b))
#define srs_max(a, b) (((a) < (b))? (b) : (a))
#define srs_freep(p) \
    delete p; \
    p = NULL; \
    (void)0
// Please use the freepa(T[]) to free an array, otherwise the behavior is undefined.
#define srs_freepa(pa) \
    delete[] pa; \
    pa = NULL; \
    (void)0

// The thread mutex wrapper, without error.
class SrsThreadMutex
{
private:
    pthread_mutex_t lock_;
    pthread_mutexattr_t attr_;
public:
    SrsThreadMutex();
    virtual ~SrsThreadMutex();
public:
    void lock();
    void unlock();
};

#define SrsThreadLocker(instance) \
    impl__SrsThreadLocker _SRS_free_##instance(instance)

class impl__SrsThreadLocker
{
private:
    SrsThreadMutex* lock;
public:
    impl__SrsThreadLocker(SrsThreadMutex* l) {
        lock = l;
        lock->lock();
    }
    virtual ~impl__SrsThreadLocker() {
        lock->unlock();
    }
};
bool srs_log_header(char* buffer, int size, bool utc, bool dangerous, const char* tag, std::string cid, const char* level, int* psize);
#endif // CHW_ADAPT_H
