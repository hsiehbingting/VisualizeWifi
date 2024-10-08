CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -Wextra -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
LIB = _calc_path_loss$(shell python3-config --extension-suffix)


all: ${LIB}
	
${LIB}: cpp/calc_path_loss.cpp
	${CXX} ${CXXFLAGS} $^ -o $@ 

test:
	python3 -m pytest -v

clean: 
	rm -rf *.so __pycache__ .pytest_cache