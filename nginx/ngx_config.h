
#ifndef _NGX_CONFIG_H_INCLUDE_
#define _NGX_CONFIG_H_INCLUDE_

#include "ngx_win32_config.h"

#define NGX_WIN32_LEN (sizeof("-2147483648" - 1))

typedef uintptr_t		ngx_uint_t; 
typedef intptr_t		ngx_int_t; 

typedef int64_t			ssize_t; 

#define NGX_INT32_LEN (sizeof("-2147483648") - 1)
#define NGX_INT64_LEN   (sizeof("-9223372036854775808") - 1)

#if (NGX_PTR_SIZE == 4)
#define NGX_INT_T_LEN NGX_INT32_LEN
#define NGX_INT_T_VALUE 2147483647
#else 
#define NGX_INT_T_LEN NGX_INT64_LEN
#define NGX_INT_T_VALUE 9223372036854775807
#endif 

#define NGX_MAX_UINT32_VALUE	(uint32_t)0xffffffff 
#define NGX_MAX_INT32_VALUE		(uint32_t)0x7fffffff


#endif              