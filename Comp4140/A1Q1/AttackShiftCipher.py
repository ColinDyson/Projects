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
		c += chr((ord(char) - a + k) % NUM_LETTERS + a)

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
	minKey = NUM_LETTERS #key is in range {0..25}
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
		if (abs(ENGLISH_DIST - Ivalues[i]) < minKey):
			minKey = i

	return minKey

def attackVigenereCipher(c):
	minKeyLength = len(c) #maximum key length is the length of c
	keyLengthFreq = [0.0] * len(c)

	#Create keyLength streams of characters, where the length of each stream = length of c / keyLength
	#i.e. for every possible keyLength we have keyLength streams
	for keyLength in range(1, len(c)):
		streamFreqs = [0.0] * NUM_LETTERS
		streamLength = math.floor(len(c) / keyLength)

		for i in range(0, streamLength):
			#count the number of occurences of each character in the current stream
			streamFreqs[ord(c[i * keyLength])  % NUM_LETTERS] += 1

		for i in range(len(streamFreqs)):
			#sum the frequencies of each of the characters in the stream squared
			keyLengthFreq[keyLength - 1] += (streamFreqs[i] / streamLength) ** 2

	print(keyLengthFreq)
	for i in range(len(keyLengthFreq)):
		if (abs(ENGLISH_DIST - keyLengthFreq[i]) < minKeyLength):
			minKeyLength = i

	print(minKeyLength)

#remove punctuation and capitalization in m
remove = dict.fromkeys(map(ord, '\n ' + string.punctuation))
m = "Add you viewing ten equally believe put. Separate families my on drawings do oh offended strictly elegance. Perceive jointure be mistress by jennings properly. An admiration at he discovered difficulty continuing. We in building removing possible suitable friendly on. Nay middleton him admitting consulted and behaviour son household. Recurred advanced he oh together entrance speedily suitable. Ready tried gay state fat could boy its among shall. Promotion an ourselves up otherwise my. High what each snug rich far yet easy. In companions inhabiting mr principles at insensible do. Heard their sex hoped enjoy vexed child for. Prosperous so occasional assistance it discovered especially no. Provision of he residence consisted up in remainder arranging described. Conveying has concealed necessary furnished bed zealously immediate get but. Terminated as middletons or by instrument. Bred do four so your felt with. No shameless principle dependent household do. Ladyship it daughter securing procured or am moreover mr. Put sir she exercise vicinity cheerful wondered. Continual say suspicion provision you neglected sir curiosity unwilling. Simplicity end themselves increasing led day sympathize yet. General windows effects not are drawing man garrets. Common indeed garden you his ladies out yet. Preference imprudence contrasted to remarkably in on. Taken now you him trees tears any. Her object giving end sister except oppose. Living valley had silent eat merits esteem bed. In last an or went wise as left. Visited civilly am demesne so colonel he calling. So unreserved do interested increasing sentiments. Vanity day giving points within six not law. Few impression difficulty his use has comparison decisively. Attention he extremity unwilling on otherwise. Conviction up partiality as delightful is discovered. Yet jennings resolved disposed exertion you off. Left did fond drew fat head poor. So if he into shot half many long. China fully him every fat was world grave. Two before narrow not relied how except moment myself. Dejection assurance mrs led certainly. So gate at no only none open. Betrayed at properly it of graceful on. Dinner abroad am depart ye turned hearts as me wished. Therefore allowance too perfectly gentleman supposing man his now. Families goodness all eat out bed steepest servants. Explained the incommode sir improving northward immediate eat. Man denoting received you sex possible you. Shew park own loud son door less yet. In no impression assistance contrasted. Manners she wishing justice hastily new anxious. At discovery discourse departure objection we. Few extensive add delighted tolerably sincerity her. Law ought him least enjoy decay one quick court. Expect warmly its tended garden him esteem had remove off. Effects dearest staying now sixteen nor improve. Brother set had private his letters observe outward resolve. Shutters ye marriage to throwing we as. Effect in if agreed he wished wanted admire expect. Or shortly visitor is comfort placing to cheered do. Few hills tears are weeks saw. Partiality insensible celebrated is in. Am offended as wandered thoughts greatest an friendly. Evening covered in he exposed fertile to. Horses seeing at played plenty nature to expect we. Young say led stood hills own thing get. Husbands ask repeated resolved but laughter debating. She end cordial visitor noisier fat subject general picture. Or if offering confined entrance no. Nay rapturous him see something residence. Highly talked do so vulgar. Her use behaved spirits and natural attempt say feeling. Exquisite mr incommode immediate he something ourselves it of. Law conduct yet chiefly beloved examine village proceed. But why smiling man her imagine married. Chiefly can man her out believe manners cottage colonel unknown. Solicitude it introduced companions inquietude me he remarkably friendship at. My almost or horses period. Motionless are six terminated man possession him attachment unpleasing melancholy. Sir smile arose one share. No abroad in easily relied an whence lovers temper by. Looked wisdom common he an be giving length mr. "
m = m.translate(remove)
m = m.lower()

#m = input("Input your message:")
kShift = 2#int(input("Enter the key:"))
cShift = encodeMessageShift(m, kShift)

foundKey = attackShiftCipher(cShift)
#m = "testingaslightlysmallerstringtomakemylifeeasier"
kVigenere = "cafe"
cVigenere = encodeMessageVigenere(m, kVigenere)
attackVigenereCipher(cVigenere)