"""Implement a program that stimulates a sports tournament
    as well as give estimate to how likely it is that
            any given team wins the tournament"""

import csv
import sys
import random

# Set a number of simulations to run
N = 1000


def main():

    # Make sure the program accepts only one command - line argument
    if len(sys.argv) != 2:

        # If given the incorrect number of CLA's, exit the program
        sys.exit("Usage: python tournament.py FILENAME")

    """Define an empty list that will be populated with
            teams once data is read into memory"""
    teams = []

    # Store the name of a given team taken from the CSV file inside a variable
    filename = sys.argv[1]

    # Open up the file
    with open(filename) as file:

        # Read teams into memory from the file
        reader = csv.DictReader(file)

        """Loop through each team in the file so that you have your
                elimination bracket to run a tournament"""
        for team in reader:

            # Type cast the rating so it is not treated as a string
            team["rating"] = int(team["rating"])

            # Populate the list of teams after reading each of the team into memory
            teams.append(team)

    """Define an empty dictionary wherein each team will (key) be associated
            with a number of times this particular has won (value)
                            once populated"""
    counts = {}

    # Simulate N tournaments, keeping track of how many times a particular team has won
    for i in range(N):

        # Store the result of a simulation inside of a variable
        winner = simulate_tournament(teams)

        # If the team has won before, add to the total number of their wins
        if winner in counts:
            counts[winner] += 1

        # If the team in question has never won before add it to the dictionary
        else:
            counts[winner] = 1

        """ Print each team' chances of winning, according to simulation,
                        putting them in descending order"""
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team} has {counts[team] * 100 / N:.1f}% chance of winning")

"""Implement a function that accepts two teams as inputs
            and simulates a game between them"""
def simulate_game(team1, team2):

    # Store the value of each team' rating in a corresponding variable
    rating1 = team1["rating"]
    rating2 = team2["rating"]

    """Basing off of teams'current rating, calculate the probability of them
                    playing against each other"""
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))

    """Once done, return a random floating point number
            determining what teams are playing"""
    return random.random() < probability

"""Simulate a round"""
def simulate_round(teams):

    """Create an empty list that will be populated with teams
     that has won a given round, once that round is over"""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):

        # If the first team wins a round add it to the list
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])

        # Otherwise, the second is the one that goes into the list
        else:
            winners.append(teams[i + 1])

    # Return a list of winning teams
    return winners

# Simulate a tournament
def simulate_tournament(teams):

    """Make sure the simulation keeps on going for as long as
    there are at least two teams to play against each another"""
    while len(teams) > 1:
        teams = simulate_round(teams)

    # Return name of winning team.
    return teams[0]["team"]


if __name__ == "__main__":
    main()