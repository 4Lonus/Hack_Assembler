// Valid instructions
@2          // A: numeric address
D=A         // C: dest=comp
@3
D=D+A
@0
M=D
(END)       // L: label
@END        // A: symbol
0;JMP       // C: jump

// Invalid instructions (should be E_INSTRUCTION)
@           // just '@'
@3a         // starts with digit but not all digits
@!bad       // invalid character '!'
(           // just '('
(END        // missing closing ')'
()          // empty label
(123)       // label starts with digit
(END))      // extra ')'
(@)         // invalid symbol '@'