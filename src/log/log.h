#ifndef LOG_H
#define LOG_H

#include "colors.h"
#include <stdio.h>
#include <syslog.h>

enum l_log_type {
  Emergency = 0,     // system is unusable
  Alert = 1,         // action must be taken immediately
  Critical = 2,      // critical conditions
  Error = 3,         // error conditions
  Warning = 4,       // warning conditions
  Notice = 5,        // normal but significant condition
  Informational = 6, // informational messages
  Debug = 7          // debug-level messages
};

static const char *l_log_type_name[] = {"Emergency",     "Alert",   "Critical",
                                        "Error",         "Warning", "Notice",
                                        "Informational", "Debug"};

static const char *l_log_type_color[] = {WHTHB HRED, REDHB WHT, REDB BLK, RED,
                                         YEL,        MAG,       CYN,      GRN};
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

#endif /* L_SYSLOG */

#endif /* LOG_H */
