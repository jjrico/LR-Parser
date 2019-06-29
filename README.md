# LR-Parser

This program uses a bottom-up parser using an LR Parse table to evaluate if the input string is approved by the following Context Free Grammar:

E--> E + T

E--> E- T

E--> T

T--> T * F

T--> T / F

T--> F

F--> ( E )

F--> i
