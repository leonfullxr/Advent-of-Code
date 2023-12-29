
#!/bin/bash

# Navigate to the AOC-2023 directory
cd "$(dirname "$0")"

# Find all input.txt files in DayXX directories and append them to .gitignore
find . -name 'input.txt' | sed 's|^\./||' > .gitignore

