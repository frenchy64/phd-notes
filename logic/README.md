# Biconditional

A biconditional is an expression of two subexpressions that is true if both are always of equivalent boolean value.
aka. if and only if, iff

```
a | b | a iff b
---------------
1 | 1 | 1
0 | 1 | 0
1 | 0 | 0
0 | 0 | 1
```

# Law of excluded middle

The assumption that for any sentence p, either p or ~p is true.
A characteristic of classical logics like the sequent calculus.

Intuitionistic logics break the law of excluded middle (eg. Coq is based on intuitionistic logic).

# Tautology

A forumla that is always true, in any possible environment.

# Bottom

We can represent bottom in calculus' that lack it with `p ^ ~p`.

# Disjunction

A disjunction just encodes that two expressions cannot both be simultaneously false.

```
a v b == ~(~a ^ ~b)
```

Truth table:

```
a | b | a v b
-------------
1 | 1 | 1
0 | 1 | 1
1 | 0 | 1
0 | 0 | 0
```

# Implication

An implication is like an if-then statement.
We can expand it using AND and NOT: it is NOT possible for the conditional to be true while the consequent is false.

```
a -> b == ~a v b == ~(a ^ ~b)
```

Use modus ponens to eliminate an implication.

```
a -> b    a
----------- (Modus ponens)
    b
```

