import unittest
import subprocess
import socket
from time import sleep

TESTMSG = 'Hello World'
MSGLEN = len(TESTMSG)
PORT = 3000

class MySocket:
    """demonstration class only
      - coded for clarity, not efficiency
    """
    def close(self):
        self.sock.close()

    def __init__(self, sock=None):
        if sock is None:
            self.sock = socket.socket(
                socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host, port):
        self.sock.connect((host, port))

    def mysend(self, msg):
        totalsent = 0
        while totalsent < MSGLEN:
            sent = self.sock.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent

    def myreceive(self):
        chunks = []
        bytes_recd = 0
        while bytes_recd < MSGLEN:
            chunk = self.sock.recv(min(MSGLEN - bytes_recd, 2048))
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
        return b''.join(chunks)


class TestStringMethods(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        print("Seting up..")
        subprocess.Popen(["../bin/mendoza_server", str(PORT)], stdout=subprocess.DEVNULL)
        sleep(.3)

    @classmethod
    def tearDownClass(cls):
        subprocess.run(['/bin/bash', '-c', 'killall mendoza_server'], stdout=subprocess.DEVNULL)

    def test_echo(self):
        s = MySocket()
        s.connect('localhost', PORT)
        s.mysend(str.encode(TESTMSG))
        echo_msg  = s.myreceive()
        print(echo_msg)
        s.close()

if __name__ == '__main__':
    unittest.main()
