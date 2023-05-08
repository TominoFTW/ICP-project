.PHONY : all clean build run doxygen pack
build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/PacmanICP .
run: build
	./PacmanICP
doxygen:
	doxygen Doxyfile
pack: clean
	zip -r xbehal02-xkontr02.zip src/ replays/ examples/ textures/ Makefile README.txt doc/
clean:
	rm -rf doc/html
	rm -rf build
	rm -f PacmanICP
