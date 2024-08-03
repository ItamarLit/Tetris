all:
	gcc -Isrc/Include -Lsrc/lib -o Tetris Tetris.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf