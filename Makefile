main:
	gcc src/main.c `pkg-config --libs --cflags raylib` -o pong