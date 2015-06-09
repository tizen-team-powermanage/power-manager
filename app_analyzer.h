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

//#include <stdbool.h>
#include "cpu_analyzer.h"

PS *m_ps=NULL;
static int noti_fd = 0;

int process_kill(int *pid,int cnt)
{
	int ret = 0;
	int i=0;
	for(i=0; i<cnt; i++)
	{
		if (kill(pid, 0) == -1) 
		{
                	ERR("%d process does not exist",pid);
                        ret = -1;
                }
		
		INFO("process kill : %d",pid);
	}

	return ret;
}

void *analyzer_function(void *data)
{
	m_ps = get_cpu_pid();

	
}

void battinfo_caculation()
{

}

void set_battinfo_gathering()
{
/*
	 if((noti_fd = heynoti_init()) < 0) {
                        ERR("heynoti init failed!");
                        return -1;
                }
                ret = heynoti_subscribe(noti_fd, "device_charge_chgdet",
                                (void *)battinfo_calculation, (void *)NULL);
                if(ret != 0) {
                        LOGERR("heynoti subscribe fail!");
                        return -1;
                }

                ret = heynoti_attach_handler(noti_fd);
                if(ret != 0) {
                        LOGERR("heynoti attach handler fail!");
                        return -1;
                }
*/
	return;
}

void check_pwsaving_mode(int capacity)
{
	if(capacity <= 4000)
	{
	   set_power_saving();
	   //static value change
	}
}

void set_power_saving()
{
    pthread_t p_thread;
    int thread_id;
    int status;
    int ret=0;

    thread_id = pthread_create(&p_thread, NULL, analyzer_function, (void *)&ret);
    if (thread_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    
    pthread_detach(p_thread);
    //pause();
    return 0;	
}
