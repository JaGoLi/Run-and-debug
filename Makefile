build: list_files.c
	gcc -lncurses -o list_files list_files.c

cpp: list_files.cpp
	g++ -lncurses -o list_files list_files.cpp

c-clang: list_files.c
	clang -lncurses -o list_files list_files.c

cpp-clang: list_files.cpp
	clang++ -lncurses -o list_files list_files.cpp

.PHONY: clean

clean:
	rm -f list_files
