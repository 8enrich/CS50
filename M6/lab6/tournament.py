# Simulate a sports tournament

import csv
from sys import exit, argv
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(argv) != 2:
        exit("Usage: python3 tournament.py FILENAME")
    if argv[1][len(argv[1]) - 4:len(argv[1])] != ".csv":
        exit("The file needs to be a .csv")

    teams = []
    try:
        with open(argv[1], "r") as file:
            for line in csv.DictReader(file):
                line["rating"] = int(line["rating"])
                teams.append(line)
    except:
        exit(f"{argv[1]} could not be found")

    counts = {}
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner not in counts:
            counts[winner] = 0
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    winner = simulate_round(teams)
    if len(winner) == 1:
        return winner[0]["team"]
    else:
        return simulate_tournament(winner)

if __name__ == "__main__":
    main()
