class Assembly:
    def compile(self, program: str) -> str:
        compiled_bytes = ''

        for line in program.split('\n'):
            instuction = None
            reg_a = None
            reg_b = None
            data = None

            for i, word in enumerate(line.split(' ')):
                if word:
                    if not instuction and word in list(Assembly.__dict__):
                        instuction = getattr(self, word)
                    elif not reg_a and word.startswith('R'):
                        reg_a = bin(int(word[1]))[2:].zfill(2)
                    elif not reg_b and word.startswith('R'):
                        reg_b = bin(int(word[1]))[2:].zfill(2)
                    elif word.isdigit():
                        data = bin(int(word))[2:].zfill(8)
                    else:
                        raise ValueError(f'Invalid instruction line: {line}, {word}')
            # print(i, reg_a, reg_b, data)
            if instuction:
                bitcode = instuction(reg_a, reg_b)
                # print(bitcode)
                compiled_bytes += hex(int(bitcode, base=2))[2:].zfill(2) + ((' ' + hex(int(data, base=2))[2:].zfill(2) + ' ') if data != None else ' ')

        return compiled_bytes

    def LDR(self, reg_a, reg_b):
        return f'0000{reg_a}{reg_b}'

    def SDR(self, reg_a, reg_b):
        return f'0001{reg_a}{reg_b}'

    def LDD(self, reg_a, reg_b):
        return f'0010{reg_a}00'

    def MOV(self, reg_a, reg_b):
        return f'0011{reg_a}{reg_b}'
    
    def KBD(self, reg_a, reg_b):
        return f'0100{reg_a}00'

    def JMP(self, reg_a, reg_b):
        return f'01010000'

    def JMC(self, reg_a, reg_b):
        return f'01101000'

    def JML(self, reg_a, reg_b):
        return f'01100100'

    def JME(self, reg_a, reg_b):
        return f'01100010'

    def JMZ(self, reg_a, reg_b):
        return f'01100001'

    def CMP(self, reg_a, reg_b):
        return f'0111{reg_a}{reg_b}'
        
    def ADD(self, reg_a, reg_b):
        return f'1000{reg_a}{reg_b}'

    def SUB(self, reg_a, reg_b):
        return f'1001{reg_a}{reg_b}'

    def AND(self, reg_a, reg_b):
        return f'1010{reg_a}{reg_b}'

    def OR(self, reg_a, reg_b):
        return f'1011{reg_a}{reg_b}'

    def XOR(self, reg_a, reg_b):
        return f'1100{reg_a}{reg_b}'

    def NOR(self, reg_a, reg_b):
        return f'1101{reg_a}{reg_b}'

    def HLT(self, reg_a, reg_b):
        return f'11100000'

    def NOP(self, reg_a, reg_b):
        return f'11111111'
