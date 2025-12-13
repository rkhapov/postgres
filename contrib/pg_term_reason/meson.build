pg_term_sources = files(
  'pg_term_reason.c',
)

pg_term_reason = shared_module('pg_term_reason',
  pg_term_sources,
  kwargs: contrib_mod_args,
)
contrib_targets += pg_term_reason

install_data(
  'pg_term_reason--1.0.sql',
  'pg_term_reason.control',
  kwargs: contrib_data_args,
)

tests += {
  'tap': {
    'tests': [
      't/001_basic.pl',
    ],
  },
}
