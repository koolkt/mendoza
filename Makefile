#
#   Makefile for zappy
#
#

SERVER =	bin/mendoza_server

TESTS_DIR =	tests

TEST1_DIR =	$(TESTS_DIR)/test_basic_network

TEST1 = 	$(TEST1_DIR)/bin/test1

TESTS =		$(TEST1)

CC =		g++

CFLAGS =	-Wall -Werror -Wextra -g

RM =		rm -f

INC =		-I./include

SERVER_SOURCES = $(shell find src/  -name "*.cpp")

TEST_SOURCES = $(shell find src/  -name "*.cpp" ! -name 'main.cpp')

SRVR_OBJ := $(SERVER_SOURCES:src/%.cpp=build/%.o)

TEST_OBJ := $(TEST_SOURCES:src/%.cpp=build/%.o)

###### TEST1

MAIN1_OBJ  = $(TEST1_DIR)/build/test_main.o

################

DEPS =	$(shell find ./include  -name "*.hh")

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

tests/%/build/test_main.o : tests/%/src/test_main.cpp
	$(CC)  -c $< $(INC) -o $@

all:		$(SERVER) $(TEST1)


$(SERVER):	$(SRVR_OBJ) $(DEPS)
		$(CC) $(CFLAGS) $(INC) $(SRVR_OBJ) -o $@

run_tests:	$(TESTS)
		python -m unittest

test1 :		$(TEST1)
		python $(TEST1_DIR)/test_basic_sockets.py

$(TEST1):	$(TEST_OBJ) $(DEPS) $(MAIN1_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN1_OBJ) $(TEST_OBJ) -o $@

clean_tests:
			$(RM) $(TEST1_OBJ) $(TEST_OBJ)

clean:
			$(RM) $(SRVR_OBJ)

fclean:		clean clean_tests
			$(RM) $(SERVER) $(TESTS)

re:			fclean $(SERVER)

.PHONY:			all clean fclean re clean_tests run_tests
