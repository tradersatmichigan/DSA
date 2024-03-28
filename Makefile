CXX = g++
STD = -std=c++11

% : src/%.cpp
	$(CXX) $(STD) -o $@ $<
