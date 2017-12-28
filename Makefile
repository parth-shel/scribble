
goal: scribblemake git

scribblemake: scribble.cpp
	gcc -g -w -o scribble scribble.cpp /usr/lib/libXbgi.a -lX11 -lm

git:
	git add .
	git commit -v -m "made some changes"

clean:
	rm -rf scribble
