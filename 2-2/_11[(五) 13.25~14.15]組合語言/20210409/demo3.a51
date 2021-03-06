	ORG		000H
	MOV	P0, #00000000B
LOOP:	MOV	P1, #11111110B
	JNB	P2.0, FAL
	JNB	P2.1, SOL
	JNB	P2.2, LAL
	JNB	P2.3, SIL

	MOV	P1, #11111101B
	JNB	P2.0, DO
	JNB	P2.1, RE
	JNB	P2.2, MI
	JNB	P2.3, FA

	MOV	P1, #11111011B
	JNB	P2.0, SO
	JNB	P2.1, LA
	JNB	P2.2, SI
	JNB	P2.3, DOH

	MOV	P1, #11110111B
	JNB	P2.0, REH
	JNB	P2.1, MIH
	JNB	P2.2, FAH
	JNB	P2.3, SOH
	AJMP	LOOP

FAL:	MOV	R6, #175
	ACALL	KEY0
	AJMP	OUTPUT
SOL:	MOV	R6, #156
	ACALL	KEY1
	AJMP	OUTPUT
LAL:	MOV	R6, #139
	ACALL	KEY2
	AJMP	OUTPUT
SIL:	MOV	R6, #124
	ACALL	KEY3
	AJMP	OUTPUT
DO:	MOV	R6, #116
	ACALL	KEY4
	AJMP	OUTPUT
RE:	MOV	R6, #104
	ACALL	KEY5
	AJMP	OUTPUT
MI:	MOV	R6, #92
	ACALL	KEY6
	AJMP	OUTPUT
FA:	MOV	R6, #87
	ACALL	KEY7
	AJMP	OUTPUT
SO:	MOV	R6, #78
	ACALL	KEY8
	AJMP	OUTPUT
LA:	MOV	R6, #69
	ACALL	KEY9
	AJMP	OUTPUT
SI:	MOV	R6, #62
	ACALL	KEYA
	AJMP	OUTPUT
DOH:	MOV	R6, #57
	ACALL	KEYB
	AJMP	OUTPUT
REH:	MOV	R6, #52
	ACALL	KEYC
	AJMP	OUTPUT
MIH:	MOV	R6, #46
	ACALL	KEYD
	AJMP	OUTPUT
FAH:	MOV	R6, #43
	ACALL	KEYE
	AJMP	OUTPUT
SOH:	MOV	R6, #39
	ACALL	KEYF
	AJMP	OUTPUT

KEY0:	MOV	P0, #00000000B
	RET
KEY1:	MOV	P0, #00000001B
	RET
KEY2:	MOV	P0, #00000010B
	RET
KEY3:	MOV	P0, #00000011B
	RET
KEY4:	MOV	P0, #00000100B
	RET
KEY5:	MOV	P0, #00000101B
	RET
KEY6:	MOV	P0, #00000110B
	RET
KEY7:	MOV	P0, #00000111B
	RET
KEY8:	MOV	P0, #00001000B
	RET
KEY9:	MOV	P0, #00001001B
	RET
KEYA:	MOV	P0, #00001010B
	RET
KEYB:	MOV	P0, #00001011B
	RET
KEYC:	MOV	P0, #00001100B
	RET
KEYD:	MOV	P0, #00001101B
	RET
KEYE:	MOV	P0, #00001110B
	RET
KEYF:	MOV	P0, #00001111B
	RET

OUTPUT:	CLR	P2.6
		ACALL	DELAY
		SETB	P2.6
		ACALL	DELAY
		AJMP	LOOP

DELAY:	MOV	B, R6
DL:		MOV	R7, #6
		DJNZ	R7, $
		DJNZ	R6, DL
		MOV	R6, B
		RET

	END

