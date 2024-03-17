from std import getInt

def main():
    while True:
        value = str(getInt("Number: "))
        if len(value) >= 13 and len(value) <= 16:
            break
        else:
            print("That's not a valid card number!")
    luhn(value)

def luhn(number):
    sum = 0
    for i in range(len(number)):
        if i < len(number)//2:
            num = int(number[len(number) - 2 * (i + 1)]) * 2
        else:
            num = int(number[len(number) - (2 * (i%(len(number)//2)) + 1)])
        if num < 10:
            sum += num
        else:
            for j in range(2):
                sum += int(str(num)[j])
    if sum%10:
        print("Invalid!")
    else:
        first_numbers = int(number[0:2])
        if first_numbers >= 40 and first_numbers <= 49:
            print("VISA")
        elif first_numbers >= 34 and first_numbers <= 37:
            print("AMEX")
        elif first_numbers >= 51 and first_numbers <= 55:
            print("MASTERCARD")
        else:
            print("Invalid")

if __name__ == "__main__":
    main()
