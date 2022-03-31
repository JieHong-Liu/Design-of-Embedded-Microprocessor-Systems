	AREA Fibon, CODE, READONLY ; name this block of code
	ENTRY ; mark first instruction
start
;====write your code here=====
;=======================
	LDR r1,=Sequence;
	MOV r2,#1;
	STR r2,[r1],#4;
	STR r2,[r1],#4;
	MOV r0,#2;

	MOV r3,#1;
	MOV r4,#1;
Label
	ADD r5,r3,r4;
	STR r5,[r1],#4;
	MOV r3,r4;
	MOV r4,r5;	
	
	ADD r0,r0,#1;
	CMP r0,#10;
	BNE Label;
stop
	AREA data, DATA, READONLY
n1 dcd 1
n2 dcd 1
num dcd 10 ;Number of items
Sequence dcd 0
	END ; Mark end of file