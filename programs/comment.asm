// Simple test program for the Hack assembler parser
// Computes R0 = 2 + 3

@2          // A-instruction with inline comment
D=A

@3
D=D+A

@0
M=D         // store result in R0

(END)       // label
@END
0;JMP       // infinite loop

   @5    // indented A-instruction
   D=A   // C-instruction with spaces
   
// full-line comment
   (LOOP)
   @LOOP
   0;JMP