# Implement a program that identifies to whom a sequence of DNA belongs
import csv
import sys
from csv import reader, DictReader
from sys import argv, exit


def main():

    """Make sure that users provide correct number of CLA's
        such that our program operates as intended"""
    if len(sys.argv) != 3:

        # Render an error if user has failed to provide the correct number of CLA's
        print("Type the correct number of CLA")
        sys.exit(1)

    """Create an empty list that represents the database comprised of a given person' name
            and the number of times a particular STR  is found in that person' DNA"""
    database = []

    # Open up a file for reading only
    with open(sys.argv[1], 'r') as csvfile:

        """Map the information in each row to a dictionary
                whose keys are given by the CSV files"""
        reader = csv.DictReader(csvfile)

        # Add some data to the list
        for row in reader:
            database.append(row)

    # Opens a file containing DNA sequenses for reading only
    with open(sys.argv[2], 'r') as textfile:
        # Return a list of strings
        sequence = textfile.read()

    """Create a list of STR's to be examined ensuring
    disregard for the first colums (the one that has names)"""
    subsequences = list(database[0].keys())[1:]

    """Create an empty dictionary with STR as key mapped to the number
        telling how many times a given STR has been found as value"""
    matches = {}

    """For each position in the sequence keep on looking
    for successive substrings until the STR repeats no longer"""
    for subsequence in subsequences:

        # Identify the maximum number of times that a particular STR repeats
        matches[subsequence] = longest_match(sequence, subsequence)

    # Check database for matching STR's
    for human in database:

        """Make sure the initial value of matches set to zero,
        since that's exactly how many people have been identified yet"""
        match = 0

        # Iterate over each row in the CSV files
        for subsequence in subsequences:

            # If certain STR has been detected increment the value of matches by one
            if int(human[subsequence]) == matches[subsequence]:
                match += 1

        # If all STR's coincide, print out person's name
        if match == len(subsequences):
            print(human["name"])
            return

    # Otherwise, no match
    print("No match")
    return

"""Returns the length of longest run of subsequence in sequence."""
def longest_match(sequence, subsequence):

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Iterate over the entirety of the sequence
    for i in range(sequence_length):

        """Initialize a counter variable that tracks how many
        times a given STR appears in the DNA sequence"""
        count = 0

        """Check for a subsequence match in a "substring" within sequence
            If match, move substring to a next potential match in sequence
     continue moving substring and checking for matches until out of consecutive matches"""
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # Increment the value of an STR if there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring, end the program
            else:
                break

        # Update the total of most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each spot in the sequence, return longest run found
    return longest_run


main()