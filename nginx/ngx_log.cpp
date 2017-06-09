
#include "ngx_log.h"
#include "ngx_string.h"
#include "ngx_times.h"

static ngx_str_t err_levels[] =
{
	ngx_null_string,
	ngx_string("emerg"),
	ngx_string("alert"),
	ngx_string("crit"),
	ngx_string("error"),
	ngx_string("warn"),
	ngx_string("notice"),
	ngx_string("info"),
	ngx_string("debug"),
}

void ngx_cdecl ngx_log_error(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
	va_list args;

	if (log->level >= level)
	{
		va_start(args, fmt);
		ngx_log_error_core(level, log, err, fmt, args);
		va_end(args);
	}
}

void ngx_cdecl ngx_log_debug_core(ngx_log_t *log, ngx_err_t *err, const char *fmt, ...)
{

}

#if (NGX_HAVE_VARIADIC_MACROS)
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
#else
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err, const char *fmt, va_list args)
#endif
{
#if (NGX_HAVE_VARIADIC_MACROS)
	va_list			args;
#endif
	u_char			*p, *last, *msg;
	//ssize_t		n;
	ngx_uint_t		wrote_stderr, debug_connection;
	u_char			errstr[NGX_MAX_ERROR_STR];

	last = errstr + NGX_MAX_ERROR_STR;

	p = ngx_cpymem(errstr, ngx_cached_err_log_time.data, ngx_cached_err_log_time.len);

	p = ngx_slprintf(p, last, " [%V]", &err_levels[level]);









}

