
#ifndef _NGX_TIMES_H_INCLUDE_
#define _NGX_TIMES_H_INCLUDE_

#include "ngx_config.h"
#include "ngx_core.h"
#include "ngx_string.h"

typedef struct
{
	//time_t sec;
	ngx_uint_t msec; 
	ngx_uint_t gmtoff;   // gmt 格林尼治时间
}ngx_time_t;

// volatile 编译器的优化器，在用到这个值时，每次都会小心去读这个值，而不会去读寄存器中的备份
extern volatile ngx_str_t ngx_cached_err_log_time;  


#endif 