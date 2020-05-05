#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

void run(int argc, char *argv[]);
bool check_sum(char *);
bool master_card(char *);
bool visa(char *);
bool american(char *);
bool correct_length(bool, bool, bool, char *);
int digits(int);
void final_output(bool, bool, bool, bool, bool);

int main(void)
{
    long dummy = get_long("Number: "); //get card number from user

    int counter = 0;
    long holder = dummy;

    while (holder != 0) //count the length of the card, number of digits in the card
    {
        holder /= 10;
        counter++;
    }

    char *argv[counter + 1];
    holder = dummy;
    char local[counter + 1];

    int x = -1;
    char letter = '\n'; //holder variables

    for (int j = counter - 1; j > -1; j--) //this makes a character array out of the long passed by the user
    {
        x = holder % 10;
        letter = x + '0';
        local[j] = letter;
        holder /= 10;
    }
    local[counter] = '\0';
    *argv = &local[0];

    run(2, argv); //hardcoded 2, arguments from main allow more than two for testing
    //the code below works for args passed into main,
    /*
    if(argc > 1){
        run(argc, argv);
    }
    else{
    printf("no inputs provided\n");
    }

    printf( "\n" );
    */
    return 0;

}

void run(int argc, char *argv[])
{
    bool dummy = false;
    bool is_valid = false;
    bool is_mastercard = false;
    bool length = false;
    bool is_visa = false;
    bool passes = false;
    bool is_american = false;

    is_mastercard = master_card(*argv);
    is_visa = visa(*argv);
    is_american = american(*argv);
    length = correct_length(is_mastercard, is_visa, is_american, *argv);
    is_valid = (is_mastercard || is_visa || is_american) && length;
    if (is_valid)
    {
        passes = check_sum(*argv);
        final_output(is_mastercard, is_visa, is_american, length, passes);
        return;
    }
    else
    {
        printf("INVALID\n");
        return;
    }
    return;




    //the code below works for arguments passed by the main function
    /*
    for( int j= 1; j< argc; j++ ){
        printf("iteration: %i, %s\n", j, argv[j]);
        is_mastercard= master_card( argv[j] );
        is_visa= visa( argv[j] );
        is_american= american( argv[j] );
        length= correct_length(is_mastercard, is_visa, is_american, argv[j]);
        is_valid= is_mastercard || is_visa || is_american;
        if( is_valid ){
            //printf("running check_sum: ");
            passes= check_sum( argv[j] );
            //printf("passes: %d\n", passes);

        }
        final_output( is_mastercard, is_visa, is_american, length, passes);
    }
    */
}

bool check_sum(char *num)
{
    //printf(" inside check_sum: %s\n", num);
    int counter = 0;
    int temp = -1;
    int dummy = 0;
    int sum = 0;
    while (num[counter] != '\0')
    {
        counter++;
    }
    temp = counter - 2;
    while (temp >= 0) //multiply every other digits starting from second to last digit counting down for non-zero
    {
        dummy = (num[temp] - '0') * 2;
        sum += digits(dummy);
        temp = temp - 2;
    }
    temp = counter - 1;
    while (temp >= 0) //second part of the creditcard algorithm add to sum non-multiplied digits
    {
        dummy = num[temp] - '0';
        sum += dummy;
        temp = temp - 2;
    }

    if (sum % 10 == 0)
    {
        return true;
    }
    return false;
}

bool master_card(char *num) //checks if the card is a mastercard
{
    int const SIZE = 5;
    if (num[0] - '0' != 5)
    {
        return false;
    }
    else
    {
        for (int j = 1; j <= SIZE; j++) //MasterCard are 51, 52, 53, 54, 55 per spec
        {
            if (num[1] - '0' == j)
            {
                return true;
            }
        }
    }
    return false;
}

bool visa(char *num) //checks if the card is a visa
{
    if ((num[0] - '0') == 4) //VISA cards start with 4
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool american(char *num) //checks if american card starts with either 34 or 37
{
    if ((num[0] - '0'  == 3 && num[1] - '0' == 4) || (num[0] - '0'  == 3
            && num[1] - '0'  == 7)) //possible American Express are 34 or 37
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool correct_length(bool is_mastercard, bool is_visa, bool is_american,
                    char *num) //this checks if each type of card has the correct length
{
    int counter = 0;
    int mastercard = 16; //printf(" mastercard: %d", is_mastercard);
    int american = 15;
    int visa1 = 13; //printf(" american: %d", is_american);
    int visa2 = 16; //printf(" visa %d", is_visa);
    while (num[counter] != '\0')
    {
        counter++;
    } //printf( " num of digits: %i\n", counter );
    if ((counter == mastercard) && is_mastercard) //check that each card has the correct length for its network
    {
        return true;
    }
    else if ((counter == american) && is_american)
    {
        return true;

    }
    else if ((counter == visa1) && is_visa)
    {
        return true;
    }
    else if ((counter == visa2) && is_visa)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int digits(int num) //this adds the digits
{
    int digits = 0;
    while (num != 0)
    {
        digits += num % 10;
        num /= 10;
    }
    return digits;
}

void final_output(bool is_mastercard, bool is_visa, bool is_american, bool length, bool is_valid) //this displays the final output
{
    if (is_mastercard && length && is_valid) //checks all criteria each credit card
    {
        printf("MASTERCARD\n");
        return;

    }
    else if (is_american && length && is_valid)
    {
        printf("AMEX\n");
        return;
    }
    else if (is_visa && length && is_valid)
    {
        printf("VISA\n");
        return;

    }
    else
    {
        printf("INVALID\n");
        return;
    }
}

//american express 15 digits
//visa 13 digits or 16 digits
//master card 16 digits