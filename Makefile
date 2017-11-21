
goal: git scribblemake

scribblemake: scribble.cpp
	gcc -g -o scribble scribble.cpp

git:
	git add .
	@git commit -v -m "made some changes"

clean:
	rm -rf scribble
