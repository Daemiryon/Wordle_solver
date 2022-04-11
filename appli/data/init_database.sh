mv database.db database.old.db
{ echo $".open database.db";\
 echo $".read tables.sql";\
 echo $".separator ,";\
 echo $".import joueurs.csv joueurs";\
 echo $".import parties.csv parties";\
 echo $".import essais.csv essais";}\
 | sqlite3
