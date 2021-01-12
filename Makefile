
.PHONY: all inter link clean

all: inter link

inter:
	cmake . -B.build

link:
	cmake --build .build

clean:
	rm -rf .build/
