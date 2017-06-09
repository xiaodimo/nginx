

#ifndef _NGX_STRING_H_INCLUD_
#define _NGX_STRING_H_INCLUD_

#include "ngx_string.h"
#include "ngx_log.h"
#include "ngx_core.h"
#include "ngx_win32_config.h"
#include "ngx_process.h"
#include "ngx_time.h"
#include "ngx_config.h"
#include "ngx_atomic.h"
#include <stdlib.h> 

static u_char * ngx_sprintf_num(u_char *buf, u_char *last, uint64_t ui64, u_char zero, ngx_uint_t hexadecimal, ngx_uint_t width); 

#if (NGX_MEMCPY_LIMIT)

void *ngx_memcpy(void *dest, const void *src, size_t n)
{
	if (n > NGX_MEMCPY_LIMIT)
	{
		ngx_log_error(NGX_LOG_ALERT, NULL, 0, "memcpy %uz bytes", n); 
		abort(); 
	}

	return memcpy(dest, src, n); 
}

#endif

u_char * ngx_cdecl ngx_slprintf(u_char *buf, u_char *last, const char *fmt, ...)
{
	u_char *p; 

	va_list args; 

	va_start(args, fmt); 

	p = 0; 

	va_end(args); 


	return p; 
}

u_char * ngx_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args)
{
	u_char					*p,	zero; 
	int						d; 
	size_t					slen, len; 
	ngx_uint_t				width, sign, hex, max_width, frac_width, scale, n; 
	ngx_str_t				*v; 
	ngx_variable_value_t	*vv;
	int64_t					i64; 
	uint64_t				ui64, frac; 
	ngx_msec_t				ms; 

	double					f;

	while (*fmt && buf < last)
	{
		/*
		 * buf < last means that we could copy at least one character: 
		 * the plain character, "%%", "%c", and minus without the checking
		 */
		if (*fmt == '%')
		{

			zero = (u_char)((*++fmt == '0') ? '0' : ' ');

			width = 0;
			sign = 1;
			hex = 0;   // 0  1  2  ？？？
			max_width = 0;
			frac_width = 0;
			slen = (size_t)-1; 


			while (*fmt >= '0' && *fmt <= '9')
			{
				width = width * 10 + *fmt++ - '0';
			}

			for (;;)
			{
				switch (*fmt)
				{
				case 'u':
					sign = 0;
					fmt++;
					continue;

				case 'm':
					max_width = 1;
					fmt++;
					continue;

				case 'X':
					hex = 2;
					fmt++;
					sign = 0;
					continue;

				case 'x':
					hex = 1;
					fmt++;
					sign = 0;
					continue;

				case '.':
					fmt++;

					while (*fmt >= '0' && *fmt <= '9')
					{
						frac_width = frac_width * 10 + *fmt++ - '0';
					}

					break;

				case '*':
					slen = va_arg(args, size_t);
					fmt++;
					continue;

				default:
					break;
				}

				break;
			} // end for ;; 

			switch (*fmt)
			{
			case 'V':
				v = va_arg(args, ngx_str_t *);

				len = ngx_min((size_t)(last - buf), v->len);
				buf = ngx_cpymem(buf, v->data, len);
				fmt++;

				continue;

			case 'v':
				vv = va_arg(args, ngx_variable_value_t *);

				len = ngx_min((size_t)(last - buf), vv->len);
				buf = ngx_cpymem(buf, vv->data, len);
				fmt++;

				continue;

			case 's':
				p = va_arg(args, u_char *);

				if (slen == (size_t)-1)  // 对-1 进行强转，转换后是0xffffffff 
				{
					while (*p && buf < last)
					{
						*buf++ = *p++;
					}
				}
				else
				{
					len = ngx_min((size_t)(last - buf), slen);
					buf = ngx_cpymem(buf, p, len);
				}

				fmt++;

				continue;

			case 'O':
				i64 = (int64_t)va_arg(args, off_t);
				sign = 1;
				break;

			case 'P':
				i64 = (int64_t)va_arg(args, ngx_pid_t);
				sign = 1;
				break;

			case 'T':
				i64 = (int64_t)va_arg(args, time_t);
				sign = 1;
				break;

			case 'M':
				ms = (ngx_msec_t)va_arg(args, ngx_msec_t);
				if ((ngx_msec_int_t)ms == -1)
				{
					sign = 1;
					i64 = -1;
				}
				else
				{
					sign = 0;
					ui64 = (uint64_t)ms;
				}
				break;

			case 'z':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, ssize_t);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, size_t);
				}
				break;

			case 'i':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, ngx_int_t);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, ngx_uint_t);
				}

				if (max_width)
				{
					width = NGX_INT_T_LEN;
				}

				break;

			case 'd':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, int);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, u_int);
				}
				break;

			case 'l':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, long);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, u_long);
				}
				break;

			case 'D':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, int32_t);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, uint32_t);
				}
				break;

			case 'L':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, int64_t);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, uint64_t);
				}
				break;

			case 'A':
				if (sign)
				{
					i64 = (int64_t)va_arg(args, ngx_atomic_int_t);
				}
				else
				{
					ui64 = (uint64_t)va_arg(args, ngx_atomic_uint_t);
				}

				if (max_width)
				{
					max_width = NGX_ATOMIC_T_LEN;
				}

				break;

			case 'f':
				f = va_arg(args, double);

				if (f < 0)
				{
					*buf++ = '-';
					f = -f;
				}

				ui64 = (int64_t)f;
				frac = 0;

				if (frac_width)
				{
					scale = 1;
					for (n = frac_width; n; n--)
					{
						scale *= 10;
					}

					frac = (uint64_t)((f - (double)ui64) * scale + 0.5);   // +0.5 四舍五入  

					if (frac == scale)
					{
						ui64++;
						frac = 0;
					}
				}

				buf = ngx_sprintf_num(buf, last, ui64, zero, 0, width); 

				if (frac_width)
				{
					if (buf < last)
					{
						*buf++ = '.'; 
					}

					buf = ngx_sprintf_num(buf, last, frac, '0', 0, frac_width); 
				}

				fmt++; 

				continue; 

#if !(NGX_WIN32)
			case 'r': 
				i64 = (int64_t)va_arg(args, rlim_t); 
				sing = 1; 
				break; 
#endif

			case 'p':
				ui64 = (uintptr_t)va_arg(args, void *); 
				hex = 2; 
				sign = 0; 
				zero = '0'; 
				width = 2 * sizeof(void *); 
				break; 

			case 'c':
				d = va_arg(args, int); 
				*buf++ = (u_char)(d & 0xff); 
				fmt++; 
				continue; 

			case 'Z': 
				*buf++ = '\0'; 
				fmt++; 
				continue; 

			case 'N': 
#if (NGX_WIN32)
				*buf++ = CR; 
				if (buf < last)
				{
					*buf++ = LF; 
				}
#else
				*buf++ = LF; 
#endif
				fmt++; 

				continue; 

			case '%':
				*buf++ = '%'; 
				fmt++; 

				continue; 

			default: 
				*buf++ = *fmt++; 

				continue; 
			}

			if (sign)
			{
				if (i64 < 0)
				{
					*buf++ = '-'; 
					ui64 = (uint64_t)-i64; 
				}
				else
				{
					ui64 = (uint64_t)i64; 
				}
			}

			buf = ngx_sprintf_num(buf, last, ui64, zero, hex, width); 

			fmt++; 
		}
		else
		{
			*buf++ = *fmt++; 
		}
	}

	return buf; 
}

static u_char * ngx_sprintf_num(u_char *buf, u_char *last, uint64_t ui64, u_char zero, ngx_uint_t hexadecimal, ngx_uint_t width)
{
	u_char		*p, temp[NGX_INT64_LEN + 1]; 
	size_t		len;
	uint32_t	ui32;
	static u_char hex[] = "123456789abcdef"; 
	static u_char HEX[] = "123456789ABCDEF"; 

	p = temp + NGX_INT64_LEN; 

	if (hexadecimal == 0)
	{
		if (ui64 <= (uint64_t)NGX_MAX_UINT32_VALUE)
		{
			ui32 = (uint32_t)ui64; 

			do
			{
				*--p = (u_char)(ui32 % 10 + '0'); 
			} while (ui32 / 10); 
		}
		else
		{
			do
			{
				*--p = (u_char)(ui64 % 10 + '0'); 
			} while (ui64 % 10); 
		}
	}
	else if (hexadecimal == 1)
	{
		do
		{
			*--p = hex[(uint32_t)(ui64 & 0xf)]; 
		} while (ui64 >>= 4); 
	}
	else /*hexadecemal == 2*/
	{
		do
		{
			*--p = HEX[(uint32_t)(ui64 & 0xf)]; 
		} while (ui64 >>= 4); 
	}

	/* zero or space padding */
	len = (temp + NGX_INT64_LEN) - p; 

	while (len++ < width && buf < last)
	{
		*buf++ = zero; 
	}

	/* number safe copy */
	len = (temp + NGX_INT64_LEN) - p;
	if (buf + len > last)
	{
		len = last - buf; 
	}

	ngx_cpymem(buf, p, len); 
}


#endif 