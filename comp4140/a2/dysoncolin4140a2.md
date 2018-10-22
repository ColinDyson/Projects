Colin Dyson - dysonc - 7683407
####COMP 4140 ASSIGNMENT 1

######(1)
Define our encryption scheme as follows: on input of a plaintext message $m$ where $|m| \leq \ell(n)$, where $\ell(n)$ is some polynomial function of $n$:

We pad $m$ to a length of $L = \ell(n) + n$. Generate $r \in \{0, 1\}^{L - |m|}$ where $r$ is chosen from a uniform distribution. Append $r$ to $m$ to create $m'$. Finally, for every $m_i$ of length $n$ in $m$, generate the ciphertext $c_i = m_i \oplus k$ and concatenate the resulting $c_i$.
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
\mathrm{Pr}[{\mathrm{Priv}_k}^{eav}_{A, \Pi} = 1] \leq \frac{1}{2} + \mathrm{negl}(n)
\]
Where $\mathrm{negl}(n)$ is a negligible function of $n$. We observe that for any length of $m$ that $A$ provides, we are padding $m$ to a uniform length of $\ell(n) + n$ with random bits. This makes distinguishing between
And our encryption scheme has indistinguishable encryptions in the presence of an eavesdropper even when messages are not restricted to being equal length.  

######(2)

######(3)  
**a)** The scheme does not have indistinguishable encryptions in the presence of an eavesdropper. If $c = G(r) \oplus m$, then $m = G(r) \oplus c$. The value of $r$ is concatenated to the beginning of our ciphertext, and $G$ is fully available to our adversary (Kerchkoff's Principle states only the key may be private). Our adversary knows both $G(r)$ and $c$, and so can find any $m$.  

Since a cpa-capable adversary has all the capabilites of a eav-capable adversary, a lack of eav-security implies the scheme is not cpa-secure either.

**b)** This scheme uses the pseudorandom function $F_k$ with input $0^n$ to encrypt a message of length $n$. Using a static input means $F_k$ is limited to only have a number of possibly inputs that is exactly equal to $|\mathcal{K}|$.
This means that for every message $m$ we are choosing from $\mathcal{K}$ with a pseudorandom distrution to produce $c$. Assuming some adversary cannot distinguish between our pseudorandom distribution and a purely random one, and since $|m| = |k| = |c|$, this scheme is equivalent to the one-time pad and is thus eav-secure.  

It is easy to observe that the scheme is not cpa-secure due to it's deterministic nature. If we consider the experiment ${\mathrm{Priv}_k}_{A, \Pi}^{cpa}$ where we encrypt one of two messages, we can show that the adversary can succeed with a probability of 1. First, $A$ provides us with two strings $m_0, m_1$. We choose a bit $b$ at random, then encrypt $m_b$ and pass the resulting ciphertext $c$ to our adversary. Our adversary then outputs a bit $b'$. If $b' = b$, ${\mathrm{Priv}_k}_{A, \Pi}^{cpa} = 1, else\;0$. With access to an oracle which will encrypt any message of the adversary's choosing using the same key used to encrypt our original message, $F_k(0^n)$ will result in the same $n$-length value for any encryption by the oracle. Our adversary chooses the values of $m_0$ and $m_1$, and so can simply ask the oracle to encrypt them both to produce $c_O$. $A$ then outputs the bit $b\prime$ such that $\mathrm{Enc}_k(m_b\prime) = c$ where $c$ is the message we encrypted.
\[
\begin{align}
c &:= m_b \oplus F_k(0^n)\\
c_{O_0} &:= m_0 \oplus F_k(0^n)\\
c_{O_1} &:= m_1 \oplus F_k(0^n)\\
c_{O_0} &= c \implies m_b = m_0, b\prime = 0\\
c_{O_1} &= c \implies m_b = m_1, b\prime = 1\\\\
&Pr[{\mathrm{Priv}_k}_{A, \Pi}^{cpa}(n) = 1] = 1
\end{align}
\]
Therefore the scheme is not cpa-secure.  

**c)** To encrypt $m \in \{0, 1\}^{2n}$, parse $m$ as $m_1 || m_2$ with $|m_1| = |m_2|$, then choose uniform $r \in \{0, 1\}^n$ and send $\langle r, m_1 \oplus F_k(r), m_2 \oplus F_k(r+1) \rangle$  
Assume that the encryption scheme is cpa-secure. Let $\widetilde{\Pi}$ be an encryption scheme that is exactly the same as $\Pi = (\mathrm{Gen, Enc, Dec})$ except that a truly random function $f$ is used in place of $F_k$. $\widetilde{\mathrm{Gen}}(1^n)$ chooses a uniform function $f \in \mathrm{Func}_n$, and $\widetilde{\mathrm{Enc}}$ encrypts like Enc except $f$ is used instead of $F_k$.  

Fix an arbitrary PPT adversary $A$, and let $q(n)$ b an upper bound on the number of queries that $A(1^n)$ makes to its encryption oracle. We must first show that
\[
|Pr [{\mathrm{Priv}_k}_{A, \Pi}^{cpa}(n) = 1] - Pr [{\mathrm{Priv}_k}_{A, \widetilde{\Pi}}^{cpa}(n) = 1]| \leq \mathrm{negl}(n)
\]
We prove this by reduction. Use $A$ to construct a distinguisher $D$ for the pseudorandom function $F$. $D$ is given oracle access to some function $\mathscr{O}$ and its goal is to determine whether this funciton is pseudorandom or random. To do this, $D$ emulates experiment $\mathrm{PrivK}^{cpa}$ for $A$ in the manner described below, and observes whether

######(4)  
Define some adversary $A$ which knows in advance the initialization vector $IV$ that will be used for the second encrypted message. Let $A$ choose two messages $m_1^0, m_1^1$. We pick a value for bit $b$ at random, then encode $m_1 = m_1^b$. The adversary recieves $c$ and outputs a bit $b'$. Our experiment ${\mathrm{Priv}_k}_{A, \Pi}^{cpa}(n) = 1$ if $b' = b$, else it outputs 0. In order to be secure, it must hold that
\[
Pr[{\mathrm{Priv}_k}_{A, \Pi}^{cpa}(n) = 1] \leq \frac{1}{2} + \mathrm{negl}(n)
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
Pr[{\mathrm{Priv}_k}_{A, \Pi}^{cpa}(n) = 1] = 1
\]
And the scheme is **not** cpa-secure.

######(5)
**CBC**

**OFB**

**CTR**

######(6)
