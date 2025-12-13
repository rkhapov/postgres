use strict;
use warnings FATAL => 'all';
use PostgreSQL::Test::Cluster;
use PostgreSQL::Test::Utils;
use Test::More;

my $node = PostgreSQL::Test::Cluster->new('primary');
$node->init();
$node->start;

$node->safe_psql('postgres', 'create extension pg_term_reason;');

my ($stdout, $stderr);
$node->psql('postgres',
	q[select pg_terminate_backend_msg(pg_backend_pid(), 0, 'hello from tap tests!');],
	stdout => \$stdout, stderr => \$stderr);
like($stderr, qr/hello from tap tests\!/, "expected message to be passed");

$stdout = '';
$stderr = '';
$node->psql('postgres',
	q[select pg_cancel_backend_msg(pg_backend_pid(), 'hello from tap tests again!');],
	stdout => \$stdout, stderr => \$stderr);
like($stderr, qr/hello from tap tests again\!/, "expected message to be passed");

$node->stop;

done_testing();
