CC := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++11 -g
RM := rm -rf

NAME := cpplox

SRC_DIR := src/
OBJ_DIR := obj/

HEADERS := common.hpp Lox.hpp ErrorReporter.hpp Token.hpp TokenType.hpp \
Scanner.hpp Expr.hpp Binary.hpp Grouping.hpp Literal.hpp Unary.hpp

SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re