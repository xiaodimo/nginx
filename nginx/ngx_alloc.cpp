
#include "ngx_alloc.h"
#include "ngx_string.h"
#include <stdlib.h>

void *ngx_alloc(size_t size, ngx_log_t *log)
{
	void *p; 

	p = malloc(size);  
	if (p == NULL)
	{
		//ngx_log_error(); 
	}

	// ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size); 

	return p; 
}

void *ngx_calloc(size_t size, ngx_log_t *log)
{
	void *p; 

	p = ngx_alloc(size, log); 

	if (p)
	{
		ngx_memzero(p, size); 
	}

	return p; 
}