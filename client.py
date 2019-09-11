"""
Name: Russell Harvey <rdh1896@rit.edu>
File: client.py
Assignment: Lab 02
"""

import socket
import sys

def main():
    """
    Establishes a connection with a server then asks user to enter a command.
    User can enter:
    'PUT ./filename.extension ./filename.extension'
        PUT - implies placing a file on the server
        First file name is the file you're placing on the server
        Second file name is what the file will be named on the server after write
    'GET ./filename.extension ./filename.extension'
        GET - implies retrieving a file on the server
        First file name is the file you're getting on the server
        Second file name is what the file will be named on the client after write
    After input, the request is sent to the server and is processed.
    Transferred files will end up in the directory in which the respective Python programs
    are running within.
    :args: [hostname] [port]
    :return: None
    """
    ip = sys.argv[1]
    port = int(sys.argv[2])
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.settimeout(0.5)
    serverSocket.connect((ip, port))
    print("Connection Established.")
    while True:
        data = input("Please enter a command: ")
        command = data.split()
        if command[0] == "PUT":
            fileName = command[1]
            try:
                file = open(fileName, "rb")
            except FileNotFoundError:
                msg = "Error: No such file exists."
                print(msg)
                serverSocket.send(msg.encode())
                break
            serverSocket.send(command[0].encode())
            file_data = file.read(1024)
            serverSocket.send(file_data)
            serverSocket.send(command[2].encode())
        elif command[0] == "GET":
            serverSocket.send(command[0].encode())
            serverSocket.send(command[1].encode())
            file_data = serverSocket.recv(1024)
            if file_data.decode() == "Error: File not found.":
                print("Error: File not found on server.")
                break
            fileName = command[2]
            file = open(fileName, "wb")
            file.write(file_data)
            file.close()
        else:
            print("Error: Invalid Command. Please use 'PUT' to place a file, or 'GET' to retrieve one")
            break

main()


