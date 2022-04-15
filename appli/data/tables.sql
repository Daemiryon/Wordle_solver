CREATE TABLE joueur (
	id integer,
	CONSTRAINT joueur_key PRIMARY KEY (id)
);

CREATE TABLE parties (
	id integer,
	idJoueur integer,
	nbEssaisMax integer,
	motATrouver VARCHAR,
	FOREIGN KEY(idJoueur) REFERENCES "joueur"("id")
	CONSTRAINT parties_key PRIMARY KEY (id,idJoueur)
);

CREATE TABLE essais (
	idJoueur integer,
	idPartie integer,
	id integer,
	motEssai VARCHAR,
	FOREIGN KEY(idJoueur) REFERENCES "joueur"("id"),
	FOREIGN KEY(idPartie) REFERENCES "parties"("id"),
	CONSTRAINT essais_key PRIMARY KEY (idJoueur,idPartie,id)
);

