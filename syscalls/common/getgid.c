#include <glib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Get group identity.
// gid_t getgid(void);
SYSFUZZ(getgid, SYS_getgid, SYS_SAFE | SYS_BORING, CLONE_DEFAULT, 0)
{
    return spawn_syscall_lwp(this, NULL, SYS_getgid);      // gid_t
}

