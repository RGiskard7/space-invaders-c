CC=gcc
CPLUS=g++
CFLAGS=-g -Wall -pedantic
EJECUTABLES=SpaceInvaders.exe
DIR=spaceInvaders

ALLEGRO_VERSION=5.2.9.1
MINGW_VERSION=14.1.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
#LIB_ALLEGRO=\lib\liballegro_monolith.dll.a

LIB_ALLEGRO=\lib
INCLUDE_ALLEGRO=\include

# Archivos fuente y objetos
SRCS=src/main.c src/game.c src/bullet.c src/ship.c src/martian.c src/object.c
OBJS=main.o game.o bullet.o ship.o martian.o object.o

# Regla por defecto
all: $(EJECUTABLES)

# Regla para compilar el ejecutable
$(EJECUTABLES): $(OBJS)
	@echo "----------------------------------------------------------"
	@echo "Makefile SpaceInvaders hecho por RGiskard7"
	@echo "Ejecuta make help para mas informacion"
	@echo "----------------------------------------------------------"
	$(CC) $(CFLAGS) -o $(EJECUTABLES) $(OBJS) -L $(PATH_ALLEGRO)$(LIB_ALLEGRO) -lallegro_monolith -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf

# Regla para compilar main.o
main.o: src/main.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/main.c -o main.o

# Regla para compilar game.o
game.o: src/game.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/game.c -o game.o

# Regla para compilar bullet.o
bullet.o: src/bullet.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/bullet.c -o bullet.o

# Regla para compilar ship.o
ship.o: src/ship.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/ship.c -o ship.o

# Regla para compilar martian.o
martian.o: src/martian.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/martian.c -o martian.o

# Regla para compilar object.o
object.o: src/object.c
	$(CC) -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I include $(CFLAGS) -c src/object.c -o object.o

# Regla para limpiar los archivos generados
clean:
	del *.o $(EJECUTABLES)

# Regla para empaquetar los archivos
dist: src/*.c include/*.h Makefile
	tar -cvzf $(DIR).tgz src/*.c include/*.h Makefile

# Regla de ayuda
help:
	@echo "AYUDA:"
	@echo "--make dist: Crea un paquete tgz con los ficheros del programa."
	@echo "--make clean: Borra todos los ficheros .o y el ejecutable."

.PHONY: all clean dist help