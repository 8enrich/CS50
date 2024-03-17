def main():
    text = input("Text: ")
    value = grade(text)
    if value <= 1:
        print("Before grade 1")
    elif value < 16:
        print(f"Grade {value}")
    else:
        print("Grade 16+")


def grade(text):
    Alphabet = []
    Points = ['.','?','!']
    for i in range(26):
        Alphabet.append(chr(65 + i))
        Alphabet.append(chr(97 + i))
    letters = 0
    words = 0
    phrases = 0
    for i in range(len(text)):
        if text[i] in Alphabet:
            letters += 1
        elif text[i] == ' ':
            words += 1
        elif text[i] in Points:
            phrases += 1
    words += 1
    index = 0.0588 * (letters/words) * 100 - 0.296 * (phrases/words) * 100 - 15.8
    index = round(index)
    return index

if __name__ == "__main__":
    main()
