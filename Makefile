
goal: scribblemake git

scribblemake: scribble.cpp
	gcc -g -w -o scribble scribble.cpp /usr/lib64/libXbgi.a -lm

git:
	git add .
	@git commit -v -m "made some changes"

clean:
	rm -rf scribble
