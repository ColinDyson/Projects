NUM_KEYS = 26

def test(m, c):
	#performs a shift cipher attack on c to acquire a list of the 26 possible values of m,
	#The test passes if m is contained within c, and will then return the value of k
	print("Test value ", c, " finds ", m, ": ", end='')
	candidates = decode(c)
	if m.upper() in candidates:
		print("PASS, key = ", candidates.index(m.upper()))
	else:
		print("FAIL")
	print("\n")


def decode(c):
	#Basic shift cipher attack, shifts c by all 26 possible key values, and 
	#returns a list containing all shifted results
	a = ord("A")

	shiftedText = ""
	candidates = []

	for i in range(NUM_KEYS):
		shiftedText = ""
		
		for char in c:
			shiftedText += chr((ord(char) - a - i) % NUM_KEYS + a)
		
		candidates.append(shiftedText);

	return candidates


#ciphertext values were generated using ShiftCipher.py
test("aaa", "AAA")
test("aaa", "ZZZ")
test("helloworld", "FFF")
test("helloworld", "NKRRUCUXRJ")
test("zzzz", "ZZZZ")
test("zzzz", "AAAA")
test("thequickredfoxjumpedoverthelazydog", "MAXJNBVDKXWYHQCNFIXWHOXKMAXETSRWHZ")