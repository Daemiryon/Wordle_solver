mv database.db database.old.db
{ echo $".open database.db";\
 echo $".read tables.sql";\
 echo $".separator ,";\
 echo $".import players.csv PLAYERS";\
 echo $".import games.csv GAMES";\
 echo $".import tries.csv TRIES";}\
 | sqlite3
