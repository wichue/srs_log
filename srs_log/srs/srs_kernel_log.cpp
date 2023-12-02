#include <srs_kernel_log.hpp>
#include <stdarg.h>

const char* srs_log_level_strings[] = {
#ifdef SRS_LOG_LEVEL_V2
        // The v2 log level specs by log4j.
        "FORB",     "TRACE",     "DEBUG",    NULL,   "INFO",    NULL, NULL, NULL,
        "WARN",     NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        "ERROR",    NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        NULL,       NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        "OFF",
#else
        // SRS 4.0 level definition, to keep compatible.
        "Forb",     "Verb",     "Debug",    NULL,   "Trace",    NULL, NULL, NULL,
        "Warn",     NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        "Error",    NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        NULL,       NULL,       NULL,       NULL,   NULL,       NULL, NULL, NULL,
        "Off",
#endif
};

ISrsLog::ISrsLog()
{
}

ISrsLog::~ISrsLog()
{
}

ISrsContext::ISrsContext()
{
}

ISrsContext::~ISrsContext()
{
}

void srs_logger_impl(SrsLogLevel level, const char* tag, std::string context_id, const char* fmt, ...)
{
    if (!_srs_log) return;

    va_list args;
    va_start(args, fmt);
    _srs_log->log(level, tag, context_id, fmt, args);
    va_end(args);
}
