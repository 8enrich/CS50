def getInt(input_str: str) -> int:

    while True:

        numStr = input(input_str)

        try:
            num = int(numStr)
            return num
        except:
            print("That's not an integer")

def getFloat(input_str: str) -> float:

    while True:

        numStr = input(input_str)

        try:
            num = float(numStr)
            return num
        except:
            print("That's not a float")
