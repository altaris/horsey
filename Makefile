format:
	clang-format										\
	--sort-includes	 									\
	--style="{BasedOnStyle: mozilla, IndentWidth: 4}"   \
	--verbose	   										\
	-i *.cpp *.h
