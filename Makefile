#
#   Makefile for zappy
#
#

SERVER =	bin/mendoza_server

TESTS_DIR =	tests

TEST1_DIR =	$(TESTS_DIR)/test_basic_network

TEST2_DIR =	$(TESTS_DIR)/test_smtp

TEST1 = 	$(TEST1_DIR)/bin/test1

TEST2 = 	$(TEST2_DIR)/bin/test2

TESTS =		$(TEST1) $(TEST2)

CC =		g++

CFLAGS =	-std=c++11 -Wall -Werror -Wextra -g

RM =		rm -f

INC =		-I./include

SERVER_SOURCES = $(shell find src/  -name "*.cpp")

TEST_SOURCES = $(shell find src/  -name "*.cpp" ! -name 'main.cpp')

SRVR_OBJ := $(SERVER_SOURCES:src/%.cpp=build/%.o)

TEST_OBJ := $(TEST_SOURCES:src/%.cpp=build/%.o)

###### TESTS

MAIN1_OBJ  = $(TEST1_DIR)/build/test_main.o

MAIN2_OBJ  = $(TEST2_DIR)/build/test_main.o

######

DEPS =	$(shell find ./include  -name "*.hh")

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

tests/%/build/test_main.o : tests/%/src/test_main.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

all:		$(SERVER) $(TEST1)


$(SERVER):	$(SRVR_OBJ) $(DEPS)
		$(CC) $(CFLAGS) $(INC) $(SRVR_OBJ) -o $@

run_tests:	$(TESTS)
		python3 -m unittest

test_basic :	$(TEST1)

test_smtp :	$(TEST2)

$(TEST1):	$(TEST_OBJ) $(DEPS) $(MAIN1_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN1_OBJ) $(TEST_OBJ) -o $@

$(TEST2):	$(TEST_OBJ) $(DEPS) $(MAIN2_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN2_OBJ) $(TEST_OBJ) -o $@

clean_tests:
			$(RM) $(TEST1_OBJ) $(TEST2_OBJ) $(TEST_OBJ) $(MAIN1_OBJ) $(MAIN2_OBJ)

clean:
			$(RM) $(SRVR_OBJ)

fclean:		clean clean_tests
			$(RM) $(SERVER) $(TESTS)

re:			fclean $(SERVER) $(TESTS)

re_tests:		fclean run_tests

.PHONY:			all clean fclean re clean_tests run_tests re_tests
