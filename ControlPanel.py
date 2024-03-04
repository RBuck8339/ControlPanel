import serial
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


def sendToLED():
    pass


def sendToWanda(number: int):
    number |= 0xBC000000
    wandaSocket.sendall(number.to_bytes(length=4, byteorder="little", signed=False))


def bitFlip(instruction: int, bits: int):
    return (instruction ^ (1 << bits))


def waitInstruction():
    instruction = 0
    while True:
        instruction_code = ser.readline().decode('UTF-8').strip()
        if instruction_code != "":

            if instruction_code == "Empty":
                continue

            elif instruction_code == "Power":
                instruction = bitFlip(instruction, 13)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nox Fill":
                instruction = bitFlip(instruction, 1)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nox Vent":
                instruction = bitFlip(instruction, 2)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nitrogen Fill":
                instruction = bitFlip(instruction, 3)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nitrogen Vent":
                instruction = bitFlip(instruction, 4)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nitrogen QD":
                instruction = bitFlip(instruction, 5)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Nox QD":
                instruction = bitFlip(instruction, 6)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Air QD":
                instruction = bitFlip(instruction, 7)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Rocket Nox Vent":
                instruction = bitFlip(instruction, 8)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Rocket Nitrogen Vent":
                instruction = bitFlip(instruction, 9)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Enable Fire":
                instruction = bitFlip(instruction, 10)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Fire":
                instruction = bitFlip(instruction, 11)
                sendToWanda(instruction)
                sendToLED()

            elif instruction_code == "Abort":
                instruction = bitFlip(instruction, 12)
                sendToWanda(instruction)
                sendToLED()


def sendConfig():
    with open('OLED', 'r') as f:
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
