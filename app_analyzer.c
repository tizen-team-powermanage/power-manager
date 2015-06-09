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

#include <heynoti.h>
#include "cpu_analyzer.h"

static int MAX_SIZE_KILL_PS=5;

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
	int cnt =0;
	int* arr_pid;
	int i=0;
	int max = MAX_SIZE_KILL_PS;
	m_ps = get_cpu_pid(&cnt);

	arr_pid = (int*)malloc(size*sizeof(int));
	
	if(cnt < max)
		max = cnt;
	
	for(i=0; i<max; i++)
	{
		arr_pid[i] = m_ps[i]->PID;
	}

	free(m_ps);
	m_ps = 0;

	process_kill(m_ps,cnt);
}

void battinfo_caculation()
{

}

int set_battinfo_gathering()
{
	int ret=0;	

	if((noti_fd = heynoti_init()) < 0) 
	{
               ERR("heynoti init failed!");
               return -1;
        }
        
	ret = heynoti_subscribe(noti_fd, "device_charge_chgdet",
              (void *)battinfo_calculation, (void *)NULL);
        
	if(ret != 0) 
	{
                ERR("heynoti subscribe fail!");
                return -1;
        }

        ret = heynoti_attach_handler(noti_fd);
        if(ret != 0) 
	{
        	ERR("heynoti attach handler fail!");
                return -1;
        }

	return 0;
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
