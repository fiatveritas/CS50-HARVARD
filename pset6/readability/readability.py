#!/usr/bin/python
from cs50 import get_string
import string


def run(text):  # this function runs the program
    """this function runs the program, input is string (text)"""
    letter_count = 0  # this is the number of letter in a string
    word_count = 0  # this is the word count in a string
    sentence_count = 0  # this is the sentence in a string
    grade_level = 0  # this is the reading grade level

    letter_count = count_letter(text)
    word_count = count_word(text)
    sentence_count = count_sentences(text)
    grade_level = int(coleman_liau(letter_count, word_count, sentence_count))
    output(grade_level)
    return


def output(grade_level):
    """this outputs the grade leve, input is a positive int"""
    if (grade_level < 1):
        print(f"Before Grade 1\n", end="")
        return
    elif (grade_level >= 2 and grade_level <= 15):
        print(f"Grade %i\n" % grade_level, end="")
        return
    else:
        print(f"Grade 16+\n", end="")
        return


def count_letter(text):  # this function counts the letters (ignores non-space, ignores puctuation, counts lower case and upper case)
    """this function counts the letter in the function, text is a string"""
    counter = 0
    size = len(text)

    for j in range(size):
        if ((not text[j].isspace()) and text[j].isalpha() and (text[j] not in string.punctuation)):
            counter += 1
    return counter


def count_word(text):  # this function counts the number of words
    """this function counts the number of words, text is a string"""
    count = 0
    size = len(text)
    if (size == 0):
        return count
    for j in text.split():
        count += 1
    # count += 1  # increase by one more because counter starts at zero at the first word, need this!
    return count


def count_sentences(text):  # this function counts the number of sentence, it counts the number periods
    """this function counts the number of sentences, text is a string"""
    count = 0
    size = len(text)
    for j in range(size):
        if (text[j] == '.' or text[j] == '?' or text[j] == '!'):
            count += 1
    return count


def coleman_liau(letter_count, word_count, sentence_count):
    """this function computers the reading level, inputs are integers"""
    index = 0  # where L is the average number of letters per 100 words in the text,
# and S is the average number of sentences per 100 words in the text.
    L = -1.0
    S = -1.0

    L = (100.0 / float(word_count)) * letter_count  # printf("\tL: %f\n", L)
    S = (100.0 / float(word_count)) * sentence_count  # printf("\tS: %f\n", S)
    index = ((0.0588 * L) - (0.296 * S) - 15.8)  # printf("\tGrade: %f\n", index)
    index = round(index)  # printf("\tGrade: %f\n", index)
    return index


#  run the program
if __name__ == "__main__":
    text = get_string("Text: ")
    run(text)

# readability "One fish. Two fish. Red fish. Blue fish."
# (Before Grade 1)
# readability "Would you like them here or there? I would not like them here or there. I would not like them anywhere."
# (Grade 2)
# readability "Congratulations! Today is your day. You're off to Great Places! You're off and away!"
# (Grade 3)
# readability "Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard."
# (Grade 5)
# readability "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since."
# (Grade 7)
# readability "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, \"and what is the use of a book,\" thought Alice \"without pictures or conversation?\""
# (Grade 8)
# readability "When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh."
# (Grade 8)
# readability "There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy."
# (Grade 9)
# readability "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him."
# (Grade 10)
# readability "A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains."
# (Grade 16+)