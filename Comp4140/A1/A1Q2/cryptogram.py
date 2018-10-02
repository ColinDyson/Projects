#Name - Colin Dyson
#userid - dysonc
#Student number - 7683407
#dependancies - prettytable - run `pip install prettytable`
import textwrap
from prettytable import PrettyTable

def printCryptogram(c):
    print("\n" + textwrap.fill(c, LINE_LENGTH))

def printKeyMap(c):
    print("\nKey Map:\n")
    t = PrettyTable()
    t.field_names = ["Character", "Count in C", "Key"]
    for i in range (len(ALPHABET)):
        t.add_row([ALPHABET[i], c.lower().count(ALPHABET[i]), keyMap[i]])
    print(t)

def updateKeyMap():
    #query user for substitution
    userInput = input('Enter a new key mapping of the form \"x y": ').split()
    oldChar = userInput[0].lower()
    newChar = userInput[1].lower()
    oldCharIndex = ord(oldChar) - a
    keyMap[oldCharIndex] = newChar

def applyKeyMap():
    #Apply keyMap
    #using the same key for one character is allowed, however the modified
    #ciphertext will show both characters substitued, so keeping track is up
    #to the user
    newText = ""
    for char in CIPHERTEXT:
        if keyMap[ord(char.lower()) - a] != -1:
            newText += keyMap[ord(char.lower()) - a]
        else:
            newText += char
    return newText

LINE_LENGTH = 61
ALPHABET = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
ENGLISH_FREQS = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.015, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001]
a = ord('a')
CIPHERTEXT = "JGRMQOYGHMVBJWRWQFPWHGFFDQGFPFZRKBEEBJIZQQOCIBZKLFAFGQVFZFWWEOGWOPFGFHWOLPHLRLOLFDMFGQWBLWBWQOLKFWBYLBLYLFSFLJGRMQBOLWJVFPFWQVHQWFFPQOQVFPQOCFPOGFWFJIGFQVHLHLROQVFGWJVFPFOLFHGQVQVFILEOGQILHQFQGIQVVOSFAFGBWQVHQWIJVWJVFPFWHGFIWIHZZRQGBABHZQOCGFHX"
tempCipher = CIPHERTEXT
keyMap = [-1] * len(ALPHABET)

while(1):
    printCryptogram(tempCipher)
    printKeyMap(tempCipher)
    updateKeyMap()
    tempCipher = applyKeyMap()

#cryptographicsystemsareextremelydifficulttobuildneverthelessforsomereasonmanynonexpertsinsistondesigningnewencryptionschemesthatseemtothemtobemoresecurethananyotherschemeonearththeunfortunatetruthhoweveristhatsuchschemesareusuallytrivialtobreak
