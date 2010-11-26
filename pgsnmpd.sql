CREATE TABLE pgsnmpd_rdbmsDbTable (
	-- ideally this would reference pg_database.oid, but pgsql won't allow such a reference
	database_oid OID PRIMARY KEY,
	vendor_name VARCHAR(255) DEFAULT 'PostgreSQL Global Development Group',
	contact_name VARCHAR(255),
	last_backup TIMESTAMPTZ);

CREATE TABLE pgsnmpd_rdbmsSrvTable (
	vendor_name VARCHAR(255) DEFAULT 'PostgreSQL Global Development Group',
	product_name VARCHAR(255) DEFAULT 'PostgreSQL',
	contact_name VARCHAR(255));
