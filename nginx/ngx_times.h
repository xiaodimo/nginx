
#ifndef _NGX_TIMES_H_INCLUDE_
#define _NGX_TIMES_H_INCLUDE_

#include "ngx_config.h"
#include "ngx_core.h"
#include "ngx_string.h"

typedef struct
{
	//time_t sec;
	ngx_uint_t msec; 
	ngx_uint_t gmtoff;   // gmt ��������ʱ��
}ngx_time_t;

// volatile ���������Ż��������õ����ֵʱ��ÿ�ζ���С��ȥ�����ֵ��������ȥ���Ĵ����еı���
extern volatile ngx_str_t ngx_cached_err_log_time;  


#endif 