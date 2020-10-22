# Calling Convention x64
# Arguments 1 to 6
# RDI - RSI - RDX - RCX - R8 - R9
# 7 to infinity: stack 7th on [ESP + 0x8] (we save the jump back address)

# caller saved variables
# RAX, RCX, RDX, RSI, RDI, R8, R9, R10, R11
# callee saved
# RBX, R12-R15, RSP

#use intel intel syntax
.intel_syntax noprefix
#make function globally accessible
.global addVariables
.global countTo
.global sumTo
.global halfOf
.global thirdOf
.global addArray
#code section of asm
.text

addVariables:
    ADD RDI, RSI
    MOV RAX, RDI 
    RET

countTo:
    XOR RAX, RAX
    MOV RCX, RDI
    l1:
        INC EAX
    LOOP l1
    RET

sumTo:
    XOR RAX, RAX
    CMP RDI, 0
    l_start:
    JLE l_end
        ADD RAX, RDI
        DEC RDI
        JMP l_start
    l_end:
    RET

#SIMD Calling Convention
#XMM0 - XMM7: Parameters
#XMM0 return value
#all registers are caller saved

#convert doubleword integer to scalar single precision floating point value
halfOf:
    CVTSI2SS XMM1, RDI
    MOV RDI, 2
    CVTSI2SS XMM2, RDI
    DIVSS XMM1, XMM2
    MOVSS XMM0, XMM1
    RET

# use SD for double precision
thirdOf:
    CVTSI2SD XMM0, RDI
    MOV RDI, 3
    CVTSI2SD XMM1, RDI
    DIVSD XMM0, XMM1
    RET 

addArray:
    MOVDQU XMM0, [RDI]
    MOVDQU XMM1, [RSI]

    ADDPS XMM0, XMM1
    MOVDQU [RDI], XMM0
    
    RET
