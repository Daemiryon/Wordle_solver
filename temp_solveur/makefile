# Macros
exec = clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
comp = clang -c -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
toexe = -o
toobj = -o

# -----
# Execution
solveur: main
	@exe/main

table: test_table_occ
	@exe/test_table_occ

tree: test_tree
	@exe/test_tree

# -----
# Création des exécutables
main: obj/main.o obj/tree.o obj/occurence_table.o obj/dictionnary.o
	$(exec) obj/main.o obj/tree.o obj/occurence_table.o obj/dictionnary.o $(toexe) exe/main

test_table_occ: obj/occurence_table.o obj/test_table_occ.o
	$(exec) obj/occurence_table.o obj/test_table_occ.o $(toexe) exe/test_table_occ

test_tree: obj/test_tree.o obj/tree.o
	$(exec) obj/test_tree.o obj/tree.o $(toexe) exe/test_tree

# -----
# Création des fichiers objets
obj/main.o: src/dictionnary.h src/occurence_table.h src/tree.h src/main.c
	$(comp) src/main.c $(toexe) obj/main.o

obj/dictionnary.o: src/dictionnary.h src/dictionnary.c
	$(comp) src/dictionnary.c $(toobj) obj/dictionnary.o

obj/occurence_table.o: src/occurence_table.h src/occurence_table.c
	$(comp) src/occurence_table.c $(toobj) obj/occurence_table.o

obj/tree.o: src/tree.h src/tree.c
	$(comp) src/tree.c $(toobj) obj/tree.o

obj/test_table_occ.o: src/occurence_table.h src/test_table_occ.c
	$(comp) src/test_table_occ.c $(toobj) obj/test_table_occ.o

obj/test_tree.o: src/tree.h src/test_tree.c
	$(comp) src/test_tree.c $(toobj) obj/test_tree.o

# -----
# clean obj and exe repertories
clean:
	@rm -f obj/*.o exe/*