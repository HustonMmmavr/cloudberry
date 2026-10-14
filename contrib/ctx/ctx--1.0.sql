\echo Use "CREATE EXTENSION ctx" to load this file. \quit

CREATE FUNCTION test_ctx()
RETURNS VOID
AS 'MODULE_PATHNAME'
LANGUAGE C;
