import csv
from sys import argv, exit

def main():

    verification()

    People = []
    Str = []

    writeData(Str, People)
    countStr(Str)
    match = compare(Str, People)

    if match != None:
        print(match)
    else:
        print("No match")

    exit(0)

def verification():

    if len(argv) != 3:
        print(f"Usage: <{argv[0]}> <str_file.csv> <dna_file.txt>")
        exit(1)

    if argv[1][len(argv[1]) - 4:len(argv[1])] != ".csv":
        print("The str_file needs to be a .csv!")
        exit(2)

    if argv[2][len(argv[2]) - 4:len(argv[2])] != ".txt":
        print("The dna_file needs to be a .txt!")
        exit(3)

def writeData(Str, People):
    try:
        with open(argv[1], "r") as csv_file:
            for line in csv.DictReader(csv_file):
                People.append(line)
            csv_file.seek(0)
            for line in csv.reader(csv_file):
                for i in line:
                    dict = {}
                    if i != "name":
                        dict["base"] = i
                        dict["quantity"] = 0
                        Str.append(dict)
                break
            for person in People:
                for sequence in Str:
                    person[sequence["base"]] = int(person[sequence["base"]])
    except:
        print("The str_file was not found!")
        exit(2)

def countStr(Str):
    try:
        with open(argv[2], "r") as txt_file:
            line = txt_file.read()
            for i in range(len(Str)):
                count = 0
                begin = 0
                end = len(Str[i]["base"])
                while True:
                    last = line[begin:end]
                    if last == Str[i]["base"]:
                        count += 1
                        begin = end
                        end += len(Str[i]["base"])
                    else:
                        if count > Str[i]["quantity"]:
                            Str[i]["quantity"] = count
                        count = 0
                        begin += 1
                        end += 1
                    if end > len(line):
                        break
    except:
        print("The txt_file was not found!")
        exit(3)

def compare(Str, People):
    for i in range(len(People)):
        count = 0
        for j in range(len(Str)):
            if People[i][Str[j]["base"]] == Str[j]["quantity"]:
                count += 1
            else:
                break
        if count == len(Str):
            return People[i]["name"]
    return None

if __name__ == "__main__":
    main()
