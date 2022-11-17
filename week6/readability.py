# Import get_string from CS50
from cs50 import get_string

# Get text from user
text = get_string("Text: ")

# Count numbers of letters, words, sentences
# Number of letters
letters = 0
for i in range(len(text)):
    if text[i].isalpha():
        letters += 1

# Number of words indicated by number of spaces
words = 1 + text.count(" ")

# Number of sentences indicated by punctuation ".?!"
sentences = text.count(".") + text.count("?") + text.count("!")

# Calculate index
l = letters / words * 100.0
s = sentences / words * 100.0
index = 0.0588 * l - 0.296 * s - 15.8

# Calculate grade
if index < 1:
    print("Before Grade 1")
elif round(index) >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
