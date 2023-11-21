CXX=g++
CXX_FLAGS= -Iincludes -std=c++20 -g

CIPHER_FILES = ./src/bcrypt.cpp  ./src/bcryptUtilities.cpp ./src/XOR.cpp ./src/blowfishUS.cpp

exec: bin/exec
	bin/exec

bin/exec: ./src/Main.cpp ./src/MainUtilities.cpp ./src/User.cpp $(CIPHER_FILES)
	$(CXX) $(CXX_FLAGS) ./src/Main.cpp ./src/MainUtilities.cpp  ./src/User.cpp $(CIPHER_FILES) -o $@

.DEFAULT_GOAL := exec
.PHONY: exec

clean:
	rm -rf bin/*
