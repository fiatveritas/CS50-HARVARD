#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void run(int argc, char *argv[]);  //this runs all
bool check_length(char *message[]);  //this checks for the length of the key
bool check_letter(char *message[]);  //this checks all that only letters are in the key
bool check_repeated(int, char *messege[]);  //this checks for repeated key letters
char cipher(char, char *message[]);  //this runs the cipher on the letter
char lower_letter(char, char *message[]);  //gets called if letter is lower
char upper_letter(char, char *message[]);  //gets called if letter is upper

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        bool correct_length = check_length(argv);  //check if the letter mapping is correct
        bool correct_letters = check_letter(argv); //check if the letter mapping are letters
        bool repeated_letter = check_repeated(26, argv); //checks for repitition in the key

        if (!correct_length) //check if the user passed in correct # of key
        {
            printf("not long enough!\n");
            return 1;
        }
        else if (correct_letters) //check if all are letter
        {
            printf("non-letters in key!\n");
            return 1;
        }
        else if (repeated_letter) //check for repeated letters
        {
            printf("repeated letters in key!\n");
            return 1;
        }
        run(argc, argv);  //run if all the tests pass
    }
    else if (argc > 2) //error if the user passed in more than two inputs at terminal
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else  //prompt the user how to pass function at terminal
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    return 0;
}

void run(int argc, char *argv[])  //run the function
{
    string message = get_string("plaintext: ");
    int n = strlen(message);
    char *encrypted[n + 1]; //leave space for '\0' at the end of the array
    char final[n + 1];
    for (int j = 0; j < n; j++)  //run cipher on each character of the message
    {
        final[j] = cipher(message[j], argv);
    }
    final[n] = '\0'; //mark the end of the array after creation
    *encrypted = &final[0];  //put the encrypted message into string
    printf("ciphertext: %s\n", *encrypted);
}

bool check_length(char *message[])  //cheks for the correct number of key letters
{
    int const SIZE = 26;  //size of key
    int counter = 0;

    while (message[1][counter] != '\0')
    {
        counter++;
    }

    if (counter == SIZE)
    {
        return true;
    }

    return false;
}

bool check_letter(char *message[])  //checks if all the inputs are letters in the key
{
    for (int j = 0; j < 26; j++)
    {
        if (!((message[1][j] >= 'a' && message[1][j] <= 'z') || (message[1][j] >= 'A' && message[1][j] <= 'Z')))
        {
            return true;  //this means that the function found a non-letter
        }
    }
    return false;
}

bool check_repeated(int size, char *messege[]) //checks for repeated letters in the key
{
    char temp[size];
    for (int j = 0; j < size; j++)
    {
        if (messege[1][j] >= 'A' && messege[1][j] <= 'Z') //converts to lower
        {
            temp[j] = messege[1][j] + 32;
        }
        else
        {
            temp[j] = messege[1][j];
        }
    }




    int counter = 0;
    for (int j = 0; j < size; j++)  //checks for repition based off all lower
    {
        counter = j + 1;
        if (counter == size)
        {
            break;
        }
        while (counter < size)
        {
            if (temp[counter] == temp[j])
            {
                return true;
            }
            counter++;
        }
    }
    return false;
}

char cipher(char x, char *message[])  //encrypts the words
{
    if (x >= 'a' && x <= 'z')
    {
        x = lower_letter(x, message);
    }
    else if (x >= 'A' && x <= 'Z')
    {
        x = upper_letter(x, message);
    }
    return x;
}

char lower_letter(char x, char *message[])  //outputs the returns lower ciphered char
{
    int const SIZE = 27;
    char holder[SIZE];  //sets up array for lower
    for (int j = 0; j < SIZE - 1; j++)
    {
        if (message[1][j] >= 'A' && message[1][j] <= 'Z')
        {
            holder[j] = message[1][j] + 32;
        }
        else
        {
            holder[j] = message[1][j];
        }
    }

    holder[26] = '\0';

    int counter = 0;
    char dummy = '\t';
    for (char y = 'a'; y <= 'z'; y++)  //looks for the lower by indicies matches encrypted value
    {
        if (x == y)
        {
            dummy = holder[counter];
            return dummy;
        }
        counter++;
    }

    return x;
}

char upper_letter(char x, char *message[])  //similar to function above, return ciphered upper
{
    int const SIZE = 27;
    char holder[SIZE];
    for (int j = 0; j < SIZE - 1; j++) //make array of all upper
    {
        if (message[1][j] >= 'a' && message[1][j] <= 'z')
        {
            holder[j] = message[1][j] - 32;
        }
        else
        {
            holder[j] = message[1][j];
        }
    }

    holder[26] = '\0';

    int counter = 0;
    char dummy = '\t';
    for (char y = 'A'; y <= 'Z'; y++)  //returns the upper ciphered char
    {
        if (x == y)
        {
            dummy = holder[counter];
            return dummy;
        }
        counter++;
    }

    return x;
}


//debub50 substitution ./substitution
//check50 cs50/problems/2020/x/substitution
//style50 substitution.c
//submit50 cs50/problems/2020/x/substitution