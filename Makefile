# -*- MakeFile -*-

VPATH	=	parsing helper includes list_token variable_expansion echo \
			utility pwd env export
NAME	=	minishell
FUNCTS	=	minishell.c				\
				find_token.c		\
				token_add_back.c	\
				token_add_front.c	\
				token_clear.c		\
				token_delone.c		\
				token_last.c		\
				token_new.c			\
				token_size.c		\
				cmd_searchlst.c		\
				expand_variable.c	\
				utilities.c			\
				parse_function.c	\
				ft_echo.c			\
				ft_pwd.c			\
				ft_env.c			\
				copy_envp.c			\
				ft_getenv.c			\
				ft_export.c			\
				extract_quote_node.c	\
				extract_var_node.c	\
				extract_arg_node.c	\
				extract_token_node.c	\
				testing.c
LIBFTNAME =	ft
OBJS	=	$(addprefix $(OBJ_PATH),$(notdir $(FUNCTS:.c=.o)))
CC		=	cc
CFLAGS	= 	-Wall -Werror -Wextra
OBJ_PATH =	./obj/
LIBFTPATH =	./libft/
RLPATH	=	./readline/
IFLAGS	=	-I ./includes -I ./readline
RM 		=	/bin/rm -f
RMR		=	/bin/rm -rf
DEPEND	=	-MMD -MP

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	make -C $(LIBFTPATH)
	cd $(RLPATH) && sh ./configure
	make -C $(RLPATH)
	$(CC) -o $(NAME) $(IFLAGS) $(DEPEND) $(OBJS) -L $(LIBFTPATH) -l $(LIBFTNAME) -ltermcap \
		-L $(RLPATH) -lreadline -L $(RLPATH) -lhistory -L $(RLPATH)

$(OBJ_PATH) :
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPEND) -c $< -o $@

clean:
	make clean -C $(LIBFTPATH)
	make mostlyclean -C $(RLPATH)
	$(RMR) $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFTPATH)
	make clean -C $(RLPATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
-include $(OBJS:.o=.d)
