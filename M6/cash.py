from std import getFloat

def main():
    while True:
        value = getFloat("Change owed: ")
        if value > 0:
            break
        else:
            print("That's not a positive float bigger than 0!")
    result = change(value)
    print(result)

def change(x):
    Coins = [25, 10, 5, 1]
    x *= (10**2)
    x = int(x)
    position = 0
    count = 0
    while x > 0:
        if x >= Coins[position]:
            x -= Coins[position]
            count += 1
        else:
            position += 1
    return count

if __name__ == "__main__":
    main()
