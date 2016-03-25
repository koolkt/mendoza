#
#   Makefile for zappy
#
#

SERVER =	bin/mendoza_server

SERVER_TESTS = server_tests

CC =		g++

CFLAGS =	-Wall -Werror -Wextra -g

RM =		rm -f

INC =		-I./include

SERVER_SOURCES = $(shell find src/  -name "*.cpp")

SRVR_OBJ := $(SERVER_SOURCES:src/%.cpp=build/%.o)

DEPS =	$(shell find ./include  -name "*.hh")

build/%.o : src/%.cpp
	$(CC)  -c $< $(INC) -o $@

all:		$(SERVER)

$(SERVER):	$(SRVR_OBJ) $(DEPS)
		$(CC) $(CFLAGS) $(INC) $(SRVR_OBJ) -o $@

#runtests:

clean:
			$(RM) $(SRVR_OBJ)

fclean:		clean
			$(RM) $(SERVER) bin/$(SERVER)

re:			fclean $(SERVER)

.PHONY:			all clean fclean re
