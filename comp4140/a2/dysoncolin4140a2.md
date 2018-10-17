Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

######(1)
- Gen: on input $1^n$, choose uniform $k \in \{0,1\}^n$ and output it as the key

- Enc: on input a key $k \in \{0,1\}^n$ and a message $m \in \{0,1\}^l$, $|m| = l \leq \ell(n)$, choose $p \in \{0, 1\}^{2\ell(n) - l}$ uniformly and append to the end of $m$. Finally, encode $q = |p| + n$ into $n$ bits and append to $m$. The resulting $m\prime$ will be of length $2\ell(n) + n$. Output the ciphertext
\[
\begin{align}
m\prime &= \langle m, p, q \rangle\\
c_i &:= k \oplus m\prime_i\\
c &= \langle c_0, c_1, ... c_i \rangle\\
\end{align}
\]

- Dec: on input a key $k \in \{0,1\}^n$ and a ciphertext $c \in \{0,1\}^{2\ell(n) + n}$, output the message
\[
\begin{align}
q &= m\prime_0 \oplus k\\
m_i &:= k \oplus c_i\\
m &= \langle m_0, m_1, ... m_{|c| - q} \rangle\\
\end{align}
\]

The scheme accepts messages of variable length up to some polynomial function of $n$, and produces ciphertexts of uniform length $2\ell(n) + n$. An adversary $A$ running in probabilistic polynomial time could perform an exhaustive search over all values of $q$. For any possible value $Q$,
\[
\mathrm{Pr}[Q = q] = \frac{1}{2^n}
\]
Which is a negligible function of $n$. Therefore,
\[
\mathrm{Pr}[{\mathrm{Priv}_k}^{eav}_{A, \Pi} = 1] \leq \frac{1}{2} + \mathrm{negl}(n)
\]
And our encryption scheme has indistinguishable encryptions in the presence of an eavesdropper even when messages are not restricted to being equal length.  

######(2)

######(3)  
**a)** The scheme does not have indistinguishable encryptions in the presence of an eavesdropper. The value of $r$ is concatenated to the beginning of our ciphertext. Since we use $G(r)$ to encrypt $m$ and any adversary can be assumed to have access to $G$, they are fully able to decrypt any $c$. CPA-security is just stricter definition of indistinguishability in the presence of an eavesdropper, then the scheme is not cpa-secure for the same reasons.  

**b)** This scheme uses the pseudorandom function $F_k$ with input $0^n$ to encrypt a message of length $n$. Encrypting any message $m$ will then result in a ciphertext of length $n$. Since $\mathit{|C|} = \mathit{|M|} = \mathit{|K|}$ and keys are chosen with

(4)

(5)

(6)
