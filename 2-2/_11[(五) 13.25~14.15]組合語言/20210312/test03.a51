;
; �t�X"8��LED(�@��)��ߪO"
;     P0�ұ���8��LED(��l���A:�̥�2�ӫG�F��l6��LED����),�öi��k�۪��ܤ�
;
START:	
	MOV	P0, #0FEH		;
	ORG	0000H			;
LOOP:	MOV	P0, #00000000B	;
	MOV	A,P0			;
	RL	A			;
	MOV	P0,A			;

	ACALL	DELAY			;
	MOV	P0, #11111111B	;
	ACALL	DELAY			;
	AJMP	LOOP			;


DELAY:	MOV	R6, #250	;
DL1:		MOV	R7, #200	;
DL2:		DJNZ	R7, DL2	;
		DJNZ	R6, DL1	;
		RET			;

		END			;
