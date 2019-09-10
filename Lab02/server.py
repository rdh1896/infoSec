import sys
import socket
import threading

ip = "127.0.0.1"  # The IP address that our server will listen on
port = 3306  # The port that our server will listen on


def conn_handler(conn, address):
    print(f"{address} has connected")


def main():
    # socket.socket() = socket class constructor
    # socket.AF_INET = IPv4 will be used
    # socket.SOCK_STREAM = TCP will be used (socket.SOCK_DGRAM = UDP)

    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # srv.bind() takes a tuple as an arg
    # first element of the tuple is a string (IP or hostname)
    # second element is an int (port number)
    srv.bind((ip, port))

    # Number of concurrent connections allowed
    srv.listen(1)

    while True:
        # srv.accept() is a blocking call, waits for a connection
        print("Waiting for a client...")
        clientSock, address = srv.accept()
        handler = threading.Thread(target=conn_handler, args=(clientSock, address))
        handler.start()


main()