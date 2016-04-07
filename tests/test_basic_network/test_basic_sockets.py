import unittest
import socket
from time import sleep
import subprocess

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
        self.sock.setblocking(False)
        chunks = []
        bytes_recd = 0
        while bytes_recd < MSGLEN:
            chunk = self.sock.recv(min(MSGLEN - bytes_recd, 4096))
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
        return b''.join(chunks)


class TestBasicNetwork(unittest.TestCase):
    def setUp(self):
        self.p = subprocess.Popen(['/bin/bash', '-c', './tests/test_basic_network/bin/test1 '+str(PORT)],
                                  stderr=subprocess.DEVNULL, stdout=subprocess.PIPE, universal_newlines=True)
        sleep(.01)

    def tearDown(self):
        self.p.stdout.close()

    def test_server_rcv(self):
        s = MySocket()
        s.connect('localhost', PORT)
        s.mysend(str.encode(TESTMSG))
        sleep(.005)
        s.close()
        self.p.kill()
        self.assertTrue(TESTMSG in self.p.stdout.read())

    def test_server_send(self):
        s = MySocket()
        s.connect('localhost', PORT)
        s.mysend(str.encode(TESTMSG))
        sleep(.1)
        msg = s.myreceive()
        s.close()
        self.p.kill()
        self.assertEqual(msg.decode(),TESTMSG)

if __name__ == '__main__':
    unittest.main()
