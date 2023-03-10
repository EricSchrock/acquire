.PHONY: all
all: format build test

.PHONY: format
format:
	clang-format src/* -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

./PHONY: test
test:
	./build/acquire

.PHONY: clean
clean:
	rm -rf build
