def getInt(input_str):
    Num = []
    for i in range(10):
        Num.append(f"{i}")
    while True:
        number = input(input_str)
        count = 0
        sign = 0
        for i in range(len(number)):
            if number[i] in Num:
                count += 1
            elif number[0] == '-' and sign < 1:
                sign += 1
            else:
                break
        if len(number) == count + sign and len(number) > 0:
            return int(number)
        else:
            print("That's not an integer")

def getFloat(input_str):
    Num = []
    for i in range(10):
        Num.append(f'{i}')
    while True:
        num = input(input_str)
        count = 0
        point = 0
        sign = 0
        for digit in num:
            if digit in Num:
                count += 1
            elif digit == '.' and point < 1:
                point += 1
            elif digit == '-' and sign < 1:
                sign += 1
            else:
                break
        if len(num) == count + point + sign and len(num) != 0:
            return float(num)
        else:
            print("That's not a float")

