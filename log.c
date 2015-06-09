
#include <syslog.h> 
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <log.h>
#include <dlog.h>
#include <stdarg.h>

#ifndef EXTAPI
#define EXTAPI __attribute__((visibility("default")))
#endif

#define RKF_SERVER_MSG_LOG_FILE		"/var/log/app_analyzer"
#define FILE_LENGTH 255

static int debug_file_fd;
static char debug_file_buf[FILE_LENGTH];

EXTAPI void msg_file_log(const char *tag, const char *fmt, ...)
{
	va_list ap;
        va_start(ap, fmt);

	debug_file_fd = open(RKF_SERVER_MSG_LOG_FILE, O_WRONLY|O_CREAT|O_APPEND, 0644);
        if (debug_file_fd != -1) 
	{
        	vsnprintf(debug_file_buf,255, fmt , ap );
                write(debug_file_fd, debug_file_buf, strlen(debug_file_buf));
                close(debug_file_fd);
        }

	va_end(ap);
} 


