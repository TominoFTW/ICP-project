.PHONY : all clean build run
build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/PacmanICP .
run: build
	./PacmanICP
clean:
	rm -rf build
	rm -f PacmanICP