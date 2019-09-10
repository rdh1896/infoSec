import socket
import sys

def get():
    pass

def put():
    pass

def main():
    command = sys.argv[1]
    sourceFile = sys.argv[2]
    destFile = sys.argv[3]
    ip = input("Please enter the File Server's IP address: ")
    port = 3306
    severSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    severSocket.settimeout(0.5)
    ip.connect((ip, port))
    print("Connection Established.")
    if command == "PUT":
        pass
    elif command == "GET":
        pass
    else:
        print("Error: Invalid Command. Please use 'PUT' to place a file, or 'GET' to retrieve one")


