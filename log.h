#if !defined(_LOG_H_)
#define _LOG_H_


#ifdef __cplusplus
extern "C"
{
#endif


void msg_file_log(const char *tag , const char *fmt , ...);

#define MICROSECONDS(tv)        ((tv.tv_sec * 1000000ll) + tv.tv_usec)

#ifndef __MODULE__
#include <string.h>
#define __MODULE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

//for new log system - dlog
#ifdef LOG_TAG
	#undef LOG_TAG
#endif
#define LOG_TAG	"POWER_MANAGER_FW_LOG"

#define ERR(fmt, arg...)        do { msg_file_log(LOG_TAG ,"[MSG_ERR][%s:%d] "fmt"\n",__MODULE__, __LINE__, ##arg); } while(0)
#define DBG(fmt, arg...)        do { msg_file_log(LOG_TAG ,"[MSG_DBG][%s:%d] "fmt"\n",__MODULE__, __LINE__, ##arg); } while(0)
#define INFO(fmt, arg...)       do { msg_file_log(LOG_TAG ,"[MSG_INFO][%s:%d] "fmt"\n",__MODULE__, __LINE__, ##arg); } while(0)


#ifdef __cplusplus
}
#endif

//! End of a file

