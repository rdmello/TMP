
INCLUDES := include/ch1/binary_to_decimal.hpp include/ch1/decimal_to_binary.hpp \
	include/ch2/iter_swap.hpp


all: build/main.run

run: all
	./build/main.run

build/%.run: src/%.cpp $(INCLUDES)
	g++ -Wall -Werror -std=c++11 $< -o $@ -I./include/

clean:
	rm -f ./build/*.run

