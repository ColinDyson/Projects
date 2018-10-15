Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

(1)
- Gen: on input $1^n$, choose uniform $k \in {0,1}^n$ and output it as the key

- Enc: on input a key $k \in \{0,1\}^n$ and a message $m \in \{0,1\}^{(n)}$, $|m| \leq \ell(n)$,  pad $m$ with $0^k$ to produce $m\prime$ such that $p = \ell(n) + k$ results in the smallest prime number larger than $\ell(n)$. Output the ciphertext
\[
\begin{align}
c_i := &k \oplus m_i\\
c = &\langle c_0, c_1, ... c_i \rangle\\
\end{align}
\]

- Dec: on input a key $k \in \{0,1\}^n$ and a ciphertext $c \in \{0,1\}^{\ell(n) + k}$, output the message
\[
\begin{align}
m_i := &k \oplus c_i\\
m = &\langle m_0, m_1, ... m_{\ell(n)} \rangle\\
\end{align}
\]

Doesn't work: key is in first $n$ bits of msg $0^{\ell(n)}$

(2)

(3)

(4)

(5)

(6)
