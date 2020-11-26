//
// Created by XingfengYang on 2020/7/22.
//

#ifndef __KERNEL_LOG_H__
#define __KERNEL_LOG_H__

#include "libc/stdlib.h"

#define LOG_LEVEL_VERBOSE 1
#define LOG_LEVEL_DEBUG  2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_WARNING  4
#define LOG_LEVEL_ERROR 5
#define LOG_LEVEL_FATAL  6
#define DEFAULT_LOG_LEVEL LOG_LEVEL_VERBOSE

#ifndef LOG_LEVEL
#define LOG_LEVEL DEFAULT_LOG_LEVEL
#endif

#ifndef LOG_OUTPUT_COLORFUL
#define LOG_OUTPUT_COLORFUL 1
#endif

/// log filename, line number, function name or not
/// enable log format like [DEBUG finename.c:25(function_name)] or not
#ifndef LOG_OUTPUT_LABEL
#define LOG_OUTPUT_LABEL 1
/// enable log format like [DEBUG finename.c:25] or not
#ifndef LOG_OUTPUT_FUNCTION_NAME
#define LOG_OUTPUT_FUNCTION_NAME 1
#define LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER "(%s)"
#define LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE __func__
#endif
#endif

#if LOG_OUTPUT_LABEL
#ifndef LOG_OUTPUT_LABEL_VALUE
#if LOG_OUTPUT_FUNCTION_NAME
#define LOG_OUTPUT_LABEL_VALUE(value) \
    "[" #value " " __CURRENT_FILE_NAME__ ":" __STRINGIFY__(__LINE__) LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER "] "
#else
#define LOG_OUTPUT_LABEL_VALUE(value) "[" #value " " __CURRENT_FILE_NAME__ ":" __STRINGIFY__(__LINE__) "] "
#endif
#endif
#else
#define LOG_OUTPUT_LABEL_VALUE(value)
#endif

#if LOG_OUTPUT_COLORFUL
#define LOG_OUTPUT_COLOR_BLACK "\033[30m"
#define LOG_OUTPUT_COLOR_RED "\033[31m"
#define LOG_OUTPUT_COLOR_GREEN "\033[32m"
#define LOG_OUTPUT_COLOR_YELLOW "\033[33m"
#define LOG_OUTPUT_COLOR_BLUE "\033[34m"
#define LOG_OUTPUT_COLOR_MAGENTA "\033[35m"
#define LOG_OUTPUT_COLOR_CYAN "\033[36m"
#define LOG_OUTPUT_COLOR_WHITE "\033[37m"

#define LOG_OUTPUT_COLOR_BACKGROUND_BLACK "\033[40m"
#define LOG_OUTPUT_COLOR_BACKGROUND_RED "\033[41m"
#define LOG_OUTPUT_COLOR_BACKGROUND_GREEN "\033[42m"
#define LOG_OUTPUT_COLOR_BACKGROUND_YELLOW "\033[43m"
#define LOG_OUTPUT_COLOR_BACKGROUND_BLUE "\033[44m"
#define LOG_OUTPUT_COLOR_BACKGROUND_MAGENTA "\033[45m"
#define LOG_OUTPUT_COLOR_BACKGROUND_CYAN "\033[46m"
#define LOG_OUTPUT_COLOR_BACKGROUND_WHITE "\033[47m"

#define LOG_OUTPUT_COLOR_RESET "\033[0m"
#else
#define LOG_OUTPUT_COLOR_BLACK
#define LOG_OUTPUT_COLOR_RED
#define LOG_OUTPUT_COLOR_GREEN
#define LOG_OUTPUT_COLOR_YELLOW
#define LOG_OUTPUT_COLOR_BLUE
#define LOG_OUTPUT_COLOR_MAGENTA
#define LOG_OUTPUT_COLOR_CYAN
#define LOG_OUTPUT_COLOR_WHITE

#define LOG_OUTPUT_COLOR_BACKGROUND_BLACK
#define LOG_OUTPUT_COLOR_BACKGROUND_RED
#define LOG_OUTPUT_COLOR_BACKGROUND_GREEN
#define LOG_OUTPUT_COLOR_BACKGROUND_YELLOW
#define LOG_OUTPUT_COLOR_BACKGROUND_BLUE
#define LOG_OUTPUT_COLOR_BACKGROUND_MAGENTA
#define LOG_OUTPUT_COLOR_BACKGROUND_CYAN
#define LOG_OUTPUT_COLOR_BACKGROUND_WHITE

#define LOG_OUTPUT_COLOR_RESET
#endif

#ifndef __CURRENT_FILE_NAME__
#define __CURRENT_FILE_NAME__ __FILE__
#endif

#ifndef _log_function
#define _log_function(format, ...) printf(format, ##__VA_ARGS__)
#endif

/// log verbose
#if LOG_LEVEL <= LOG_LEVEL_VERBOSE
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogVerbose(format, ...)                                                                             \
    _log_function(LOG_OUTPUT_COLOR_BLUE LOG_OUTPUT_LABEL_VALUE(VERBOSE) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogVerbose(format, ...) \
    _log_function(LOG_OUTPUT_COLOR_BLUE LOG_OUTPUT_LABEL_VALUE(VERBOSE) format LOG_OUTPUT_COLOR_RESET "\n", ##__VA_ARGS__)
#endif
#else
#define LogVerbose(format, ...)
#endif

/// log debug
#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogDebug(format, ...)                                                                             \
    _log_function(LOG_OUTPUT_COLOR_CYAN LOG_OUTPUT_LABEL_VALUE(DEBUG) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogDebug(format, ...) \
    _log_function(LOG_OUTPUT_COLOR_CYAN LOG_OUTPUT_LABEL_VALUE(DEBUG) format LOG_OUTPUT_COLOR_RESET "\n", ##__VA_ARGS__)
#endif
/// log trace
#define LogTrace LogDebug("---TRACING LOG---")
#else
#define LogDebug(format, ...)
#define LogTrace()
#endif

/// log info
#if LOG_LEVEL <= LOG_LEVEL_INFO
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogInfo(format, ...)                                                                              \
    _log_function(LOG_OUTPUT_COLOR_WHITE LOG_OUTPUT_LABEL_VALUE(INFO) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogInfo(format, ...) \
    _log_function(LOG_OUTPUT_COLOR_WHITE LOG_OUTPUT_LABEL_VALUE(INFO) format LOG_OUTPUT_COLOR_RESET "\n", ##__VA_ARGS__)
#endif
#else
#define LogInfo(format, ...)
#endif

/// log warning
#if LOG_LEVEL <= LOG_LEVEL_WARNING
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogWarn(format, ...)                                                                               \
    _log_function(LOG_OUTPUT_COLOR_YELLOW LOG_OUTPUT_LABEL_VALUE(WARN) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogWarn(format, ...) \
    _log_function(LOG_OUTPUT_COLOR_YELLOW LOG_OUTPUT_LABEL_VALUE(WARN) format LOG_OUTPUT_COLOR_RESET "\n", ##__VA_ARGS__)
#endif
#else
#define LogWarn(format, ...)
#endif

/// log error
#if LOG_LEVEL <= LOG_LEVEL_ERROR
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogError(format, ...)                                                                            \
    _log_function(LOG_OUTPUT_COLOR_RED LOG_OUTPUT_LABEL_VALUE(ERROR) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogError(format, ...) \
    _log_function(LOG_OUTPUT_COLOR_RED LOG_OUTPUT_LABEL_VALUE(ERROR) format LOG_OUTPUT_COLOR_RESET "\n", ##__VA_ARGS__)
#endif
#else
#define LogError(format, ...)
#endif

/// log fatal
#if LOG_LEVEL <= LOG_LEVEL_FATAL
#if LOG_OUTPUT_LABEL && LOG_OUTPUT_FUNCTION_NAME
#define LogFatal(format, ...)                                                                                \
    _log_function(LOG_OUTPUT_COLOR_MAGENTA LOG_OUTPUT_LABEL_VALUE(FATAL) format LOG_OUTPUT_COLOR_RESET "\n", \
                  LOG_OUTPUT_FUNCTION_NAME_PLACE_HOLDER_VALUE, ##__VA_ARGS__)
#else
#define LogFatal(format, ...)                                                                                \
    _log_function(LOG_OUTPUT_COLOR_MAGENTA LOG_OUTPUT_LABEL_VALUE(FATAL) format LOG_OUTPUT_COLOR_RESET "\n", \
                  ##__VA_ARGS__)
#endif
#else
#define LogFatal(format, ...)
#endif

#endif// __KERNEL_LOG_H__
