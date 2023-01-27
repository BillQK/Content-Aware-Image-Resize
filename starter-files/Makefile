# Makefile
# Build rules for CS 3520 Homework 2

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Wextra -pedantic -g

# Run a regression test
test: matrix_public_test.exe matrix image_public_test.exe image processing_public_tests.exe resize.exe
	./matrix
	./image
	./processing_public_tests.exe
	./resize.exe dog.ppm dog_4x5.out.ppm 4 5
	diff dog_4x5.out.ppm dog_4x5.correct.ppm

matrix_public_test.exe: Matrix_public_test.cpp Matrix.cpp Matrix_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

matrix: Matrix_tests.cpp Matrix.cpp Matrix_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

image_public_test.exe: Image_public_test.cpp Matrix.cpp Image.cpp \
			Matrix_test_helpers.cpp Image_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

image: Image_tests.cpp Matrix.cpp Image.cpp Matrix_test_helpers.cpp \
			Image_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

processing_public_tests.exe: processing_public_tests.cpp Matrix.cpp \
				Image.cpp processing.cpp \
				Matrix_test_helpers.cpp Image_test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

resize.exe: resize.cpp Matrix.cpp Image.cpp processing.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf *.exe *.out.txt *.out.ppm *.dSYM *.stackdump

