program: main.o fungsi.o
	$(CXX) $(CXXFLAGS) main.o fungsi.o -o program

main.o: main.cpp data.h fungsi.h
	$(CXX) $(CXXFLAGS) -c main.cpp

fungsi.o: fungsi.cpp fungsi.h data.h
	$(CXX) $(CXXFLAGS) -c fungsi.cpp

run:
	./program