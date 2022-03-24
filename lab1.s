    AREA ARMex,CODE,READONLY
	ENTRY   

start
	MOV r0, #0   
	MOV r1, #0xf7000000   
	MOV r2, #0   
	MOV r3, #0x9000000   
	ADDS r5,r1,r3   
	ADC r4,r0,r2   
stop

    END
