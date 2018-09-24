#Created by Colin Dyson on 09/24/2018 for COMP 4140 A1 Q1

import string
import math

ENGLISH_DIST = 0.065
ALPHABET = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
ENGLISH_FREQS = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.015, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001]
DECIMALS = 3 #for rounding
NUM_LETTERS = len(ALPHABET) #number of letters in our alphabet
a = ord("a") #for shifting

def encodeMessageShift(m, k):
	c = ""
	#shift each letter in m by k
	for char in m:
		c += chr((ord(char) - a + ord(k) - a) % NUM_LETTERS + a)

	return c

def encodeMessageVigenere(m, k):
	#Perform Vigenere's shift encryption with key of some length on m
	c = ""

	for char in range(len(m)):
		mCharInt = ord(m[char]) - a
		kCharInt = ord(k[char % len(k)]) - a

		c += chr((mCharInt + kCharInt) % NUM_LETTERS + a)

	return c

def attackShiftCipher(c):
	cipherFreqs = [0] * NUM_LETTERS
	Ivalues = [0] * NUM_LETTERS
	minKey = 25 #key is in range {0..25}
	p = 0.0
	q = 0.0

	#count frequency of each letter in the ciphertext
	for letter in ALPHABET:
		cipherFreqs[(ord(letter) - a)] = c.count(letter) / len(c)

	#for all possible key values, calculate the sum of p * q for each letter of the alphabet
	#p = the frequency at which i appears in normal english text
	#q = the frequency at which (i + j) appears in the cipher text
	for j in range(NUM_LETTERS):
		for i in range(NUM_LETTERS):
			p = ENGLISH_FREQS[i]
			q = cipherFreqs[(i + j) % NUM_LETTERS]
			Ivalues[j] += (p * q)

		Ivalues[j] = round(Ivalues[j], DECIMALS)

	#find the key value for which the sum is closest to 0.065
	for i in range(len(Ivalues)):
		if (abs(ENGLISH_DIST - Ivalues[i]) < abs(ENGLISH_DIST - Ivalues[minKey])):
			minKey = i

	return chr(minKey + a)

def attackVigenereCipher(c):
	ACCEPTANCE_MARGIN = 0.01 #how close must the distribution in our stream math the normal english distribution before we are confident we have found the stream length
	SValues = [0.0] * math.floor(len(c) / 2)
	keyLength = 1
	streamStart = 0
	possibleKeyLengths = []
	#when keyLength is at least half of the ciphertext, our stream length is only 2, which does not give enough data for a probabilistc approach

	#Create keyLength streams of characters, where the length of each stream = length of c / keyLength
	#i.e. for every possible keyLength we have keyLength streams
	while keyLength < math.floor(len(c) / 2):
		streamFreqs = [0.0] * NUM_LETTERS
		streamLength = math.floor(len(c) / (keyLength - streamStart))

		for i in range(0, streamLength):
			#count the number of occurences of each character in the current stream
			streamFreqs[ord(c[streamStart + (i * keyLength)])  % NUM_LETTERS] += 1

		for i in range(len(streamFreqs)):
			#sum the frequencies of each of the characters in the stream squared
			SValues[keyLength - 1] += (streamFreqs[i] / streamLength) ** 2
			#keyLength of 1 is stored in index 0 of our SValues array

		if (abs(ENGLISH_DIST - SValues[keyLength - 1]) <= ACCEPTANCE_MARGIN):
			possibleKeyLengths.append(keyLength)

		keyLength += 1
	
	#The smallest value among the list of possible keyLengths is most likely the actual keyLength
	trueKeyLength = min(possibleKeyLengths)
	streamStrings = []

	#Construct a set of trueKeyLength strings
	for i in range(0, trueKeyLength):
		streamString = ""
		for j in range(0, math.floor(len(c) / trueKeyLength)):
			streamString += c[(i + (trueKeyLength * j)) % len(c)]
		streamStrings.append(streamString)

	keys = ""
	#perform a shift attack on each stream
	for i in range(len(streamStrings)):
		keys += attackShiftCipher(streamStrings[i])
	#simply combine the deciphered characters in order to form the key
	return keys

def cleanMessage(m):
	#remove punctuation and capitalization in m
	newMessage = ""
	for char in m:
		if char not in string.punctuation and char != " ":
			newMessage += char.lower()

	return newMessage.strip()

def testShiftAttack(k, m):
	cipherText = encodeMessageShift(m, k)
	print("Shift Attack with key =", k, ":", end="\t")

	if  attackShiftCipher(cipherText) == k:
		print("PASS")
	else:
		print("FAIL")

def testVigenereAttack(k, m):
	cipherText = encodeMessageVigenere(m, k)
	print("Vigenere Attack with key =", k, ":", end="\t")

	if attackVigenereCipher(cipherText) == k:
		print("PASS")
	else:
		print("FAIL")

#Random passages of english text were taken randomly from https://www.writerswrite.com/books/excerpts/
with open('SampleMessages.txt') as f:
	for line in f:
		m = cleanMessage(line)
		print("\nNew Test Message")
		testShiftAttack("a", m)
		testShiftAttack("b", m)
		testShiftAttack("z", m)
		
		testVigenereAttack("ls", m)
		testVigenereAttack("cafe", m)
		testVigenereAttack("longerkey", m)
		print("Complete")