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
        # self.sock.setblocking(False)
        chunks = []
        bytes_recd = 0
        while bytes_recd < MSGLEN:
            chunk = self.sock.recv(min(MSGLEN - bytes_recd, 2048))
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
        return b''.join(chunks)


class TestBasicNetwork(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        print("Seting up..")
        # subprocess.Popen(['bin/test1', str(PORT)], stdout=subprocess.DEVNULL)
        subprocess.Popen(['/bin/bash', '-c', './tests/test_basic_network/bin/test1 '+str(PORT)+
                          ' > tests/test_basic_network/test_log'])
        sleep(.1)

    @classmethod
    def tearDownClass(cls):
        subprocess.run(['/bin/bash', '-c', 'killall test1'], stdout=subprocess.DEVNULL)

    def test_server_rcv(self):
        s = MySocket()
        s.connect('localhost', PORT)
        s.mysend(str.encode(TESTMSG))
        with open('tests/test_basic_network/test_log','r') as f:
            self.assertTrue(TESTMSG in f.read())
        s.close()

    def test_server_send(self):
        s = MySocket()
        s.connect('localhost', PORT)
        s.mysend(str.encode(TESTMSG))
        msg = s.myreceive()
        self.assertEqual(msg.decode(),TESTMSG)
        s.close()

if __name__ == '__main__':
    unittest.main()
