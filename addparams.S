; Calling Convention x64
; Arguments 1 to 6
; RDI - RSI - RDX - RCX - R8 - R9
; 7 to infinity: stack 7th on [ESP + 0x8] (we save the jump back address)

; caller saved variables
; RAX, RCX, RDX, RSI, RDI, R8, R9, R10, R11
; callee saved
; RBX, R12-R15, RSP

; this assembly file is using NASM instead of GNU assembly (GAS)
; differences: 
; comment: ; instead of #
; global instead of .global
; we don't need intel_syntax noprefix as NASM uses per default intel syntax
; variable initialization with RESB instead of .lcomm
; we need section .data instead of .data
; for more differences view https://developer.ibm.com/articles/l-gas-nasm/ 


; make function globally accessible
global addVariables
global countTo
global sumTo
global halfOf
global thirdOf
global addArray
global toUpper

; unitialized data
section .bss
    buffer RESB 1024

;intialized data
section .data
    table DB 1,2,3,4
    ascii_first_lower_case_letter EQU 97
    ascii_last_lower_case_letter EQU 122
    ascii_diff_lower_upper_case EQU 32
    ascii_nil_character EQU 0

; code section of asm
section .text
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

; SIMD Calling Convention
; XMM0 - XMM7: Parameters
; XMM0 return value
; all registers are caller saved

; convert doubleword integer to scalar single precision floating point value
halfOf:
    CVTSI2SS XMM1, RDI
    MOV RDI, 2
    CVTSI2SS XMM2, RDI
    DIVSS XMM1, XMM2
    MOVSS XMM0, XMM1
    RET

; use SD for double precision
thirdOf:
    CVTSI2SD XMM0, RDI
    MOV RDI, 3
    CVTSI2SD XMM1, RDI
    DIVSD XMM0, XMM1
    RET 

; adds two arrays with one command (SIMD)
addArray:
    XOR RAX, RAX

    JMP l2_cmp
    l2_start:
        MOVDQU XMM0, [RDI + RAX]
        MOVDQU XMM1, [RSI + RAX]
        ADDPS XMM0, XMM1
        MOVDQU [RDI + RAX], XMM0

        ADD RAX, 16
        SUB RDX, 4
    l2_cmp:
        CMP RDX, 0
        JG l2_start

    XOR RAX, RAX
    RET

toUpper:
    XOR RCX, RCX
    XOR RAX, RAX

    l3_cmp:
        MOV AL, BYTE [RDI+RCX]
        CMP AL, ascii_nil_character
        JLE l3_end 
        
        CMP AL, ascii_first_lower_case_letter
        JL l3_continue
        CMP AL, ascii_last_lower_case_letter
        JG l3_continue

        SUB AL, ascii_diff_lower_upper_case
        MOV BYTE [RDI+RCX], AL
    l3_continue:
        INC RCX
        JMP l3_cmp
    l3_end:
        XOR RAX, RAX
        RET