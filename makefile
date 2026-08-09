app ?="authchanger"
installPath ?= "/usr/bin"
build:
	g++  main.cxx -o ${app} -I toml++/

install: build
	cp ${app} ${installPath}
	cp -r .userlist/ ${installPath}

