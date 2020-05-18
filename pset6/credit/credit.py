#!/usr/bin/python
def check_sum(num):
    # num is a string of numbers
    # print(" inside check_sum: %s\n" %num, end="");
    counter = 0
    temp = -1
    dummy = 0
    total = 0
    temp = len(num)
    temp = counter - 2
    while (temp >= 0):  # multiply every other digits starting from second to last digit counting down for non-zero
        dummy = int(num[temp]) * 2
        total += dummy
        temp = temp - 2
    temp = counter - 1
    while (temp >= 0):  # second part of the creditcard algorithm add to sum non-multiplied digits
        dummy = int(num[temp])
        total += dummy
        temp = temp - 2

    if (total % 10 == 0):
        return True
    return False


def master_card(num):  # checks if the card is a mastercard
    """this function checks if a creditcard
    is a master card."""
    SIZE = 5
    if (int(num[0]) != 5):
        return False
    else:
        for j in range(1, SIZE + 1):  # MasterCard are 51, 52, 53, 54, 55 per spec
            if (int(num[1]) == j):
                return True
    return False


def visa(num):  # checks if the card is a visa
    """"this checks if a card is a visa
    this checks if the first digit is 4"""
    if (int(num[0]) == 4):  # VISA cards start with 4
        return True
    else:
        return False


def american(num):  # checks if american card starts with either 34 or 37
    """this function checks the first two digits of the
    credit card and determines if it is an american express"""
    if ((int(num[0]) == 3 and int(num[1]) == 4) or (int(num[0]) == 3 and int(num[1]) == 7)):  # possible American Express are 34 or 37
        return True
    else:
        return False


def correct_length(is_mastercard, is_visa, is_american, num):  # this checks if each type of card has the correct length
    """this return whether the card has the correct
    length given the type of card it is"""
    counter = 0
    mastercard = 16  # printf(" mastercard: %d", is_mastercard);
    american = 15
    visa1 = 13  # print(f" american: %d" %is_american);
    visa2 = 16  # print(f" visa %d" %is_visa)

    counter = len(num)
    #print(f" num of digits: %i\n" %counter )
    if ((counter == mastercard) and is_mastercard):  # check that each card has the correct length for its network
        return True
    elif ((counter == american) and is_american):
        return True
    elif ((counter == visa1) and is_visa):
        return True
    elif ((counter == visa2) and is_visa):
        return True
    else:
        return False


def final_output(is_mastercard, is_visa, is_american, length, is_valid):  # this displays the final output
    """this outputs the final results give the
    credit card number"""
    if (is_mastercard and length and is_valid):  # checks all criteria each credit card
        print(f"MASTERCARD\n", end="")
        return
    elif (is_american and length and is_valid):
        print(f"AMEX\n", end="")
        return
    elif (is_visa and length and is_valid):
        print(f"VISA\n", end="")
        return
    else:
        print(f"INVALID\n", end="")
        return


def run(num):
    """"this function runs the program"""
    dummy = False
    is_valid = False
    is_mastercard = False
    length = False
    is_visa = False
    passes = False
    is_american = False

    is_mastercard = master_card(num)
    is_visa = visa(num)
    is_american = american(num)
    length = correct_length(is_mastercard, is_visa, is_american, num)
    is_valid = (is_mastercard or is_visa or is_american) and length
    if (is_valid):
        passes = check_sum(num)
        final_output(is_mastercard, is_visa, is_american, length, passes)
        return
    else:
        print(f"INVALID\n", end="")
        return
    return


if __name__ == "__main__":
    dummy = input("Number: ")
    run(dummy)


# american express 15 digits, start with  34 or 37
# visa 13 digits or 16 digits, start with 4
# master card 16 digits, start with 51, 52, 53, 54, 55

# Algorithm
# multiply every other digits starting from second to last digit counting down for non-zero
# second part of the creditcard algorithm add to sum non-multiplied digits

# American Express	378282246310005
# American Express	371449635398431
# American Express Corporate	378734493671000
# Diners Club	30569309025904
# Discover	6011111111111117
# Discover	6011000990139424
# JCB	3530111333300000
# JCB	3566002020360505
# MasterCard	2221000000000009
# MasterCard	2223000048400011
# MasterCard	2223016768739313
# MasterCard	5555555555554444
# MasterCard	5105105105105100
# Visa	4111111111111111
# Visa	4012888888881881
# Visa	4222222222222


# 378282246310005 as AMEX
# 371449635398431 as AMEX
# 5555555555554444 as MASTERCARD
# 5105105105105100 as MASTERCARD
# 4111111111111111 as VISA
# 4012888888881881 as VISA
# 1234567890 as INVALID
# 369421438430814 as INVALID
# 4062901840 as INVALID
# 5673598276138003 as INVALID
# 4111111111111113 as INVALID