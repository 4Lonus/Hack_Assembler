// Basic test program
// Computes a simple countdown loop

@R0
M=0         // Initialize R0 to 0

@counter    // 'counter' is a new variable
M=1         // Initialize counter to 1

(LOOP)
    @counter
    D=M     // D = counter
    @10
    D=D-A   // D = counter - 10
    @END
    D;JGT   // If counter > 10, jump to END

    @counter
    M=M+1   // counter++
    
    @LOOP
    0;JMP   // Jump to LOOP

(END)
    @END
    0;JMP   // Infinite loop