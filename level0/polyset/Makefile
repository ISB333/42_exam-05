NAME = polyset

SRCS_DIR = .
SUBJ_DIR = subject/subject
OBJ_DIR = objs

SRCS = polyset.cpp \
       searchable_array_bag.cpp \
       searchable_tree_bag.cpp \
       set.cpp \
       $(SUBJ_DIR)/array_bag.cpp \
       $(SUBJ_DIR)/tree_bag.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I. -I$(SUBJ_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SUBJ_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
