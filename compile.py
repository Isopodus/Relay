from assembly import Assembly

program = '''
LDD R0 1
LDD R1 2
LDD R2 3
LDD R3 255
ADD R1 R0
JMC 14
SUB R2 R0
JMZ 15
HLT
MOV R3 R2
LDD R0 1
ADD R0 R2
JMC 22
HLT 
ADD R1 R1
JME 26
HLT
ADD R1 R0
JML 30
HLT
LDD R3 34
JMPR R3
HLT
LDD R0 63
LDD R1 128
SDR R0 R1
LDR R0 R2
SUB R1 R2
JMZ 44
HLT
LDD R0 9
LDD R1 5
LDD R2 1
AND R0 R1
SUB R1 R2
JMZ 55
HLT
LDD R1 6
LDD R2 15
OR R0 R1
SUB R2 R1
JMZ 0
'''

assembly = Assembly()
bytecode = assembly.compile(program)
print(f"Program size: {len(bytecode.split(' '))} bytes")
print(bytecode)