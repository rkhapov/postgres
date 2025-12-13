# contrib/pg_term_reason/Makefile

MODULE_big = pg_term_reason
OBJS = \
	pg_term_reason.o

EXTENSION = pg_term_reason
DATA = pg_term_reason--1.0.sql
PGFILEDESC = "pg_term_reason - add pg_terminate_backend_reasoned function"

TAP_TESTS = 1

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/pg_term_reason
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
