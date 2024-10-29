CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -Wextra -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
LIB = _calcPathLoss$(shell python3-config --extension-suffix)


all: ${LIB}
	
${LIB}: src/_calcPathLoss.cpp src/_PathLossStructures.hpp
	${CXX} ${CXXFLAGS} $< -o $@ 

test:
	python3 -m pytest -v

clean: 
	rm -rf *.so __pycache__ .pytest_cache