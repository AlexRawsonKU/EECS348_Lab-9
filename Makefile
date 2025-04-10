# Lazy approach; rebuilds everything every time. Not a problem for ~~3~~ 2 small files though
lab9.exe: matrix.hpp main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^