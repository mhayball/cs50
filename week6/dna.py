import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as data_file:
        reader = csv.DictReader(data_file)
        for row in reader:
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], "r")
    sequence = sequence_file.read()
    sequence_file.close()

    # TODO: Find longest match of each STR in DNA sequence
    # Set up STRs - from data
    strs = []
    for key in data[0]:
        if key != "name":
            count = longest_match(sequence, key)
            strs.append({"str": key, "count": count})

    # TODO: Check database for matching profiles
    # Iterate through people
    for person in data:
        # Set person_check to 1 - will reset to 0 if not an exact match on any str
        person_check = 1

        # Iterate through strs - check counts of person vs sequence
        for str in strs:
            count_person = int(person[str["str"]])
            count_sequence = int(str["count"])

            if count_person != count_sequence:
                # No match, set person_check to 0 and break for next person
                person_check = 0
                break

        # If person_check == 1, then must match all strs
        if person_check == 1:
            print(person["name"])
            break

    # If person_check remains 0, then there have been no matches
    if person_check == 0:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
