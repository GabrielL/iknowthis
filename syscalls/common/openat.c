#include <glib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Callback for typelib_add_resource().
static gboolean destroy_open_file(guintptr fd)
{
    return close(fd) != -1;
}

// Open and possibly create a file or device.
// int openat(int dirfd, const char *pathname, int flags, mode_t mode);
SYSFUZZ(openat, SYS_openat, SYS_NONE, CLONE_DEFAULT, 1000)
{
    gchar *pathname;
    glong  retcode;
    glong  fd = -1;

    // Execute systemcall.
    retcode = spawn_syscall_lwp(this, &fd, SYS_openat,                                      // int
                                     typelib_get_resource(this, NULL, RES_FILE, RF_NONE),   // int dirfd
                                     typelib_get_pathname(&pathname),                       // const char *pathname
                                     typelib_get_integer(),                                 // int flags
                                     typelib_get_integer());                                // mode_t mode

    // Record the new file descriptor.
    if (retcode == ESUCCESS) {
        typelib_add_resource(this, fd, RES_FILE, RF_NONE, destroy_open_file);
    }

    // Release string.
    g_free(pathname);

    return retcode;
}

