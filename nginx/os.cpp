
#define DLL_IMPLEMENTATION 

#include "os.h"
#include "ngx_win32_config.h"
#include "ngx_alloc.h"
#include "ngx_string.h"
#include <stdlib.h>

DLL_API int  add(int x, int y)
{



	u_char *p = (u_char *)ngx_calloc(10, 0); 
	
	u_char szMsg[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 

	u_char *dp = ngx_cpymem(p, szMsg, 5); 

	return x + y;
	
}

