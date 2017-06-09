
#ifndef _NGX_LOG_H_INCLUDE_
#define _NGX_LOG_H_INCLUDE_

#include "ngx_config.h"
#include "ngx_core.h"
#include "ngx_errno.h"

#include <stdarg.h>

#define NGX_LOG_STDERR				0
#define NGX_LOG_EMERG				1
#define NGX_LOG_ALERT				2


#define NGX_HAVE_VARIADIC_MACROS	0

#define NGX_MAX_ERROR_STR			2048


struct ngx_log_s
{
	ngx_uint_t			level;   
	ngx_open_file_t		*file; 

	char				*action; 

	ngx_log_t			*next; 
};


#define ngx_string(str)			{sizeof(str) - 1, (u_char *)str}
#define ngx_null_string			{0, NULL}


void ngx_cdecl ngx_log_error(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...); 

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, va_list args); 

void ngx_cdecl ngx_log_debug_core(ngx_log_t *log, ngx_err_t *err, const char *fmt, ...); 



#endif 