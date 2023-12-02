
bin/frogger : src/frogger.cpp include/*.hpp
	c++ src/frogger.cpp -I include -o bin/frogger -lcurses

run : bin/frogger
	./bin/frogger