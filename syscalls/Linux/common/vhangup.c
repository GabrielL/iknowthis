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

// Virtually hangup the current tty.
SYSFUZZ(vhangup, __NR_vhangup, SYS_FAIL | SYS_BORING | SYS_SAFE, CLONE_DEFAULT, 0)
{
	return syscall_fast(__NR_vhangup);              // int
}

