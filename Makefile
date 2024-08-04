all:
	gcc -Isrc/Include -ICode_Files -IHeader_Files  -Lsrc/lib -o Tetris Code_Files/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf