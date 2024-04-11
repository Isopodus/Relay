class Assembly:
    def compile(self, program: str) -> str:
        byte_idx = -1
        compiled_bytes = ''
        flags = {}

        for line in program.upper().split('\n'):
            instuction = None
            reg_a = None
            reg_b = None
            data = None

            for i, word in enumerate(line.split(' ')):
                if word:
                    if ';' in word:
                        break

                    if not instuction and word in list(Assembly.__dict__):
                        # Get instruction
                        instuction = getattr(self, word)
                        byte_idx += 1
                    elif not reg_a and word.startswith('R'):
                        reg_a = bin(int(word[1]))[2:].zfill(2) # Get RA
                    elif not reg_b and word.startswith('R'):
                        reg_b = bin(int(word[1]))[2:].zfill(2) # Get RB
                    elif word.isdigit():
                        data = bin(int(word))[2:].zfill(8)     # Get word as instruciton data
                        byte_idx += 1
                    elif word.startswith(':'):
                        # Store or get a flag
                        if instuction:
                            # Flag is part of the instruction, put it as is to be replaced later
                            data = word
                            byte_idx += 1
                        else:
                            # Flag is independent, store it as a pointer to the next instruction
                            # If a flag ends with + make it a pointer to the address after the next one
                            flags[word] = byte_idx + (2 if word.endswith('+') else 1)
                    else:
                        raise ValueError(f'Invalid instruction line: {line}, {word}')
            # print(i, reg_a, reg_b, data)
            if instuction:
                bitcode = instuction(reg_a, reg_b)
                # print(bitcode)
                data = hex(int(data, base=2))[2:].zfill(2) if data is not None and data.isdigit() else data
                compiled_bytes += hex(int(bitcode, base=2))[2:].zfill(2) + ((' ' + data + ' ') if data != None else ' ')
        
        # Replace the flags with their appropriate values in code
        # print(compiled_bytes)
        # print(flags)
        for flag in flags.keys():
            # print(flag) 
            # print(compiled_bytes)   
            compiled_bytes = compiled_bytes.replace(flag + ' ', hex(int(flags[flag]))[2:].zfill(2) + ' ')
        if ':' in compiled_bytes:
            colon_idx = compiled_bytes.find(':')
            raise ValueError(f'Missing flag definition: {compiled_bytes[colon_idx:compiled_bytes.find(" ", colon_idx)]}')

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
        return f'00000000'
