#ifndef LOG_H
#define LOG_H

#include "colors.h"
#include <stdio.h>
#include <syslog.h>

enum l_log_type {
  L_EMERGENCY = 0,     // system is unusable
  L_ALERT = 1,         // action must be taken immediately
  L_CRITICAL = 2,      // critical conditions
  L_ERROR = 3,         // error conditions
  L_WARNING = 4,       // warning conditions
  L_NOTICE = 5,        // normal but significant condition
  L_INFORMATIONAL = 6, // informational messages
  L_DEBUG = 7          // debug-level messages
};

static const char *l_log_type_name[] = {"Emergency",     "Alert",   "Critical",
                                        "Error",         "Warning", "Notice",
                                        "Informational", "Debug"};

static const char *l_log_type_color[] = {WHTHB HRED, REDHB WHT, REDB BLK, RED,
                                         YEL,        MAG,       CYN,      GRN};

#ifndef L_NO_LOG
#ifndef L_NOP

#ifdef L_ONLY_SYSLOG

#define LOG(lvl, ...)                                                          \
  do {                                                                         \
    syslog(lvl, __VA_ARGS__);                                                  \
  } while (0);

#else

#ifdef L_SYSLOG

#define LOG(lvl, ...)                                                          \
  do {                                                                         \
    syslog(lvl, __VA_ARGS__);                                                  \
    fprintf(stderr, CBLD "%s%s" CRST ": ", l_log_type_color[lvl],              \
            l_log_type_name[lvl]);                                             \
    fprintf(stderr, __FILE__ ":%d ", __LINE__);                                \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  } while (0);

#else

#define LOG(lvl, ...)                                                          \
  do {                                                                         \
    fprintf(stderr, CBLD "%s%s" CRST ": ", l_log_type_color[lvl],              \
            l_log_type_name[lvl]);                                             \
    fprintf(stderr, __FILE__ ":%d ", __LINE__);                                \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  } while (0);

#endif /* L_ONLY_SYSLOG */
#endif /* L_SYSLOG */
#else
static inline void __nop(void) { return; };
#define LOG(lvl, ...) __nop();

#endif /* L_NOP*/
#endif /* L_NO_LOG */

#endif /* LOG_H */
