import serial
import time
from ctypes import c_uint32 as uint32_t


PORT_NAME = 'COM3'
FILE_NAME = 'this.txt'


# I like this
ser = serial.Serial(PORT_NAME, baudrate=115200, write_timeout=1.000)
ser.flushInput()
ser.flushOutput()


def getInstruction():
    pass
    '''
    Receive a byte array from Serial
    Bitshift left by 24, 16, 8, 0
    Actually I really only need to read in a 16 bit since there are only 15 controls
    '''
    # instruction = binToDec()
    # sendInstruction(instruction)


# Needs param of binary number to convert, a 32 bit binary number, a bytearray()
def binToDec():
    # sendInstruction()
    pass


# Needs param of the instruction to send, an integer
def sendInstruction(instruction):
    pass


def sendConfig():
    with open('this.txt', 'r') as my_file:
        while True:
            line = my_file.readline().strip()  # Reads line without newline character

            if not line:
                break

            ser.write(line.encode('utf-8'))

            new_read = ser.read()
            print(new_read)

            time.sleep(0.500)


if __name__ == "__main__":
    # Should clear the input buffer
    while ser.available() == 0:
        pass

    sendConfig()

    '''
    while True:
        if Serial.available() > 0:
            getInstruction()
            
    '''
    '''
    Maybe a try-except thing waiting for the file
    '''


