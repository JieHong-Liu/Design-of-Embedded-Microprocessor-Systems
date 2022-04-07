	AREA Matrix, CODE, READONLY ; mark first instruction
	ENTRY
start
;====write your code here=====
;=======================
; sort the array

	ldr r0,=array;
	ldr r10,=array;
	mov r1,#20; // length-1 of the array, since the bubble sort will index array[length];
	mov r2,#0; // i counter
	mov r3,#0; // j counter
	mov r4,#0; // save the j counter with length - 1- i;
	mov r5,#0; // to read array data in to register.(array[j])
	mov r6,#0; // j+1 counter
	mov r7,#0; // to read array data in to register.(array[j+1])
	mov r8,#4; // to save byte length 4;
	mov r9,#0; // tmp reg to store swap value.;
loop1

	mov r3,#0;
loop2
	ldr r5,[r0,r3]; // read array data into register.
	
	add r6,r3,#4; 	// calculate j+1 into r7
	ldr r7,[r0,r6]; 
	
	
	mov r9,r5; // save r5 into r9;
	cmp r5,r7;
	
	ble no_swap; // no less equal, do swap
	
	str r7,[r0,r3]; // save r7 into array[j], vice versa.

	add r6,r3,#4; // calculate j+1
	str r9,[r0,r6];
no_swap
	
	add r3,r3,#4;
	sub r4,r1,r2; // calculate length - 1 - i(5-i);
	cmp r3,r4;
	bne loop2;
		
	add r2,r2,#4;
	cmp r2,r1;
	bne loop1;
	

stop
 	AREA Data, DATA, READWRITE
array 	dcd 9,3,0,2,7,1



	END ; Mark end of file