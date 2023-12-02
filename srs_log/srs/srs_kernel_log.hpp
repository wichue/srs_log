#ifndef SRS_KERNEL_LOG_HPP
#define SRS_KERNEL_LOG_HPP

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <stdarg.h>
#include "chw_adapt.h"

// Please note that the enum name might not be the string, to keep compatible with previous definition.
//日志级别
enum SrsLogLevel
{
    SrsLogLevelForbidden = 0x00,

    // Only used for very verbose debug, generally,
    // we compile without this level for high performance.
    SrsLogLevelVerbose = 0x01,
    SrsLogLevelInfo = 0x02,
    SrsLogLevelTrace = 0x04,
    SrsLogLevelWarn = 0x08,
    SrsLogLevelError = 0x10,

    SrsLogLevelDisabled = 0x20,
};

// Get the level in string.
extern const char* srs_log_level_strings[];

// The log interface provides method to write log.  日志接口提供了写入日志的方法。
// but we provides some macro, which enable us to disable the log when compile.但是我们提供了一些宏，它使我们能够在编译时禁用日志。
class ISrsLog
{
public:
    ISrsLog();
    virtual ~ISrsLog();
public:
    // Initialize log utilities.初始化日志实用程序。
    virtual /*srs_error_t*/int initialize() = 0;
    // Reopen the log file for log rotate.重新打开日志文件以进行日志轮替。
    virtual void reopen() = 0;
public:
    // Write a application level log. All parameters are required except the tag.写应用程序级别日志
    virtual void log(SrsLogLevel level, const char* tag, std::string context_id, const char* fmt, va_list args) = 0;
};

// The logic context, for example, a RTMP connection, or RTC Session, etc.逻辑上下文，例如，一个RTMP连接，或RTC会话等。
// We can grep the context id to identify the logic unit, for debugging.我们可以通过上下文id来标识逻辑单元，用于调试。
class ISrsContext
{
public:
    ISrsContext();
    virtual ~ISrsContext();
public:
    // Get the context id of current thread.获取当前线程的上下文id。
    virtual std::string get_id()
    {
        return "ID9527";
    }
};

// @global User must implements the LogContext and define a global instance.用户必须实现日志上下文并定义一个全局实例。
extern ISrsContext* _srs_context;

// @global User must provides a log object  用户必须提供一个日志对象
extern ISrsLog* _srs_log;

// Global log function implementation. Please use helper macros, for example, srs_trace or srs_error.
//全局日志函数的实现。请使用助手宏，例如，srs_trace或srs_error。
extern void srs_logger_impl(SrsLogLevel level, const char* tag, std::string context_id, const char* fmt, ...);

// Log style.
// Use __FUNCTION__ to print c method
// Use __PRETTY_FUNCTION__ to print c++ class:method
#define srs_verbose(msg, ...) srs_logger_impl(SrsLogLevelVerbose, NULL, _srs_context->get_id(), msg, ##__VA_ARGS__)
#define srs_info(msg, ...) srs_logger_impl(SrsLogLevelInfo, NULL, _srs_context->get_id(), msg, ##__VA_ARGS__)
#define srs_trace(msg, ...) srs_logger_impl(SrsLogLevelTrace, NULL, _srs_context->get_id(), msg, ##__VA_ARGS__)
#define srs_warn(msg, ...) srs_logger_impl(SrsLogLevelWarn, NULL, _srs_context->get_id(), msg, ##__VA_ARGS__)
#define srs_error(msg, ...) srs_logger_impl(SrsLogLevelError, NULL, _srs_context->get_id(), msg, ##__VA_ARGS__)

#endif
