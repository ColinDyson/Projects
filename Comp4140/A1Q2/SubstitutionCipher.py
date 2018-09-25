NUM_LETTERS = 26
ENGLISH_FREQS = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.015, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001]
a = ord('a')
cipherText = "jgrmqoyghmvbjwrwqfpwhgffdqgfpfzrkbeebjizqqocibzklfafgqvfzfwweogwopfgfhwolphlrlolfdmfgqwblwbwqolkfwbylblylfsfljgrmqbolwjvfpfwqvhqwffpqoqvfpqocfpogfwfjigfqvhlhlroqvfgwjvfpfolfhgqvqvfileogqilhqfqgiqvvosfafgbwqvhqwijvwjvfpfwhgfiwihzzrqgbabhzqocgfhx"
newText = ""
letterCounts = [0] * NUM_LETTERS
keyMap = ["a"] * NUM_LETTERS


#count letters in cipherText
for i in range (NUM_LETTERS):
    letterCounts[i] = cipherText.count(chr(i + a))

#Find the most common characters in our cipherText
for i in range(NUM_LETTERS):
        mostCommonCipherChar = chr(letterCounts.index(max(letterCounts)) + a)
        mostCommonEnglishChar = chr(ENGLISH_FREQS.index(max(ENGLISH_FREQS)) + a)
        # print("cipher char:", mostCommonCipherChar)
        # print("english char:", mostCommonEnglishChar)

        if mostCommonCipherChar != -1 and mostCommonEnglishChar != -1:
            keyMap[ord(mostCommonEnglishChar) - a] = mostCommonCipherChar
            letterCounts[ord(mostCommonCipherChar) - a] = -1
            ENGLISH_FREQS[ord(mostCommonEnglishChar) - a] = -1

#Apply keyMap
print(keyMap)
for i in range(len(cipherText)):
    if(keyMap[ord(cipherText[i]) - a] != -1):
        #print("Replacing", cipherText[i], "with", keyMap[ord(cipherText[i]) - a])
        newText += keyMap[ord(cipherText[i]) - a]

print(newText)
print(cipherText)

#cryptographicsystemsareextremelydifficulttobuildneverthelessforsomereasonmanynonexpertsinsistondesigningnewencryptionschemesthatseemtothemtobemoresecurethananyotherschemeonearththeunfortunatetruthhoweveristhatsuchschemesareusuallytrivialtobreak
f - e
q t
w s
g r
l n
o o
v h
h a
b i
p m
l u
