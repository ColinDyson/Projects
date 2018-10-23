Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

######(1)
Define our encryption scheme as follows: on input of a plaintext message $m$ where $|m| \leq \ell(n)$, where $\ell(n)$ is some polynomial function of $n$:

We pad $m$ to a length of $L = \ell(n) + n$. Generate $r \in \{0, 1\}^{L - |m|}$ where $r$ is chosen from a uniform distribution. Append $r$ to $m$ to create $m'$. Finally, for every $m_i$ of length $n$ in $m$, generate the ciphertext $c_i = m_i \oplus k$ and concatenate the resulting $c_i$ together.
\[
\begin{align}
m' &= \langle m, r \rangle\\
&= \langle m_0, m_1, .. m_i \rangle\\
c_i &= m_i \oplus k\\
c &= \langle c_0, .. c_i \rangle
\end{align}
\]
We create an experiment with some PPT adversary $A$ with eavesdropping capabilities on our scheme $\Pi$. $A$ produces two messages $m_0, m_1$ of at most length $\ell(n)$. The messages need not be the same length. Our experiment chooses a bit $b$ randomly, then produces $c = \mathrm{Enc}_k(m_b)$. $A$ recieves $c$, then outbputs a bit $b'$.
\[
\begin{align}
\mathrm{If\;b' = b,\;}&{\mathrm{Priv}_k}^{eav}_{A, \Pi} = 1\\
\mathrm{Else,\;}&{\mathrm{Priv}_k}^{eav}_{A, \Pi} = 0
\end{align}
\]
For our scheme to be secure, it must hold that
\[
\mathrm{Pr}[{\mathrm{PrivK}}^{eav}_{A, \Pi} = 1] \leq \frac{1}{2} + \mathrm{negl}(n)
\]
Where $\mathrm{negl}(n)$ is a negligible function of $n$. Since we can assume both $k$ and $r$ are chosen from a uniform distribution, then $m_i \oplus k$ and $r_i \oplus k$ must also be indistinguishable from a random distribution, and our adversary will not be able to discern which portion of the ciphertext was generated using $m_i$ or $r_i$. We observe that for any length of $m$ that $A$ provides, we are padding $m$ to a uniform length of $\ell(n) + n$ with random bits. Since $|m| \leq \ell(n)$, the number of bits we are padding by $p \geq n$. Let $q(n)$ be the upper bound on the number of encryption queries made by $A$. If $A$ chose to encrypt some message of length $\ell(n)$ (Our worst case scenario), then it would be guaranteed that the last $n$ bits of $c$ would be the result of $r_i \oplus k$. $A$ could perform at most $q(n) / 2^n$ attempts at guessing the value of the key.  

Combining the above with the ever present possibility of a random guess resulting in success, we have shown that
\[
\mathrm{Pr}[{\mathrm{PrivK}}^{eav}_{A, \Pi} = 1] \leq \frac{1}{2} + \frac{q(n)}{2^n}
\]
Since $q(n)$ is polynomial, $\frac{q(n)}{2^n}$ is negligible. Therefore, we have shown that our scheme is eav-secure for variable length messages of at most length $\ell(n)$.

######(2)

######(3)  
**a)** The scheme does **not** have indistinguishable encryptions in the presence of an eavesdropper. If $c = G(r) \oplus m$, then $m = G(r) \oplus c$. The value of $r$ is concatenated to the beginning of our ciphertext, and $G$ is fully available to our adversary (Kerchkoff's Principle states only the key may be private). Our adversary knows both $G(r)$ and $c$, and so can find any $m$.  

Since a cpa-capable adversary has all the capabilites of an eav-capable adversary, a lack of eav-security implies the scheme is **not** cpa-secure either.

**b)** This scheme uses the pseudorandom function $F_k$ with input $0^n$ to encrypt a message of length $n$. Using a static input means $F_k$'s range is limited to exactly $|\mathcal{K}|$. The key is chosen from a uniform distribution. This means that for every message $m$ we are choosing from $\mathcal{K}$ with a uniform distrution to produce $c$. Since $|m| = |k| = |c|$, this scheme is equivalent to the one-time pad and is thus eav-secure.  

It is easy to observe that the scheme is not cpa-secure due to it's deterministic nature. If we consider the experiment ${\mathrm{Priv}_k}_{A, \Pi}^{cpa}$ where we encrypt one of two messages, we can show that the adversary can succeed with a probability of 1. First, $A$ provides us with two strings $m_0, m_1$. We choose a bit $b$ at random, then encrypt $m_b$ and pass the resulting ciphertext $c$ to our adversary. Our adversary then outputs a bit $b'$. If $b' = b$, ${\mathrm{Priv}_k}_{A, \Pi}^{cpa} = 1, \mathrm{else}\;0$. $F_k(0^n)$ produces a one to one correspondence between any $m$ and $c$ . With access to an oracle which will take any $m'$ of $A$'s choosing and produce the corresponding $c'$, $A$ can simply ask the oracle to encrypt $m_0$ to produce $c_0$. If $c_0 = c$, $b' = 0$. Otherwise, $b = 1$.
\[
\begin{align}
c &:= m_b \oplus F_k(0^n)\\
c_0 &:= m_0 \oplus F_k(0^n)\\
c_1 &:= m_1 \oplus F_k(0^n)\\
c_0 &= c \implies m_b = m_0, b\prime = 0\\
c_1 &= c \implies m_b = m_1, b\prime = 1\\\\
&Pr[{\mathrm{PrivK}}_{A, \Pi}^{cpa}(n) = 1] = 1
\end{align}
\]
Therefore the scheme is **not** cpa-secure.  

**c)** To encrypt $m \in \{0, 1\}^{2n}$, parse $m$ as $m_1 || m_2$ with $|m_1| = |m_2|$, then choose uniform $r \in \{0, 1\}^n$ and send $\langle r, m_1 \oplus F_k(r), m_2 \oplus F_k(r+1) \rangle$  

We begin by splitting the problem in half. That is, we change the scheme to be two separate scheme $\Pi_1$ and $\Pi_2$. Our input becomes messages $m \in \{0, 1\}^n$.
\[
\begin{align}
\Pi_1: &\;\;c := \langle r, m_1 \oplus F_k(r) \rangle\\
\Pi_2: &\;\;c := \langle r, m_2 \oplus F_k(r + 1) \rangle\\
\end{align}
\]
Both of these schemes are equivalent to Construction 3.30 on page 83 of the textbook, and as Theorem 3.31 states, if $F$ is a pseudorandom function, Construction 3.30 is a CPA-secure private-key encryption scheme for messages of length $n$.  

Since neither $c_1$ nor $c_2$ influence the value of the other according to this scheme, we need only show that $r$ will only ever overlap with $r + 1$ with a negligible probability. $r + 1$ is calculated over $\mod(|r|)$ to ensure we can continue to encrypt even when our initial $r$ is chosen to be the maximum possible value. Since $|r| = n$, it is obvious that for any value of $r$, there exists a value of $r + 1$ such that $r \neq r + 1$. This would only be possible if $r$ were a single bit. Therefore, we can safely say that $m_1$ and $m_2$ are entirely independent, and so is the concatenation of the two. As a result, $\Pi$ is cpa-secure.  

Since cpa-security encapsulates eav-security, the scheme is also eav-secure.

######(4)  
Define some adversary $A$ which knows in advance the initialization vector $IV$ that will be used for the second encrypted message. Let $A$ choose two messages $m_1^0, m_1^1$. We pick a value for bit $b$ at random, then encode $m_1 = m_1^b$. The adversary recieves $c$ and outputs a bit $b'$. Our experiment ${\mathrm{PrivK}}_{A, \Pi}^{cpa}(n) = 1$ if $b' = b$, else it outputs 0. In order to be secure, it must hold that
\[
Pr[{\mathrm{PrivK}}_{A, \Pi}^{cpa}(n) = 1] \leq \frac{1}{2} + \mathrm{negl}(n)
\]
They observe the first ciphertext to be $\langle IV, c_1, .. c_i \rangle$ \. The attacker then requests an encryption of a second message $m_{i+1}, .. m_j$ where $m_{i+1} = IV \oplus m_1^0 \oplus (IV + 1)$ and observes a second ciphertext $\langle c_{i+1}, .. c_j \rangle$.
\[
\begin{align}
\mathrm{Let}\; m_1 &= m_0^1\\
c_1 &= F_k(IV \oplus m_1^0)\\
\mathrm{Choose}\;m_{i+1} &= IV \oplus m_1^0 \oplus (IV + 1)\\
c_{i+1} &= F_k(m_{i + 1} \oplus (IV + 1))\\
&= F_k(IV \oplus m_1^0)\\
&= c_1
\end{align}
\]
The above holds true if and only if $m_1$ in the original encrypted message is equal to $m_1^0$. There are only two possibilities for the value of $m_1$. Therefore, if $m_{i+1} \neq c_1$, then $m_1 = m_1^1$. This means that
\[
Pr[{\mathrm{PrivK}}_{A, \Pi}^{cpa}(n) = 1] = 1
\]
And the scheme is **not** cpa-secure.

######(5)
**CBC**

**OFB**

**CTR**

######(6)
To prove that these schemes are secure, we must prove that $F_k$ is indistinguishable from a purely random function. Fix a PPT adversary $A$ and let $q(n)$ be the polynomial upper bound on the number of queries that $A$ makes to an encryption oracle. If we let $\widetilde{\Pi}$ represent an encryption scheme that is identical to $\Pi$, but uses a truly random function $f$ in place of $F_k$, we must show that there is a negligible function such that
\[
|\mathrm{Pr}[{\mathrm{PrivK}}_{A, \Pi}^{cpa}(n) = 1] - \mathrm{Pr}[{\mathrm{PrivK}}_{A, \widetilde{\Pi}}^{cpa}(n) = 1]| \leq \mathrm{negl}(n)
\]
We use $A$ to construct a distinguisher $D$ whose goal it is to determine whether a function $F$ is pseudorandom or random. $D$ is given oracle access to some function $O$, and $D$ emulates experiment $\mathrm{PrivK}^{cpa}$ for $A$. If $A$ succeeds then $D$ guesses that its oracle must be a pseudorandom function. If $A$ fails, $D$ guesses that the oracle must be a truly random function.  

$D$ runs $A$. Whenever $A$ queries its oracle on a message, $D$ chooses a uniform $r \in \{0, 1\}^n$ and queries $O(r)$ to produce $y$. $D$ then returns the ciphertext $\langle r, y \oplus m \rangle$ to $A$.  

When $A$ outputs $m_0, m_1$, choose a uniform bit and query $O(r)$ to obtain a response $y$. $D$ then returns the challenge ciphertext $\langle r, y \oplus m_b \rangle$ to $A$. Continue answering oracle queries of $A$ until $A$ outputs a bit $b'$. Output 1 if $b' = b$, and 0 otherwise.  

$D$ runs in polynomial time since $A$ does. If $D$'s oracle is a pseudorandom function, then the view of $A$ when run as a subroutine of $D$ is distributed identically to the view of $A$ in the experiment
