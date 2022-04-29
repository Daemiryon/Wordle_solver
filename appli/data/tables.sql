CREATE TABLE PLAYERS (
	idPlayer integer,
	idLastGame integer DEFAULT 0,
	CONSTRAINT players_key PRIMARY KEY (idPlayer)
);

CREATE TABLE GAMES (
	idPlayer integer,
	idGame integer,
	nbMaxTries integer,
	gameEnded INTEGER DEFAULT 0 CHECK(gameEnded>=0 AND gameEnded<=2),
	wordToFind VARCHAR,
	score INTEGER DEFAULT 0,
	difficulty INTEGER DEFAULT 0 CHECK(difficulty>=0 AND difficulty<=9),
	FOREIGN KEY(idPlayer) REFERENCES "PLAYERS"("idPlayer")
	CONSTRAINT games_key PRIMARY KEY (idPlayer,idGame)
);

CREATE TABLE TRIES (
	idPlayer integer,
	idGame integer,
	idTry integer,
	wordTried VARCHAR,
	FOREIGN KEY(idPlayer) REFERENCES "PLAYERS"("idPlayer"),
	FOREIGN KEY(idGame) REFERENCES "GAMES"("idGame"),
	CONSTRAINT tries_key PRIMARY KEY (idPlayer,idGame,idTry)
);

