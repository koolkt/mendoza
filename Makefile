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

TEST_SOURCES = $(shell find src/  -name "*.cpp" ! -name 'main.cpp')

SRVR_OBJ := $(SERVER_SOURCES:src/%.cpp=build/%.o)

TEST_OBJ := $(TEST_SOURCES:src/%.cpp=build/%.o)

TEST1_OBJ  = tests/test_basic_network/build/test_main.o

DEPS =	$(shell find ./include  -name "*.hh")

# tests/test_basic_network/build/test_main.o : tests/test_basic_network/src/test_main.cpp
# 	$(CC)  -c $< $(INC) -o $@

build/%.o : src/%.cpp
	$(CC)  -c $< $(INC) -o $@

# %build/%.o : %src/%.cpp
# 	$(CC)  -c $< $(INC) -o $@

all:		$(SERVER)

$(SERVER):	$(SRVR_OBJ) $(DEPS)
		$(CC) $(CFLAGS) $(INC) $(SRVR_OBJ) -o $@

clean:
			$(RM) $(SRVR_OBJ)

test1:		$(TEST_OBJ) $(DEPS) $(TEST1_OBJ)
		$(CC) $(CFLAGS) $(INC) $(TEST1_OBJ) $(TEST_OBJ) -o $@

fclean:		clean
			$(RM) $(SERVER) bin/$(SERVER)

re:			fclean $(SERVER)

.PHONY:			all clean fclean re tests
