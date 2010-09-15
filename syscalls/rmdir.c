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

// Delete a directory.
SYSFUZZ(rmdir, __NR_rmdir, SYS_NONE, CLONE_DEFAULT, 0)
{
	gchar   *pathname;
	gint     retcode;

	retcode = spawn_syscall_lwp(this, NULL, __NR_rmdir,                                             // int
	                            typelib_get_pathname(&pathname));                                   // const char *pathname

    g_free(pathname);
    return retcode;
}

