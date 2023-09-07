
|Instruction	|Explanation	|Bitcode	|Description|
|--|--|--|--|
|LDR RA RB			|RA <- RB ADDR|0000RARB	|Read data from RAM from RB address into RA|
|SDR RA RB			|RA -> RB ADDR|0001RARB	|Store data from RA into RAM by RB address|
|LDD RA DATA		|DATA -> RA|0010RA00 DATADATA	|Load data into RA|
|MOV RA RB			|RA <- RB|0011RARB	|Copy data from RB to RA|
|JMPR RA ADDR		|RA ADDR -> IAR|0100RA00	|Jump to instruction in RAM at RA address|
|JMP ADDR			|ADDR -> IAR|01010000 ADDRADDR	|Jump to instruction at ADDR|
|JMC ADDR			|ADDR -> IAR if C|01101000 ADDRADDR	|Jump to ADDR if Carry flag is set|
|JML ADDR			|ADDR -> IAR if L|01100100 ADDRADDR	|Jump to ADDR if Larger flag is set|
|JME ADDR			|ADDR -> IAR if E|01100010 ADDRADDR	|Jump to ADDR if Equal flag is set|
|JMZ ADDR			|ADDR -> IAR if Z|01100001 ADDRADDR	|Jump to ADDR if Zero flag is set|
|ADD RA RB			|RA + RB -> RA|0000RARB		||
|SUB RA RB			|RA - RB -> RA|0000RARB		||
|AND RA RB			|RA and RB -> RA|0000RARB	||
|OR RA RB			|RA or RB -> RA|0000RARB	||
|XOR RA RB			|RA xor RB -> RA|0000RARB	||
|NOR RA RB			|RA nor RB -> RA|0000RARB	||
