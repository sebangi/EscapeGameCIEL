# <keyword data-keyword-id="246">Raspberry Pi</keyword> to Arduino I2C Communication
# Python Code
 
import smbus
import time

# Slave Addresses for Arduinos
ARDUINO_1_ADDRESS = 0x09 # I2C Address of Arduino 1
ARDUINO_2_ADDRESS = 0x10 # I2C Address of Arduino 2
 
# Create the I2C bus
I2Cbus = smbus.SMBus(1)

def gererMecanisme(slaveAddress, BytesToSend) :
    bSelect = input("Message à envoyer : ") 
    
    try:
        I2Cbus.write_i2c_block_data(slaveAddress, 0, BytesToSend)
        print("Sent : " + str(slaveAddress) + " the " + str(bSelect))

        # Read a block of 32 bytes from address 9, offset 0
        block = I2Cbus.read_i2c_block_data(slaveAddress, 0, 32)
    
        # Returned value is a list of 32 bytes
        print("receive from " + str(slaveAddress) + " : ")
        print(block)
    except:
        print("I2C failed")

while True:
    gererMecanisme(ARDUINO_1_ADDRESS, [2, 5, 1])
    gererMecanisme(ARDUINO_1_ADDRESS, [3, 5])
    gererMecanisme(ARDUINO_2_ADDRESS, [2, 5, 1])
    gererMecanisme(ARDUINO_2_ADDRESS, [3, 5])

print("FIN")

I2Cbus.close()
    
 
    
