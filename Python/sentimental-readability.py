"""Implement a program that calculates the approximate
        grade level needed to comprehend a given text"""

# Prompt the user with text as input
text = input("text: ")

# Assign the length value of the provided input to a corresponding variable
texlen = len(text)

"""Initialize three counter variables that track how many
    letters, words and sentences there are in the text"""
letters = 0
words = 1
sentenses = 0

# Loop through the entirety of a given text
for i in range(texlen):

    # Make sure the program deals only with alphabetical characters
    if (text[i].isalpha()):

        """Once detected, increment a value of letters in the text by one,
                assigning final value to a corresponding variable"""
        letters += 1

    """Count the total number of whitespaces in the text,
            so you can figure out how many words are in the text"""
    if (text[i].isspace()):

        """Once detected, increment a value of words in the text by one,
                assigning final value to a corresponding variable"""
        words += 1

    """Identify each and every instance of terminating punctuation marks
                in order to get the total number of sentences"""
    if (text[i] == '.' or text[i] == '!' or text[i] == '?'):

        """Once detected, increment a value of words in the text by one,
                assigning final value to a corresponding variable"""
        sentenses += 1

# Estimate an approximate grade level via the Coleman-Liau readability test equation
gauging = (0.0588 * letters / words * 100) - (0.296 * sentenses / words * 100) - 15.8

# Calculate and round acquired index
index = round(gauging)

# Print out a grade level based upon the Coleman-Liau readability test' result
if index < 1:
    print("Before Grade 1")

elif index > 16:
    print("Grade 16+")
    
else:
    print(f"Grade {index}")