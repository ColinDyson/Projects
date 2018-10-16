Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

(1)
- Gen: on input $1^n$, choose uniform $k \in \{0,1\}^n$ and output it as the key

- Enc: on input a key $k \in \{0,1\}^n$ and a message $m \in \{0,1\}^l$, $|m| = l \leq \ell(n)$, choose $p \in \{0, 1\}^{2\ell(n) - l}$ uniformly. Append $q =\{0, 1\}^{p_{10}}$ chosen uniformly to the end of $m$. Finally, place $p$ at the beginning of $m$. The resulting $m\prime$ will be of length $2\ell(n) + n$. Output the ciphertext
\[
\begin{align}
m\prime &= \langle p, m, q \rangle\\
c_i &:= k \oplus m\prime_i\\
c = &\langle c_0, c_1, ... c_i \rangle\\
\end{align}
\]

- Dec: on input a key $k \in \{0,1\}^n$ and a ciphertext $c \in \{0,1\}^{2\ell(n) + n}$, output the message
\[
\begin{align}
p &= m\prime_0 \oplus k\\
m_i &:= k \oplus c_i\\
m = &\langle m_p, m_1, ... m_{|m\prime| - (p + \ell(n))} \rangle\\
\end{align}
\]

The scheme accepts messages of variable length up to some polynomial function of $n$, and produces ciphertexts of uniform length $2\ell(n) + n$. Since an adversary $A$ knows $n$, they could try and guess the value of $p$ (the index within our ciphertext where $m$ begins). $p$ is of length $n$, and is chosen uniformly, so for any value $P$ chosen from $\{0, 1\}^n$,
\[
Pr[P = p] = \frac{1}{2^n}
\]
Which is a negligible function of $n$.

(2)

(3)

(4)

(5)

(6)
