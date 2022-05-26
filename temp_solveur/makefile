# Macros
exec = clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
comp = clang -c -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
toexe = -o
toobj = -o

# -----
# Execution
main: main.exe
	@exe/main.exe

table: test_table_occ.exe
	@exe/test_table_occ.exe

tree: test_tree.exe
	@exe/test_tree.exe

dic: dictionnary_test.exe
	@exe/dictionnary_test.exe

# -----
# Création des exécutables
main.exe: obj/main.o obj/tree.o obj/occurence_table.o obj/dictionnary.o obj/Entropy.o
	$(exec) obj/main.o obj/tree.o obj/occurence_table.o obj/dictionnary.o obj/Entropy.o $(toexe) exe/main.exe

test_table_occ.exe: obj/occurence_table.o obj/test_table_occ.o
	$(exec) obj/occurence_table.o obj/test_table_occ.o $(toexe) exe/test_table_occ.exe

test_tree.exe: obj/test_tree.o obj/tree.o obj/occurence_table.o obj/dictionnary.o
	$(exec) obj/test_tree.o obj/tree.o obj/occurence_table.o obj/dictionnary.o $(toexe) exe/test_tree.exe

dictionnary_test.exe: obj/dictionnary.o obj/dictionnary_test.o obj/occurence_table.o
	$(exec) obj/dictionnary.o obj/dictionnary_test.o obj/occurence_table.o $(toexe) exe/dictionnary_test.exe

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

obj/Entropy.o: src/Entropy.h src/Entropy.c
	$(comp) src/Entropy.c $(toobj) obj/Entropy.c

obj/test_table_occ.o: src/occurence_table.h src/test_table_occ.c
	$(comp) src/test_table_occ.c $(toobj) obj/test_table_occ.o

obj/test_tree.o: src/tree.h src/test_tree.c
	$(comp) src/test_tree.c $(toobj) obj/test_tree.o

obj/dictionnary_test.o: src/dictionnary.h src/dictionnary_test.c
	$(comp) src/dictionnary_test.c $(toobj) obj/dictionnary_test.o

# -----
# clean obj and exe repertories
clean:
	@rm -f obj/*.o exe/*