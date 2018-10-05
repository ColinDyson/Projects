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

(4) The modified scheme is **not** perfectly secret. For an encryption scheme to be perfectly secret, it must hold true that $Pr[M = m | C = c] = Pr[M =m]$. If we change the scheme such that $k \neq 0^l$, then for any message chosen, $c \neq m$. so $Pr[C = c | M = m] = \frac{1}{|\mathcal{M}| - 1} \neq Pr[M = m]$.

(5.a) Gen of a shift cipher provides $k \in \mathcal{K} = \{a..z\}$, where k is chosen with probability $1/|\mathcal{K}|$. If only a single character is encrypted, then $m \in \mathcal{M} = \{a..z\}$ and $c \in \mathcal{C} = \{a..z\}$, so $|\mathcal{K}| = |\mathcal{M}| = |\mathcal{C}| = 26$. Assume adding to $m^{'}, k, c$ is taken modulo 26.  

Given $c \in \mathcal{C}, m^{'} \in M:$
\[
  \begin{align}
  Pr[C = c | M = m^{'}] &= Pr[Enc_{(k)}(m^{'})] = c\\
  &= Pr[m^{'} + k] = c\\
  &= Pr[k = c - m]\\
  &= Pr[K = k]\\
  &= \frac{1}{26}, \mathrm{given\;Gen}
  \end{align}
\]
For any $m^{'} \in \mathcal{M}$, and $\forall c \in \mathcal{C}$,
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

(5.b) An encryption scheme may only be considered perfectly secret iff $|\mathcal{M}| = |\mathcal{K}| = |\mathcal{C}|$. Our key space $\mathcal{K}$ is the set of all permutations of the English alphabet. So $|\mathcal{K}| = 26!$. $\therefore |\mathcal{M}| = 26!$.  

(5.c) With a fixed period $t$, the keys used by the Vigenere cipher are all character strings of length $t$. Our messages are all of length $t$, and the ciphertexts our scheme produces must therefore also be of length $t$. So $|\mathcal{K}| = |\mathcal{M}| = |\mathcal{C}| = 26^t$.  

Suppose the scheme is not perfectly secret. Then the first part of Shannon's Theorem holds true, then it must be true that
\[\exists m \in \mathcal{M}, \exists c \in \mathcal{C},\,\forall \;k \in \mathcal{K} \mathrm{\;such\;that\;} Enc_{(k)}(m) \neq c\]
Choose $t =$ 7, $m =$ 'aaaaaaa', $c =$ 'colours'
\[
  \begin{align}
  c_i &= m_i + k_i\\
  k_i &= c_i - m_i\\\\
  k &= \mathrm{c-a, o-a, l-a, o-a, u-a, r-a, s-a}\\
  &= \mathrm{colours}
  \end{align}
\]
But if $k = \mathrm{'colours' and\;} m = \mathrm{'aaaaaaa',\;}  Enc_{(k)}(m) =$ 'colours', and $Enc_{(k)}(m) = c$. It is also apparent that $k$ will always be some $t$ length string of characters, since for correctness we must compute all character arithmetic under modulo 26. i.e. This equality will hold for all values of $k$ and we have a contradiction. $\therefore$ our scheme is perfectly secret.

(6) Our encryption scheme will be a modified version of the One-Time Pad which uses two keys, $k_1$ and $k_2$. Let $n$ be the length of $m$. Let $t,l \in Z^+$, where $l$ represents the length of $k_1$ and t represents the length of $k_2$. Unlike the one time pad, $l$ need not equal $n$ In addition to Gen, which chooses some $\{0,1\}^l$ over a uniform distribution, we now also have access to $Gen^{'}$, which chooses $\{0,1\}^t$. Our modified scheme simply appends $k_2$ to $k_1$ before encryption of $m$. In order for our scheme to satisfy $Pr[\mathrm{Dec}_K(\mathrm{Enc}_K(m)) = m] \geq 2^{-t}$, we only send the intended reciever of the message $k_1$, and guaruntee that $t = n - l$. Since $k_2$ is not sent to the recipient, decryption of the message will result in $\frac{1}{2^t}$ possible messages which were encrypted as long as $l < n$. $|\mathcal{K}|$ must therefore always be at least $2^{n - t}$.

e.g. Let $m = 1010101010, k_1 = 11001, k_2 = 00001$
\[
  \begin{align}
  m &= 1010101010\\
  k_1 + k_2 &= 1100100001\\
  c = m \oplus (k_1 + k_2) &= 0110001011 \\
  \end{align}
\]

To show perfect secrecy, we must consider two cases. If $l \geq n$, then our scheme is equivalent to the One-Time Pad. If, however, $l < n$, we must prove that we retain perfect secrecy. When $l < n$, then $t \geq n = l$. Let $C$ be any $c \in \mathcal{C}$, and $M$ be any $m \in \mathcal{M}$. If in this case we imagine $m$ as two concatenated messages, where the first message and $k_1$ are equivalent to using a one time pad on a message of length $l$, we are left with the last $n - l$ bits of $m$ to be encoded with $k_2$.

Let us assume that the following proof is made over the last $n- l$ bits of $m$, called $m_2$. Let $c_2$ represent the last $n - l$ bits of the resulting ciphertext $c$. Since $k_2$ is chosen uniformly over $\mathcal{K}$,
\[
  \begin{align}
  Pr[C = c_2 | M = m_2] &= Pr[\mathrm{Enc}_{K}(m_2) = c_2]\\
  &= Pr[m_2 \oplus k_2 = c_2]\\
  &= Pr[k_2 = m_2 \oplus c_2]\\
  &= \frac{1}{2^t}, \mathrm{given\;Gen^{'}}
  \end{align}
\]

Since $k_2$ is not given to our message recipient,
\[
  \begin{align}
  Pr[C = c_2] = \frac{1}{|\mathcal{C}_2|} = \frac{1}{2^t}
  \end{align}
\]

\[
  \begin{align}
  Pr[\mathrm{Dec}_K(c_2) = m_2] &= Pr[M = m_2 | C = c_2]\\
  &= \frac{Pr[C = c_2 | M = m_2] \cdot Pr[M = m_2]}{Pr[C = c_2]}\\
  &= \frac{\frac{1}{2^t} \cdot Pr[M = m_2]}{\frac{1}{2^t}}\\
  &= Pr[M = m_2]
  \end{align}
\]

$\therefore$ Our scheme is perfectly secret for both halves of $m$ and perfectly secret for all $m$.
