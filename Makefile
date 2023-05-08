.PHONY : all clean build run doxygen pack
build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/PacmanICP .
run: build
	./PacmanICP
doxygen:
	cd docs && doxygen Doxyfile
pack:
	zip -r xbehal02-xkontr02.zip src/ replays/ examples/ textures/ Makefile -x src/*.pro.user
clean:
	rm -rf docs/html
	rm -rf build
	rm -f PacmanICP
