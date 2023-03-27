# C-Utils

List of C-utils used in my C project in Epita

## Requirements
- Pyhton3
- Compiledb

## Log

Colored log utils, every log are writted in stderr. It can also use syslog:

### Macro prototype:
```c
LOG(lvl, ...)
```

### Example:
```c
  LOG(L_EMERGENCY, "Syslog gravity level: %d", L_EMERGENCY);
  LOG(L_ALERT, "Syslog gravity level: %d", L_ALERT);
  LOG(L_CRITICAL, "Syslog gravity level: %d", L_CRITICAL);
  LOG(L_ERROR, "Syslog gravity level: %d", L_ERROR);
  LOG(L_WARNING, "Syslog gravity level: %d", L_WARNING);
  LOG(L_NOTICE, "Syslog gravity level: %d", L_NOTICE);
  LOG(L_INFORMATIONAL, "Syslog gravity level: %d", L_INFORMATIONAL);
  LOG(L_DEBUG, "Syslog gravity level: %d", L_DEBUG);
```

### Output:
![Log Output](Pictures/log_output.png)

### Syslog
You can make log also writted in syslog by defining **L_SYSLOG**. Don't forget to use openlog function before.
