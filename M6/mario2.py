from std import getInt

def main():
    while True:
        height = getInt("Height: ")
        if height > 0:
            break
        else:
            print("That's not a positive integer bigger than 0!")
    draw(height)

def draw(h):
    for i in range(h):
        spaces = h - i - 1
        for j in range((h * 2) + 1):
            if j < spaces or j == h or j > h + (h - spaces):
                print(" ", end = "")
            else:
                print("#", end = "")
        print()

if __name__ == "__main__":
    main()
