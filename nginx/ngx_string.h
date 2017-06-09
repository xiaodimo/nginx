
#ifndef _NGX_STRING_H_INCLUDE_
#define _NGX_STRING_H_INCLUDE_

#include <string.h>
#include "ngx_win32_config.h"

#define ngx_memzero(buf, n) (void)memset(buf, 0, n)

typedef struct
{
	size_t	len; 
	u_char	*data; 
}ngx_str_t;

typedef struct
{
	unsigned	len : 28; 

	unsigned	valid : 1; 
	unsigned	uncachable : 1;
	unsigned	not_found : 1; 
	unsigned	escape : 1;

	u_char		*data; 
}ngx_variable_value_t;


#define NGX_MEMCPY_LIMIT 1

#if (NGX_MEMCPY_LIMIT)

void *ngx_memcpy(void *dest, const void *src, size_t n);  
#define ngx_cpymem(dest, src, n) (((u_char *) ngx_memcpy(dest, src, n)) + (n))

#else

/*
	gcc3, mscv, and icc7 complie memcpy() to the inline "rep movs"
	gcc3 compiles memcpy(d, s, 4) to the inline "mov"es 
	icc8 complies memcpy(d, s, 4) to the inline "mov"es or XMM movs
*/
#define ngx_memcpy(dest, src, n) (void) memcpy(dest, src, n)
#define ngx_cpymem(dest, src, n) (((u_char *) memcpy(dest, src, n)) + (n))

#endif 

u_char * ngx_cdecl ngx_slprintf(u_char *buf, u_char *last, const char *fmt, ...); 

#endif 