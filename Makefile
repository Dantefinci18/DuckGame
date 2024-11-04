.PHONY: all test clean clean-for-push editor client common server build compile-debug install-deps run-tests

build: install-deps compile-debug

# Default target
all: clean build

# Run tests after compiling
run-tests: all
	./build/taller_tests

# Compile the project in debug mode
compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build build/ $(EXTRA_COMPILE)

# Install dependencies, including yaml-cpp
install-deps:
	if [ -d "deps/yaml-cpp" ]; then \
		echo "yaml-cpp ya está instalado."; \
	else \
		echo "yaml-cpp no encontrado. Instalando..."; \
		mkdir -p deps && cd deps && \
		git clone https://github.com/jbeder/yaml-cpp.git && \
		cd yaml-cpp && \
		mkdir build && cd build && \
		cmake .. && \
		make && \
		sudo make install; \
	fi



# Clean the build directory
clean:
	rm -Rf build

clean-for-push: clean 
	rm -rf deps