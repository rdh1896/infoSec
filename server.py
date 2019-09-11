"""
Name: Russell Harvey <rdh1896@rit.edu>
File: server.py
Assignment: Lab 02
"""

import sys
import socket
import threading

ip = "127.0.0.1" #IP address the server is listening on
port = int(sys.argv[1]) #Port the server is listening on

def conn_handler(conn, address):
    """
    Simply prints who has connected to the server.
    (This is leftover code from the live code session in
    class I decided to incorporate.)
    :param conn: clientSock
    :param address: address
    :return:
    """
    print(f"{address} has connected")

def main():
    """
    Waits for a client to connect, then either gets or places files for the
    client based on the command issued.
    :return: None
    """
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    srv.bind((ip, port))

    srv.listen(1)

    while True:
        print("Waiting for a client...")
        clientSock, address = srv.accept()
        handler = threading.Thread(target=conn_handler, args=(clientSock, address))
        handler.start()
        data = clientSock.recv(1024).decode()
        if data == "PUT":
            info = clientSock.recv(1024)
            if info == "Error: No such file exists.":
                break
            fileName = clientSock.recv(1024)
            file = open(fileName, "wb")
            file.write(info)
            file.close()
        else:
            info = clientSock.recv(1024)
            fileName = info.decode()
            try:
                file = open(fileName, "rb")
            except FileNotFoundError:
                msg = "Error: File not found."
                clientSock.send(msg.encode())
                break
            file_data = file.read(1024)
            clientSock.send(file_data)
        clientSock.close()
        break


main()