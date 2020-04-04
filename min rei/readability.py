

def main():
    letters, sentences, words = 0, 0, 0
    text = str(input("Text: "))

    n = len(text)
    
    for i in range(n):
        if text[i].isalpha() == True:
            letters += 1

    for i in range(n):
        if text[i].isalpha() == False:
            if text[i - 1].isalpha() == True and (text[i] not in ("-", "'") or (text[i] == "'" and text[i + 1] == " ")):
                words += 1
    
    for i in range(n):
        if text[i] in (".", "!", "?"):
            sentences += 1
    
    L = 100 * (letters / words)
    S = 100 * (sentences / words)
    
    index = round(0.0588 * L - 0.296 * S - 15.8)
    
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")
    

main()