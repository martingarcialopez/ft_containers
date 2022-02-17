VECTOR 	=		ft_vector
VECTOR2	=		std_vector
MAP	=		ft_map
MAP2	=		std_map
STACK	=		ft_stack
STACK2	=		std_stack

ALL	=	$(VECTOR) $(VECTOR2) $(MAP) $(MAP2) $(STACK) $(STACK2)

RM = 	rm -rf

CXX =		clang++
CFLAGS =	-Wall -Werror -Wextra -std=c++98 #-fsanitize=address -g3

V_SRCS =		main_vector.cpp
M_SRCS =		main_map.cpp
S_SRCS =		main_stack.cpp

INCLUDES =		vector.hpp map.hpp stack.hpp

V_OBJS =		$(V_SRCS:%.cpp=%.o)
M_OBJS =		$(M_SRCS:%.cpp=%.o)
S_OBJS =		$(S_SRCS:%.cpp=%.o)


all: 			ft_vector ft_map ft_stack



clean:
				$(RM) $(V_OBJS) $(M_OBJS) $(S_OBJS)
				$(RM) *ft *std 

fclean:			clean
				$(RM) $(ALL)

re:				fclean all

.PHONY:			all clean fclean re test ft std

%.o: %.cpp $(INCLUDES)
	@$(CXX) $(CFLAGS) -c $< -o $@

ft_vector: $(V_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(VECTOR)

std_vector: $(V_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(VECTOR2)

vector:
	@$(RM) $(VECTOR)
	@$(RM) $(VECTOR2)
	@make -s ft_vector
	./$(VECTOR) > vft
	@make -s std_vector
	./$(VECTOR2) > vstd
	diff -s vft vstd

ft_map: $(M_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(MAP)

std_map: $(M_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(MAP2)

map:
	@$(RM) $(MAP)
	@$(RM) $(MAP2)
	@make -s ft_map
	./$(MAP) > mft
	@make -s std_map
	./$(MAP2) > mstd
	diff -s mft mstd

ft_stack: $(S_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(STACK)

std_stack: $(S_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(STACK2)

stack:
	@$(RM) $(STACK)
	@$(RM) $(STACK2)
	@make -s ft_stack
	./$(STACK) > sft
	@make -s std_stack
	./$(STACK2) > sstd
	diff -s sft sstd
