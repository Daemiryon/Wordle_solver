mv database.db database.old.db
{ echo $".open database.db";\
 echo $".read tables.sql";\
 echo $".separator ,";\
 echo $".import joueurs.csv PLAYERS";\
 echo $".import parties.csv GAMES";\
 echo $".import essais.csv TRIES";}\
 | sqlite3
