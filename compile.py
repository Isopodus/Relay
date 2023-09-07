from assembly import Assembly
import sys

if __name__ == "__main__":
    if len(sys.argv) > 1:
        with open(sys.argv[1], 'r') as file:
            program = file.read()
            assembly = Assembly()
            bytecode = assembly.compile(program)
            print(f"Program size: {len(bytecode.split(' ')) - 1} bytes")
            print(bytecode)
            # for word in bytecode.split(' '):
            #     if word:
            #         print(bin(int(word, 16))[2:])
    else:
        print('No program filename specified!')
