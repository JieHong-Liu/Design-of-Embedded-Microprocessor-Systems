	AREA Matrix, CODE, READONLY ; mark first instruction
	ENTRY
start
;====write your code here=====
;=======================
; multiple a and b to c;

	ldr r0,=MatrixA;
	ldr r1,=MatrixB;
	ldr r2,=MatrixC;

	mov r6,#0;//counter i
	mov r7,#0;//counter j
	mov r8,#0;//counter k

	mov r9,#0;//tmp register.
	mov r10,#0; // product register.
	
	mov r11,#0; address register for a
	mov r3, #0; address register for b
	mov r4, #0; address register for c.
	mov r5, #3;
	mov r13,#2;
	mov r12,#4; byte length
	
loop1
	mov r7,#0;				
loop2
	mov r9,#0;
	mov r8,#0;
loop3
	
	mul r11,r6,r5;	// matrix A
	add r11,r11,r8;
	ldr r11,[r0,r11];

	mul r3,r8,r13;	// matrix b
	add r3,r3,r7;
	ldr r3,[r1,r3];

	mla r9,r11,r3,r9;



	add r8,r8,#4;
	cmp r8,#12;	
	bne loop3;

	mul r4,r6,r13;	// matrix c
	add r4,r4,r7;
	str r9,[r2,r4];
		
	

	add r7,r7,#4;
	cmp r7,#8;
	bne loop2;
	
	add r6,r6,#4;
	cmp r6,#8;
	bne loop1;
	

stop
 	AREA Data, DATA, READWRITE
MatrixA 	dcd 1,2,3
			dcd 4,5,6

MatrixB 	dcd 1,4
			dcd 2,5
			dcd 3,6

MatrixC 	dcd 0,0
			dcd 0,0
	


	END ; Mark end of file
