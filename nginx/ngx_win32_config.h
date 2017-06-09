
#ifndef _NGX_WIN32_CONFIG_H_INCLUDE_
#define _NGX_WIN32_CONFIG_H_INCLUDE_



#define ngx_inline			__inline 
#define ngx_cdecl			__cdecl 


#ifdef _MSC_VER

typedef unsigned __int32	uint32_t;
typedef __int32				int32_t;
typedef unsigned __int16	uint16_t; 
#define ngx_libc_cdel		__cdecl; 
typedef unsigned __int16	u_short; 
#endif

typedef unsigned int uint; 

typedef uint uintptr_t; 
typedef int intptr_t; 

typedef unsigned char u_char; 

typedef __int64             int64_t;
typedef unsigned __int64    uint64_t;
typedef __int64				off_t;

typedef __int64				pid_t; 

	#ifdef _WIN32 
	#define NGX_PTR_SIZE 4
	#else 
	#define NGX_PTR_SIZE 8
	#endif 

	#ifndef __GUNC__
	#ifdef _WIN64
	typedef __int64				ssize_t; 
	#else 
	typedef __int32				ssize_t; 
	#endif 
	#endif 

	typedef uint32_t			in_addr_t;
	typedef u_short				in_port_t; 


#define u_int					unsigned int
#define u_long					unsigned long


#endif
