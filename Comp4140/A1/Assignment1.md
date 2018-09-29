Colin Dyson - 7683407
# COMP 4140 ASSIGNMENT 1

3. To attack a shift cipher, we simply need to choose a message containing the single character 'a'. The resulting ciphertext will then be 
$c = \{a..z\}, |c| = 1$. Since our message is 'a', the resulting ciphertext c will be the value of the key used for all other ciphertexts.  
To attack a substitution cipher we only need to supply a message of length 26. Simply make the message the english alphabet and the resulting ciphertext will be a one to one keymap for all ciphertexts. If, for example, the fifth character of our ciphertext was 'T', we know that 'e' has been substituted for 'T' in every other ciphertext.  
Breaking a Vigenere cipher requires choosing a message of at least $|k|$. If we send the message $'a'^k$, $c = k$. If $|k|$ is unknown, we can find it by choosing incrementally longer messages. At the first instance of our ciphertext constaining exactly 2 equal substrings, $|k| = |c|/2$. If the key chosen were some string which itself contained equal substrings, then our chosen k would not result in the correct plaintext, and we would continue to increment $|c|$.

4. The modified scheme is **not** perfectly secret. For an ecryption scheme to be perfectly secret, it must hold true that $Pr[M = m | C = c] = Pr[M =m]$. If we change the scheme such that $k \neq 0^l$, then we have leaked the information that $c \neq m$. Therefore $Pr[M =m|C=c] < Pr[M=m]$ and our scheme is no longer perfectly secret.

5. Gen of a shift cipher provides $k \in K = \{a..z\}$, where k is chosen with probability $1/|K|$. If only a single character is encrypted, then $m \in M = \{a..z\}$ and $c \in C = \{a..z\}$, so $|K| = |M| = |C|$. 
    


