Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

(1) See attackciphers.py for coded solution. Can be run using `python attackciphers.py` Test strings were chosen randomly from https://www.writerswrite.com/books/excerpts/

(2) Cryptogram was solved with help from cryptogram.py, which serves as an interactive cryptogram helper and can be run using `python cryptogram.py`. The user can enter what letters they wish to substitute, and the updated ciphertext will be displayed. Using information gathered from the frequency table produced by the script, and some intuition, the solution was found to be:  

```cryptographic systems are extremely difficult to build nevertheless for some reason many nonexperts insist on designing new encryption schemes that seem to them to be more secure than any other scheme on earth the unfortunate truth however is that such schemes are usually trivial to break```

Spaces were inserted manually for readability.

(3) To attack a shift cipher, we simply need to choose a message containing the single character 'a'. The resulting ciphertext will then be
$c = \{a..z\}, |c| = 1$. Since our message is 'a', the resulting ciphertext c will be the value of the key used for all other ciphertexts.  
To attack a substitution cipher we only need to supply a message of length 26. Simply make the message the English alphabet and the resulting ciphertext will be a one to one keymap for all ciphertexts. If, for example, the fifth character of our ciphertext was 'T', we know that 'e' has been substituted for 'T' in every other ciphertext.  
Breaking a Vigenere cipher requires choosing a message of at least $|k|$. If we send the message $'a'^k$, $c = k$. If $|k|$ is unknown, we can find it by choosing incrementally longer messages. At the first instance of our ciphertext containing exactly 2 equal substrings, $|k| = \frac{|c|}{2}$. If the key chosen were some string which itself contained equal substrings, then our chosen k would not result in the correct plaintext, and we would continue to increment $|c|$.

(4) The modified scheme is **not** perfectly secret. For an encryption scheme to be perfectly secret, it must hold true that $Pr[M = m | C = c] = Pr[M =m]$. If we change the scheme such that $k \neq 0^l$, then we have leaked the information that $c \neq m$. Therefore $Pr[M =m|C=c] < Pr[M=m]$ and our scheme is no longer perfectly secret.

(5.a) Gen of a shift cipher provides $k \in K = \{a..z\}$, where k is chosen with probability $1/|K|$. If only a single character is encrypted, then $m \in M = \{a..z\}$ and $c \in C = \{a..z\}$, so $|K| = |M| = |C| = 26$.  

Given $c \in C, m^{'} \in M:$
\[
  \begin{align}
  Pr[C = c | M = m^{'}] &= Pr[Enc_{(k)}(m^{'})] = c\\
  &= Pr[m^{'} + k] = c\\
  &= Pr[k = c - m]\\
  &= \frac{1}{26}, \mathrm{given\;Gen}
  \end{align}
\]
For any $m^{'} \in M$, and $\forall c \in C$,
\[
  \begin{align}
  Pr[C = c] &= \sum_{m^{'} \in M}Pr[C=c | M = m^{'}] \cdot Pr[M = m^{`}]\\
  &= \frac{1}{26} \sum_{m^{'} \in M} Pr[M=m^{`}]\\
  &= \frac{1}{26}
  \end{align}
\]
Using Baye's Theorem:
\[
  \begin{align}
  Pr[M = m |C = c] &= \frac{Pr[C =c | M = m] \cdot Pr[M = m]}{Pr[C=c]}\\
  &= \frac{\frac{1}{26} \cdot Pr[M = m]}{\frac{1}{26}}\\
  &= Pr[M = m]
  \end{align}
\]
$\therefore$ the scheme is perfectly secret.

(5.b) An encryption scheme may only be considered perfectly secret iff $|M| = |K| = |C|$. Our key space $K$ is the set of all permutations of the English alphabet. So $|K| = 26!$. $\therefore |M| = 26!$.  

(5.c) With a fixed period $t$, the keys used by the Vigenere cipher are all character strings of length $t$. Our messages are all of length $t$, and the ciphertexts our scheme produces must therefore also be of length $t$. So $|K| = |M| = |C| = 26^t$.  

Suppose the scheme is not perfectly secret. Since the first part of Shannon's Theorem holds true, then it must be true that
\[\exists m \in M, \exists c \in C,\,\forall \;k \in K \mathrm{\;such\;that\;} Enc_{(k)}(m) \neq c\]
Choose $t =$ 7, $m =$ 'aaaaaaa', $c =$ 'colours'
\[
  \begin{align}
  c_i &= m_i + k_i\\
  k_i &= c_i - m_i\\\\
  k &= \mathrm{c-a, o-a, l-a, o-a, u-a, r-a, s-a}\\
  &= \mathrm{colours}
  \end{align}
\]
But if $k = \mathrm{'colours' and\;} m = \mathrm{'aaaaaaa',\;}  Enc_{(k)}(m) =$ 'colours', and $Enc_{(k)}(m) = c$. We have a contradiction. $\therefore$ our scheme is perfectly secret.

(6) temp
