CXX = g++
STD = -std=c++14
BIN = bin/out

% : src/%.cpp
	mkdir -p $(dir $(BIN))
	$(CXX) $(STD) -o $(BIN) $<

.PHONY: clean
clean:
	rm -rf bin

.PHONY: run
run: bin/out
	./bin/out
