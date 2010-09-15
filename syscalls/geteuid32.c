#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <glib.h>
#include <asm/unistd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Get user identity.
SYSFUZZ(geteuid32, __NR_geteuid32, SYS_NONE, CLONE_DEFAULT, 0)
{
	return spawn_syscall_lwp(this, NULL, __NR_geteuid32);     // void
}

