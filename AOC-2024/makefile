# Directories to manage
DAYS := $(shell seq -w 1 25 | sed 's/^/day/')

# Default target
.PHONY: all
all:
	@echo "Available options:"
	@echo "  make clean          - Clean all .exe and .o files"
	@echo "  make <day_number>   - Create a new day folder with input.txt and dayXX.cpp"
	@echo "  make dayXX          - Compile and run dayXX.cpp"
	@echo "Example:"
	@echo "  make 02             - Create day02 with template files"
	@echo "  make day02          - Compile and execute day02/day02.cpp"

# Clean .exe and .o files in all day directories
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@find $(DAYS) -type f \( -name "*.exe" -o -name "*.o" \) -exec rm -f {} +
	@echo "Cleanup complete!"

# Rule to create a new day directory with template files
.PHONY: %
%:
	@if echo $@ | grep -Eq '^[0-9]{2}$$'; then \
		day_dir="day$@"; \
		day_file="day$@.cpp"; \
		if [ ! -d $$day_dir ]; then \
			mkdir -p $$day_dir; \
			echo "Creating $$day_dir/"; \
		fi; \
		if [ ! -f $$day_dir/input.txt ]; then \
			touch $$day_dir/input.txt; \
			echo "Creating $$day_dir/input.txt"; \
		fi; \
		if [ ! -f $$day_dir/$$day_file ]; then \
			echo "#include <iostream>" > $$day_dir/$$day_file; \
			echo "int main() {" >> $$day_dir/$$day_file; \
			echo "    std::cout << \"Day$@ solution\" << std::endl;" >> $$day_dir/$$day_file; \
			echo "    return 0;" >> $$day_dir/$$day_file; \
			echo "}" >> $$day_dir/$$day_file; \
			echo "Creating $$day_dir/$$day_file"; \
		fi; \
	else \
		echo "Invalid target. Use a two-digit day number (e.g., 02)."; \
	fi

# Rule to compile and run dayXX.cpp
.PHONY: day%
day%:
	@if echo $@ | grep -Eq '^day[0-9]{2}$$'; then \
		day_dir="$@"; \
		day_file="$$day_dir/$@.cpp"; \
		if [ -f $$day_file ]; then \
			echo "Compiling $$day_file..."; \
			g++ -o $$day_dir/$@ $$day_file && echo "Running $$day_dir/$@..." && $$day_dir/$@; \
		else \
			echo "Error: $$day_file not found."; \
		fi; \
	else \
		echo "Invalid target. Use dayXX format (e.g., day02)."; \
	fi
