
#ifndef SIGNALFUNCS_H
#define SIGNALFUNCS_H

#include <postgres.h>

Datum
pg_terminate_backend_impl(int pid, int timeout);

Datum
pg_cancel_backend_impl(int pid);

#endif /* SIGNALFUNCS_H */
