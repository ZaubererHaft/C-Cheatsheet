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
#code section of asm
.text

addVariables:
    ADD RDI, RSI
    MOV RAX, RDI 
    RET
