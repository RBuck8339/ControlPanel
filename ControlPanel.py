import serial
import time
import socket


# Wanda Setup
PRINT_SENSORS_COMMAND = 0x55000000
ADD_SENSOR_COMMAND = 0xCF000000
wandaSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    wandaSocket.connect(('192.168.1.10', 35912))
except Exception as e:
    print(f"Failed to connect: {e}")
    exit(1)

# End Wanda Setup


# Serial Setup
PORT_NAME = 'COM3'
FILE_NAME = 'this.txt'

ser = serial.Serial(PORT_NAME, baudrate=115200, write_timeout=1.000)
ser.flushInput()
ser.flushOutput()

# End Serial Setup

instruction = 0


def sendToWanda(number: int):
    # wandaSocket.sendall(number.to_bytes(length=4, byteorder="little", signed=False))  # Does this send as hex?
    # Send Hex: 'BC--' bitwise | with it

    '''
    31 - 24 is BC
    14 - 0 will just be state of buttons(on or off)
    Just waste the rest of them
    '''



def bitFlip(button_state: int, bits: int):
    return (button_state ^ (1 << bits))


def waitInstruction():
    global instruction
    while True:
        instruction_code = ser.readline().decode('UTF-8').strip()
        if instruction_code != "":  # Test this line
            if instruction_code == "empty":
                pass
            # Gotta Test
            elif instruction_code == "fill":
                instruction ^= bitFlip(1, 0)
                print(instruction)
                sendToWanda(instruction)
            elif instruction_code == "vent":
                pass
            # Continue this pattern



def sendConfig():
    with open('OLED.txt', 'r') as f:
        [ser.write(line.encode()) for line in f.readlines()]  # Line is stripped in the arduino IDE
    f.close()


def main():
    while True:
        var = ser.readline().decode('UTF-8').strip()
        if var == "READY":
            break
    sendConfig()
    waitInstruction()


if __name__ == '__main__':
    main()




# var = ser.readline().decode('UTF-8').strip()