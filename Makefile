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
	sudo apt-get install libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth libwavpack1 libwavpack-dev libfreetype-dev wavpack

# Clean the build directory
clean:
	rm -Rf build

clean-for-push: clean 
	rm -rf deps