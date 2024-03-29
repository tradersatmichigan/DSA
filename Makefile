CXX = g++
STD = -std=c++11
BIN = bin/out

% : src/%.cpp
	mkdir -p BIN
	$(CXX) $(STD) -o $(BIN) $<

.PHONY: clean
clean:
	rm -rf bin
