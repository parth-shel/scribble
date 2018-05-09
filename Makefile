goal: scribblemake

scribblemake: scribble.cpp
	gcc -g -w -o scribble scribble.cpp /usr/lib/libXbgi.a -lX11 -lm

clean:
	rm -rf scribble
