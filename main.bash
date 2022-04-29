# Define the link target.
linkTarget = a.out

# Define the libraries that we need.
LIBS = -L./usr/lib/x86_64-linux-gnu/libSDL2_2.0.so -lSDL2 -L ./usr/lib/x86_64-linux-gnu/libSDL2_gfx.so ./usr/lib/x86_64-linux-gnu/libSDL2_gfx.a
# Define any flags.
CFLAGS = -std=c++17  #-Ofast

# Define the object files that we need to use.
objects =	*.cpp #$(patsubst %.cpp,%.o,$(wildcard ./*.cpp)) 
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build. $(objects)
$(linkTarget): $(objects)
	clang++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o (object) files.
%.o: %.cpp
	clang++ -o $@ -c $< $(CFLAGS)
	
.PHONEY:
clean:
	rm $(linkTarget)