#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void run(int argc, char *argv[]); //this function runs the program
void output(int); //outputs reading level to user
int count_letter(char *argv[]); //this function counts the number of letters in a string
int count_word(char *argv[]); //this function counts the number of words in a string
int count_sentences(char *argv[]); //this function counts the number of sentences in a string
float coleman_liau(int, int, int); //this function computes the reading level

int main(void)
{
    string stuff = get_string("Text: ");
    int const argc = 2;
    int size = strlen(stuff);
    char *argv[argc];
    argv[1] = stuff;

    //char **a[2][] = {{argc + '0'} ,{stuff}};

    if (argc == 2)
    {
        //printf("inside main(): \n");
        run(argc, argv);
        return 0;
    }
    else if (argc > 2)
    {
        printf("too many arguments!\n");
        return 1;
    }
    else
    {
        printf("not enough argumnets\n");
        return 1;
    }
}

void run(int argc, char *argv[]) //this function runs the program
{
    int letter_count = 0; //this is the number of letter in a string
    int word_count = 0; //this is the word count in a string
    int sentence_count = 0; //this is the sentence in a string
    int grade_level = 0; //this is the reading grade level

    string text = argv[1];
    letter_count = count_letter(argv);
    word_count = count_word(argv);
    sentence_count = count_sentences(argv);
    grade_level = (int)coleman_liau(letter_count, word_count, sentence_count);
    output(grade_level);
    return;

}

void output(int grade_level)
{
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
        return;
    }
    else if (grade_level >= 2 && grade_level <= 15)
    {
        printf("Grade %i\n", grade_level);
        return;
    }
    else
    {
        printf("Grade 16+\n");
        return;
    }
}

int count_letter(char
                 *argv[]) //this function counts the letters (ignores non-space, ignores puctuation, counts lower case and upper case)
{
    int counter = 0;
    int size = strlen(argv[1]);

    for (int j = 0; j < size; j++)
    {
        if ((isspace(argv[1][j]) == 0) && (isalpha(argv[1][j]) != 0) && (ispunct(argv[1][j]) == 0))
        {
            counter++;
        }
    }
    return counter;
}

int count_word(char *argv[]) //this function counts the number of words
{
    int count = 0;
    int size = strlen(argv[1]);
    if (size == 0)
    {
        return count;
    }
    for (int j = 0; j < size; j++)
    {
        if (isspace(argv[1][j]) != 0) //looks for non-whitespace
        {
            count++;
        }
    }
    count++; //increase by one more because counter starts at zero at the first word, need this!
    return count;
}

int count_sentences(char *argv[]) //this function counts the number of sentence, it counts the number periods
{
    int count = 0;
    int size = strlen(argv[1]);
    for (int j = 0; j < size; j++)
    {
        if (argv[1][j] == '.' || argv[1][j] == '?' || argv[1][j] == '!')
        {
            count++;
        }
    }
    return count;
}

float coleman_liau(int letter_count, int word_count, int sentence_count)
{
    float index = 0; /*where L is the average number of letters per 100 words in the text,
                        and S is the average number of sentences per 100 words in the text.*/
    float L = -1.0;
    float S = -1.0;

    L = (100.0 / (float)word_count) * letter_count; //printf("\tL: %f\n", L);
    S = (100.0 / (float)word_count) * sentence_count; //printf("\tS: %f\n", S);
    index = ((0.0588 * L) - (0.296 * S) - 15.8); //printf("\tGrade: %f\n", index);
    index = roundf(index); //printf("\tGrade: %f\n", index);
    return index;
}


//check50 cs50/problems/2020/x/readability
//style50 readability.c
//debug 50 readability
//submit50 cs50/problems/2020/x/readability