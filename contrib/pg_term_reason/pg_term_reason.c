/*-------------------------------------------------------------------------
 *
 * pg_term_reason.c
 *	  Functions to terminate/cancel postgres backends with additional message
 *
 * IDENTIFICATION
 *	  contrib/pg_term_reason/pg_term_reason.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "fmgr.h"
#include "varatt.h"
#include "storage/signalfuncs.h"
#include "storage/lock.h"
#include "storage/procarray.h"
#include "storage/proc.h"

PG_MODULE_MAGIC_EXT(
					.name = "pg_term_reason",
					.version = PG_VERSION
);

PG_FUNCTION_INFO_V1(pg_terminate_backend_msg);
PG_FUNCTION_INFO_V1(pg_cancel_backend_msg);

static void
set_reason(int pid, const char *msg, int msglen)
{
	int			len;
	PGPROC		*proc;

	if (msglen <= 0) {
		return;
	}

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	proc = BackendPidGetProcWithLock(pid);

	if (proc != NULL) {
		len = Min(PROC_TERM_REASON_MAX_LEN - 1, msglen);
		strncpy(proc->termReasonStr, msg, len);
	}

	LWLockRelease(ProcArrayLock);
}

Datum
pg_cancel_backend_msg(PG_FUNCTION_ARGS)
{
	int			pid;
	text		*reason;
	char		*reason_str;
	int			reason_len;

	pid = PG_GETARG_INT32(0);
	reason = PG_GETARG_TEXT_P(1);

	reason_str = VARDATA(reason);
	reason_len = VARSIZE(reason) - VARHDRSZ;

	set_reason(pid, reason_str, reason_len);

	return pg_cancel_backend_impl(pid);
}

Datum
pg_terminate_backend_msg(PG_FUNCTION_ARGS)
{
	int			pid;
	int			timeout;		/* milliseconds */
	text		*reason;
	char		*reason_str;
	int			reason_len;

	pid = PG_GETARG_INT32(0);
	timeout = PG_GETARG_INT64(1);
	reason = PG_GETARG_TEXT_P(2);

	reason_str = VARDATA(reason);
	reason_len = VARSIZE(reason) - VARHDRSZ;

	set_reason(pid, reason_str, reason_len);

	return pg_terminate_backend_impl(pid, timeout);
}
