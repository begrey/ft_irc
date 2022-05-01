#!/bin/bash

while [ 1 ]
	do
		export pid=`ps -ef | grep "ircserv" | grep -v 'grep' | wc -l`
		if [ "$pid" == 1 ];then
			echo "run well"
		else
			echo "Server shutdown, restart."
			make cleanLog
			make fclean
			git pull origin2 master
			make re
			./ircserv 6000 1111
		fi
		sleep 2
	done
