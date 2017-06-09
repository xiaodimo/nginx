
#ifndef _NGX_ALLOC_H_INCLUDE_ 
#define _NGX_ALLOC_H_INCLUDE_ 

typedef void ngx_log_t; 


void *ngx_alloc(size_t size, ngx_log_t *log);
void *ngx_calloc(size_t size, ngx_log_t *log);

#define ngx_free free  
#define ngx_memalign(alignment, size, log) ngx_alloc(size, log)

#endif 