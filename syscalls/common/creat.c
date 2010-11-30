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

// Callback for typelib_add_resource().
static gboolean destroy_open_file(guintptr fd)
{
    return syscall(__NR_close, fd) != -1;
}

// Create a file or device.
// int creat(const char *pathname, mode_t mode);
SYSFUZZ(creat, __NR_creat, SYS_NONE, CLONE_DEFAULT, 1000)
{
    gchar *pathname;
    glong  retcode;
    glong  fd;

    // Execute systemcall.
    retcode = spawn_syscall_lwp(this, &fd, __NR_creat,                 // int
                                typelib_get_pathname(&pathname),       // const char *pathname
                                typelib_get_integer());                // mode_t mode

    // Record the new file descriptor.
    if (retcode == ESUCCESS) {
        typelib_add_resource(this, fd, RES_FILE, RF_NONE, destroy_open_file);
    }

    // Release string.
    g_free(pathname);

    return retcode;
}
