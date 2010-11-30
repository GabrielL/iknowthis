#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <glib.h>
#include <asm/unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Change permissions of a file.
// int chmod(const char *path, mode_t mode);
SYSFUZZ(chmod, __NR_chmod, SYS_NONE, CLONE_DEFAULT, 0)
{
    gchar *pathname;
    glong  retcode;

    // Execute systemcall.
    retcode = spawn_syscall_lwp(this, NULL, __NR_chmod,             // int
                                typelib_get_pathname(&pathname),    // const char *pathname
                                typelib_get_integer());             // mode_t mode

    g_free(pathname);
    return retcode;
}
