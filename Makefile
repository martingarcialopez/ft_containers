NAME =		a.out

CXX =		clang++
CFLAGS =	-Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3

SRCS =		main_vector.cpp

OBJS =		$(SRCS:%.cpp=%.o)

all: $(NAME)

clean:
				$(RM) $(OBJS)
				rm -rf ft std

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re test ft std

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $? -o $(NAME)

ft: $(SRCS)
	$(CXX) $(CFLAGS) -D FT $? -o $(NAME)

std: $(SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(NAME)

test:
	$(RM) $(NAME)
	make ft
	./$(NAME) > ft
	$(RM) $(NAME)
	make std
	./$(NAME) > std
	$(RM) $(NAME)
	diff ft std
