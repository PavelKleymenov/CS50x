# Implement a program that prints out a double half-pyramid of a specified height


"""Run the program for as long as the condition within the loop evaluates to True
            breaking out of it once the Boolean value puts on a False"""
while True:

    # Prompt the user with height
    height = int(input("height: "))

    # Make sure that pyramid's height is within the range of 1 through 8, both ends included
    if height >= 1 and height <= 8:
        break

# Loop through each row of the left-aligned pyramid
for row in range(height):

    # Loop through each space of the left-aligned pyramid
    for space in range(height - row - 1, 0, -1):
        print(" ", end="")

    # Loop through each column of left-aligned pyramid
    for column in range(row + 1):
        print("#", end="")

    # Print a gap between the pyramids
    print("  ", end="")

    # Loop through each column of the right-aligned pyramid
    for column in range(row + 1):
        print("#", end="")
        
    # Move to the next row
    print("\n", end="")