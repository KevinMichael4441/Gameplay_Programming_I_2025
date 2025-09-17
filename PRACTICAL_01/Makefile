.DEFAULT_GOAL := build

build:
	@echo "Build started"
	g++ -o sampleapp ./src/main.cpp ./src/sample_function.cpp -I.
	@echo "Build Complete!"
	./sampleapp #Automatically run the program!

clean:
	@echo "Cleaning up!"
	rm *.o
