"""Implement a program that calculates the minimum number of coins required to give a user change"""

# Initialize a variable to keep track of how many coins have been used so far
track = 0

"""Run the program for as long as the condition within the loop evaluates to True
            breaking out of it once the Boolean value puts on a False"""
while True:

    # Prompt users with input
    change = int(input("Change due: "))

    if change > 0:
        break

# Rounding prevents the change from having a decimal part
cents = round(change * 100)

# Determine how many quarters are to be given
while cents >= 25:

    """Keep on handing out quarters for as long as
        the change due makes it reasonable to do so,
    thus ensuring the minimum number of coins may be given back"""
    cents = cents - 25

    """Once handed, increment a value of the coins' number to give,
            assigning final value to a corresponding variable"""
    track += 1

# Determine how many dimes are to be given
while cents >= 10:

    """Keep on handing out dimes for as long as
        the change due makes it reasonable to do so,
    thus ensuring the minimum number of coins may be given back"""
    cents = cents - 10

    """Once handed, increment a value of coins' number to give,
            assigning final value to a corresponding variable"""
    track += 1

# Determine how many nickels are to be given
while cents >= 5:

    """Keep on handing out nickels for as long as
        the change due makes it reasonable to do so,
    thus ensuring the minimum number of coins may be given back"""
    cents = cents - 5

    """Once handed, increment a value of coins' number to give,
            assigning final value to a corresponding variable"""
    track += 1


# Determine how many pennies are to be given
while cents >= 1:

    """Keep on handing out pennies for as long as
        the change due makes it reasonable to do so,
    thus ensuring the minimum number of coins may be given back"""
    cents = cents - 1

    """Once handed, increment the value of coins' number to give,
            assigning final value to a corresponding variable"""
    track += 1

# Print the total number of coins to be handed 
print(track)