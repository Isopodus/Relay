from assembly import Assembly

program = '''
LDD R0 1
LDD R1 2
LDD R2 3
LDD R3 255
ADD R1 R0
JMC 14
SUB R2 R1
JMZ 15
HLT
MOV R2 R3
ADD R0 R2
JMC 20
HLT 
ADD R1 R1
JME 24
HLT
ADD R1 R0
JML 28
HLT
LDD R3 32
JMPR R3
HLT
LDD R0 63
LDD R1 128
SDR R1 R0
LDR R2 R0
SUB R1 R2
JMZ 42
HLT
LDD R0 9
LDD R1 5
LDD R2 1
AND R0 R1
SUB R0 R2
JMZ 53
HLT
LDD R0 9
LDD R1 6
LDD R2 15
OR R0 R1
SUB R2 R0
JMZ 00
HLT
'''

assembly = Assembly()
bytecode = assembly.compile(program)
print(f"Program size: {len(bytecode.split(' ')) - 1} bytes")
print(bytecode)