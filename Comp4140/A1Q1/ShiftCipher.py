#Basic Shift Cipher Implementation to create test data, fails if spaces 
#or punctation are input.

m = input("Enter the message you wish to encrypt:").lower()

k = int(input("Enter the key used for encryption:"))

a = ord("a")

c = "";

for char in m:
	c += chr(((ord(char) - a + k) % 26 ) + a)

print("Your encrypted message is:", c)