from assembly import Assembly
import sys
import serial
import time

if __name__ == "__main__":
    if len(sys.argv) > 1:
        with open(sys.argv[1], 'r') as file:
            ser = serial.Serial('/dev/ttyUSB0', 115200)
            time.sleep(3)

            program = file.read()
            assembly = Assembly()
            bytecode = assembly.compile(program)
            print(f"Program size: {len(bytecode.split(' ')) - 1} bytes")
            
            for word in bytecode.split(' '):
                if word:
                    ser.write(int(word, 16).to_bytes(1, byteorder='big'))
                    ser.read(1)
                    print(word, end=' ')

            ser.close()
            print()
    else:
        print('No program filename specified!')
