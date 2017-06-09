
#ifndef _NGX_CONFIG_FILE_H_INCLUDE_
#define _NGX_CONFIG_FILE_H_INCLUDE_ 

#include "ngx_core.h"
#include "ngx_files.h"
#include "ngx_string.h"

struct ngx_open_file_s
{
	ngx_fd_t	fd; 
	ngx_str_t	name; 

	void		(*flush)(ngx_open_file_t *file, ngx_log_t *log);
	void		*data; 
};

#endif 
