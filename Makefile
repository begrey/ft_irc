CC = g++
CFLAGS = -std=c++98 -Wall -Werror -Wextra

NAME = ircserv

DIRFTLIB = ./Utils/libft
LIB_LIBFT = libft.a

SRCS = ircserv.cpp Utils/LogTool.cpp Utils/NetSupportUtil.cpp Utils/CommQueue.cpp Utils/KeyInputTool.cpp NetCore/NetCore.cpp IRCCore/IRCCore.cpp IRCCore/ProcessFuncs.cpp
OBJS = ircserv.o LogTool.o NetSupportUtil.o CommQueue.o KeyInputTool.o NetCore.o IRCCore.o ProcessFuncs.o

$(NAME):
	cd $(DIRFTLIB) && $(MAKE)
	$(CC) -c $(SRCS)
	$(CC) -o $(NAME) $(OBJS) -L$(DIRFTLIB) -lft

all: $(NAME)

clean:
	cd $(DIRFTLIB) && $(MAKE) clean
	rm -f $(OBJS)

fclean: clean
	cd $(DIRFTLIB) && $(MAKE) fclean
	rm -f $(NAME)

cleanLog:
	rm -f IRCServLog.txt

re: fclean all