build:
	cmake

clang-format:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

clean:
	git clean -fdx

gear-build:
	gear-hsh --verbose --lazy-cleanup --commit

