import mysql.connector
import socket
import sys
import struct




#enabling connection to MySQL database
mydb = mysql.connector.connect(
  host="192.168.86.246",
  user="testuser",
  password="testpass",
  #database="test"
)


# Get the IP address
hostname = socket.gethostname()
ip_address = socket.gethostbyname(hostname)
print("IP Address:", ip_address)







# Create a socket object
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
serverAddress = ('localhost', 1030)  # Use the same port number and server address as in the C++ program
clientSocket.connect(serverAddress)

#Receive the string data from the server until the delimiter is encountered
messageData = b''
while True:
    data = clientSocket.recv(1024)  # Adjust the buffer size as per your requirements
    if not data:
        break
    messageData += data
    if b'\n' in data:
        break

# Process the received data
message = messageData.decode().rstrip('\n')
print("Received data:", message)

#Close the socket
clientSocket.close()





#mycursor = mydb.cursor()





