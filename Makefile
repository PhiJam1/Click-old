CXX=g++
CXX_FLAGS= -Iincludes -std=c++20

exec: bin/exec
	bin/exec

bin/exec: ./src/MainTester.cpp ./src/User.cpp 
	$(CXX) $(CXX_FLAGS) ./src/MainTester.cpp ./src/User.cpp -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*
