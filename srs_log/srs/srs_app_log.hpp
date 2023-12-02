#ifndef SRS_APP_LOG_HPP
#define SRS_APP_LOG_HPP

#include <string.h>
#include <string>
#include "chw_adapt.h"
#include "srs_kernel_log.hpp"

class SrsFileLog : public ISrsLog/*, public ISrsReloadHandler*/
{
private:
    // Defined in SrsLogLevel.
    SrsLogLevel level_;
private:
    char* log_data;
    // Log to file if specified srs_log_file
    int fd;
    // Whether log to file tank
    bool log_to_file_tank;//false输出到控制台，true输出到文件
    // Whether use utc time.
    bool utc;
    // TODO: FIXME: use macro define like SRS_MULTI_THREAD_LOG to switch enable log mutex or not.
    // Mutex for multithread log.多线程日志的互斥锁。
    SrsThreadMutex* mutex_;

    std::string filename_;
public:
    SrsFileLog();
    virtual ~SrsFileLog();
// Interface ISrsLog
public:
    virtual /*srs_error_t*/int initialize();
    virtual void reopen();
    //chw,日志记录包含上下文ID，更容易定位问题，这里SrsContextId使用std::string代替,减少依赖
    virtual void log(SrsLogLevel level, const char* tag, std::string context_id, const char* fmt, va_list args);
private:
    virtual void write_log(int& fd, char* str_log, int size, int level);
    virtual void open_log_file();
};

#endif
