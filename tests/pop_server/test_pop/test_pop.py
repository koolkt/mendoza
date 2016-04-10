import unittest
import subprocess
import socket
from time import sleep

TESTMSG = 'Hello World'
MSGLEN = len(TESTMSG)
PORT = 3001

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
        sent = self.sock.send(str.encode(msg))
        if sent == 0:
            raise RuntimeError("socket connection broken")

    def myreceive(self):
        chunks = []
        self.sock.setblocking(False)
        chunk = self.sock.recv(4096)
        if chunk == b'':
            raise RuntimeError("socket connection broken")
        res = chunk.decode()
        chunks.append(res)
        if res[-2] != '\r':
            chunk = self.sock.recv(4096)
            res = chunk.decode()
            chunks.append(res)
        return ''.join(chunks)


class TestBasicSmtp(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        subprocess.Popen(['./tests/pop_server/test_pop/bin/test_pop_protocol', str(PORT)]# , stdout=subprocess.DEVNULL
        )
        sleep(.1)

    @classmethod
    def tearDownClass(cls):
        subprocess.Popen(['/bin/bash', '-c', 'killall test_pop_protocol'], stdout=subprocess.DEVNULL)

    def setUp(self):
        self.s = MySocket()
        self.s.connect('localhost', PORT)

    def tearDown(self):
        self.s.close()

    def assertEqualRcv(self,string):
        sleep(.01)
        res = self.s.myreceive()
        self.assertEqual(res, string)

    def assertOkRes(self):
        sleep(.01)
        self.assertEqualRcv('250 localhost Ok\r\n')

    def test_server_send_mail(self):
        sleep(.01)
        self.assertEqualRcv('220 localhost ESMTP Mendoza\r\n')
        self.s.mysend('HELO [127.0.0.1]\r\n')
        self.assertOkRes()
        self.s.mysend('MAIL FROM: thor@viking.net\r\n')
        self.assertOkRes()
        self.s.mysend('RCPT TO: leopold@kwame.mendoza.epitech.eu\r\n')
        self.assertOkRes()
        self.s.mysend('RCPT TO: leopold@kwame.mendoza.epitech.eu\r\n')
        self.assertOkRes()
        self.s.mysend('DATA\r\n')
        self.assertEqualRcv('354 End data with <CR><LF>.<CR><LF>\r\n')
        self.s.mysend('Hello World\n\r\n.\r\n')
        self.assertOkRes()
        self.s.mysend('QUIT\r\n')
        self.assertEqualRcv('221 Bye\r\n')

if __name__ == '__main__':
    unittest.main()
