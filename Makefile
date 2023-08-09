CXX=g++
CXX_FLAGS= -Iincludes -std=c++20 -g

exec: bin/exec
	bin/exec

bin/exec: ./src/Main.cpp ./src/bcrypt.cpp  ./src/blowfish_b.cpp ./src/MainUtilities.cpp ./src/User.cpp ./src/XOR.cpp
	$(CXX) $(CXX_FLAGS) ./src/Main.cpp ./src/blowfish_b.cpp ./src/MainUtilities.cpp ./src/bcrypt.cpp ./src/User.cpp ./src/XOR.cpp -o $@

.DEFAULT_GOAL := exec
.PHONY: exec

clean:
	rm -rf bin/*
