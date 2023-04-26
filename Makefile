.PHONY : all clean build
build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/PacmanICP .
