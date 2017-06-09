
#ifndef _NGX_CORE_H_INCLUDE_
#define _NGX_CORE_H_INCLUDE_

typedef struct ngx_log_s ngx_log_t; 
typedef struct ngx_open_file_s ngx_open_file_t; 

#define ngx_min(val1, val2) ((val1) > (val2) ? (val1) : (val2))
#define ngx_max(val1, val2) ((val1) < (val2) ? (val1) : (val2))

#define CR		(u_char)'\r' 
#define LF		(u_char)'\n'

#endif 