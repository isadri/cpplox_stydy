CC := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++11 -g
RM := rm -rf

NAME := cpplox

SRC_DIR := src/
OBJ_DIR := obj/

HEADERS := common.hpp Lox.hpp ErrorReporter.hpp Token.hpp TokenType.hpp

SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re