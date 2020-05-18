#!/usr/bin/python
from cs50 import get_int
num = get_int("Height: ")

# the loop below checks for user input
# the input must be between 1 and 8
while (not(int(num) >= 1 and int(num) <= 8)):
    num = get_int("Height: ")
# the loop below executes the "mario"
# code per specification
for i in range(1, num + 1):
    print(f" "*(num - i), end="")
    print(f"#"*i, end="")
    print("  ", end="")
    print(f"#"*i, end="")
    print("\n", end="")
