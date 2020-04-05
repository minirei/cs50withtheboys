from sys import argv
import sys
import csv
import re

if len(argv) != 3:
    print("Usage: python dna.py database.csv sequence.txt")
    sys.exit(0)

# Open csv file
database = open(argv[1])
reader_database = csv.reader(database, delimiter=",")

# Open test sequence
test_seq = open(argv[2])
reader_seq = test_seq.read()

# Create dictionary for test sequence. key = [sample STR]. value = [no. of STRs in test_seq]
test_dict = {}
fieldnames = next(reader_database)
for key in fieldnames:
    test_dict[key] = 0

# Find and add values to dictionary
for key in test_dict:
    total_repeats = re.findall("(?:" + key + ")+", reader_seq)
    if len(total_repeats) > 0:
        test_dict[key] = len(max(total_repeats)) / len(key)

# Iterate through each person in database
for row in reader_database:
    # Iterate through individual's STRs
    for i in range(1, len(row)):
        Bool = False
        # Compares individual's STRs and sample's STRs
        if int(row[i]) == test_dict[fieldnames[i]]:
            Bool = True
        else:
            break
    
    if Bool == True:
        print(row[0])
        break
    
if Bool == False:
    print("No Match")
