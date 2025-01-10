#!/bin/bash
#
PATH=/bin:/sbin:/usr/local/bin
export PATH
read -p "Please input (in/out)" cz

if [ ${cz} == "in" ]; then
	cp -v ~/.profile ~/.bashrc ~/.vimrc ./
	cp -rv ~/.ssh ./
fi

if [ ${cz} == "out" ]; then
	cp -iv ./.profile ./.bashrc ./.vimrc ~/
fi
