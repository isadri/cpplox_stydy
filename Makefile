CC := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++11 -g
RM := rm -f

NAME := cpplox

CLASSES := Scanner.hpp Token.hpp TokenType.hpp

SRCS := main.cpp Scanner.cpp Token.cpp
OBJS := $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@

%.o: %.cpp $(CLASSES)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re