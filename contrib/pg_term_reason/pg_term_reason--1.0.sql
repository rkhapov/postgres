/* contrib/pg_term_reason/pg_term_reason--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_term_reason" to load this file. \quit

CREATE FUNCTION pg_terminate_backend_msg(pid integer, timeout int8 DEFAULT 0, reason text DEFAULT '')
RETURNS boolean
AS 'MODULE_PATHNAME', 'pg_terminate_backend_msg'
LANGUAGE C STRICT;

CREATE FUNCTION pg_cancel_backend_msg(pid integer, reason text DEFAULT '')
RETURNS boolean
AS 'MODULE_PATHNAME', 'pg_cancel_backend_msg'
LANGUAGE C STRICT;
