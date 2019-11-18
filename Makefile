build:
	cmake

clang-format:
	clang-format

clean:
	git clean -fdx

gear-build:
	gear-hsh --verbose --lazy-cleanup --commit

