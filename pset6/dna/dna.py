#!/usr/bin/python
import csv
import re
import sys


def get_patterns(people):
    """The argument passed is the file
    this returns a list of the patterns
    to look for."""
    counter = 0
    queries = []
    for i in people:
        for j in i:
            queries.append(j)
        break
    queries.pop(0)
    return queries


def create_suspects(people):
    holder = []
    for i in people:
        holder.append(str(i).rstrip("\n"))
    return holder


def create_counter(patterns):
    """This creates the counts for the longest
    run of a DNA pattern. patterns is list type"""
    counts = {}
    for i in patterns:
        counts[i] = 0
    return counts


def create_mystery(enigma):
    """This creates the string that will be explored
    for the longest runs for each STR"""
    mystery = ""
    for i in enigma:
        for j in i:
            mystery += j
    return mystery


def run_location(patterns):
    """this creates a dictionary of
    a list that has where the occurrences
    happen. patterns is a list of strings"""
    index = {}
    for i in patterns:
        index[i] = []
    return index


def find_location(runs, patterns, whosisit):
    for i in patterns:
        for match in re.finditer(i, whosisit):
            s = match.start()
            e = match.end()
            runs[i].append((s, e))
    return runs


def populate_count(p_count, patterns, runs):
    """this populates the longest run for each pattern.
    p_count is a dictionary, patterns is a list of strings
    runs is list containing the locations of the occurrences"""
    longest = 0  # counts the passes below
    dummy = -1  # tracks what the ending element is
    for i in patterns:
        for j in runs[i]:
            if longest == 0:
                dummy = j[1]
                longest += 1
                continue
            elif j[0] == dummy:
                dummy = j[1]
                longest += 1
                continue
            elif j[0] != dummy:
                if longest > p_count[i]:
                    p_count[i] = longest
                dummy = j[1]
                longest = 1
                continue
        if longest > p_count[i]:
            p_count[i] = longest

        longest = 0
    return p_count


def query(patterns, p_count):
    find = ""
    for i in patterns:
        find += str(p_count[i])
        find += ","
    if find[-1] == ",":
        find = find[:len(find)-1]
    return find


if __name__ == "__main__":
    # python dna.py databases/large.csv sequences/5.txt
    if len(sys.argv) == 1:
        print("not enough inputs")
    elif len(sys.argv) == 2:
        print("not enough inputs")
    elif len(sys.argv) == 3:
        file = sys.argv[1]  # name of the database of people's DNA
        file_2 = sys.argv[2]  # sequence to be identified
        #  file = "databases/large.csv"  # name of the database of people's DNA
        #  file_2 = "sequences/5.txt"  # sequence to be identified

        with open(file) as people:
            reader = csv.reader(people)
            patterns = get_patterns(reader)
            suspects = create_suspects(people)
            p_count = create_counter(patterns)  # initialize the dictionary that has the counts

        with open(file_2) as data:
            reader_2 = csv.reader(data)
            whosisit = create_mystery(reader_2)
        runs = run_location(patterns)
        runs = find_location(runs, patterns, whosisit)
        p_count = populate_count(p_count, patterns, runs)
        find = query(patterns, p_count)
        flag = True
        for i in suspects:
            for match in re.finditer(find, i):
                if match is not None:
                    print(i.split(',')[0])
                    flag = False
                    break
        if flag:
            print("No match")
    else:
        print("error")