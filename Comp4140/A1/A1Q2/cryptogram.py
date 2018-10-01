#Name - Colin Dyson
#userid - dysonc
#Student number - 7683407
NUM_LETTERS = 26
ENGLISH_FREQS = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.015, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001]
a = ord('a')
CIPHERTEXT = "jgrmqoyghmvbjwrwqfpwhgffdqgfpfzrkbeebjizqqocibzklfafgqvfzfwweogwopfgfhwolphlrlolfdmfgqwblwbwqolkfwbylblylfsfljgrmqbolwjvfpfwqvhqwffpqoqvfpqocfpogfwfjigfqvhlhlroqvfgwjvfpfolfhgqvqvfileogqilhqfqgiqvvosfafgbwqvhqwijvwjvfpfwhgfiwihzzrqgbabhzqocgfhx"
oldText = CIPHERTEXT
newText = ""
keyMap = ["a"] * NUM_LETTERS

while():
    printCryptogram()
    printKeyMap()
    printCharFreq()
    keyMap = updateKeyMap()
    applyKeyMap()

def printCryptogram():
    print(oldText)
def printKeyMap():
    print(keyMap)
def printCharFreq():
    letterCounts = [0] * NUM_LETTERS

    #count letters in cipherText
    for i in range (NUM_LETTERS):
        letterCounts[i] = oldText.count(chr(i + a))

    #print table of letters in the ciphertext and their frequencies, sorted highest to lowest

def updateKeyMap():
    #query user for substitution

def applyKeyMap():
    #Apply keyMap
    for i in range(len(oldText)):
        if(keyMap[ord(oldText[i]) - a] != -1):
            #print("Replacing", newText[i], "with", keyMap[ord(oldText[i]) - a])
            newText += keyMap[ord(oldText[i]) - a]

#cryptographicsystemsareextremelydifficulttobuildneverthelessforsomereasonmanynonexpertsinsistondesigningnewencryptionschemesthatseemtothemtobemoresecurethananyotherschemeonearththeunfortunatetruthhoweveristhatsuchschemesareusuallytrivialtobreak
# f - e
# q t
# w s
# g r
# l n
# o o
# v h
# h a
# b i
# p m
# l u
