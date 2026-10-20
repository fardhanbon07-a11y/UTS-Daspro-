program: src/main.cpp src/fungsi.cpp include/data.h include/fungsi.h
	$(CXX) $(CXXFLAGS) -Iinclude src/main.cpp src/fungsi.cpp -o program

.PHONY: run
run: program
	./program