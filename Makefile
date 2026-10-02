# Makefile du pilote ParadoxTitan
# Projet Grand Prix F1 - Challenge de programmation, ENSICAEN.
# Equipe ParadoxTitan - Khalil Anbari, Aya Khouya - mai 2026.

PILOT_NAME   = paradoxtitan

CC           = gcc
CFLAGS       = -ansi -pedantic -Wall -Wextra
CPPFLAGS     = -I./include
LDLIBS       = -lm

SRC_DIR      = src
OBJ_DIR      = obj
INSTALL_DIR  = ../drivers

SRCS         = $(wildcard $(SRC_DIR)/*.c)
OBJS         = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean distclean install reinstall run

all: $(PILOT_NAME)

$(PILOT_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

install: $(PILOT_NAME)
	mkdir -p $(INSTALL_DIR)
	cp $(PILOT_NAME) $(INSTALL_DIR)/$(PILOT_NAME)
	chmod +x $(INSTALL_DIR)/$(PILOT_NAME)

reinstall: distclean all install

clean:
	rm -f $(OBJ_DIR)/*.o

distclean: clean
	rm -f $(PILOT_NAME)
	rm -f $(INSTALL_DIR)/$(PILOT_NAME)

run: install
	cd .. && ./GrandPrix
