How to anonymize db
-------------------

1. Load not anonymized db dump: `zcat < db-dump.sql.gz  | drush sqlc`
NOTE: Remember to remove not anonymized data from local machine.

2. Enable valghalla_gdpr_dump feature: `drush en valghalla_gdpr_dump -y`

3. Export anonymized db dump :
`drush gdpr-sql-dump | gzip -9 > ../../anonimyzied-db-dump.sql.gz`


Probably you will need to reset the cache after each step: 
`drush cc all`
