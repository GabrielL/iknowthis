#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <glib.h>
#include <asm/unistd.h>
#include <linux/reboot.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Query the kernel for various bits pertaining to modules.
// int query_module(const char *name, int which, void *buf, size_t bufsize, size_t *ret);
SYSFUZZ(query_module, __NR_query_module, SYS_NONE, CLONE_DEFAULT, 0)
{
	gpointer    name;
	gpointer    buf;
	gpointer    ret;
	gint        retcode;

    retcode = spawn_syscall_lwp(this, NULL, __NR_query_module,                              // int
                                typelib_get_buffer(&name, g_random_int_range(0, 0x1000)),   // const char *name
                                typelib_get_integer(),                                      // int which
                                typelib_get_buffer(&buf, g_random_int_range(0, 0x1000)),    // void *buf
                                typelib_get_integer(),                                      // size_t bufsize
                                typelib_get_buffer(&ret, g_random_int_range(0, 32)));       // size_t *ret

    typelib_clear_buffer(name);
    typelib_clear_buffer(buf);
    typelib_clear_buffer(ret);

    return retcode;
}

