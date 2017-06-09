
#ifndef _NGX_ATOMIC_H_INCLUDE_ 
#define _NGX_ATOMIC_H_INCLUDE_ 

#include "ngx_config.h"

#define NGX_HAVE_ATOMIC_OPS		1

typedef int32_t					ngx_atomic_int_t; 
typedef uint32_t				ngx_atomic_uint_t; 

#if (NGX_PTR_SIZE == 8)
#define NGX_ATOMIC_T_LEN		(sizeof("-9223372036854775808") - 1)
#else 
#define NGX_ATOMIC_T_LEN		(sizeof("-2147483648") - 1)
#endif 

#endif