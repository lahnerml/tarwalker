CXX=clang++
CXX_FLAGS=-Wall -Werror -Wpedantic -std=c++17
CXX_FLAGS_REL=-O3 -march=native -g -DNDEBUG
CXX_FLAGS_DBG=-O0 -g3 -DDEBUG

SRCS=main.cpp
NAME=tarwalker

release:
	$(CXX) $(CXX_FLAGS) $(CXX_FLAGS_REL) $(SRCS) -o ${NAME}

debug:
	$(CXX) $(CXX_FLAGS) $(CXX_FLAGS_DBG) $(SRCS) -o ${NAME}

clean:
	rm -rf $(NAME)*
