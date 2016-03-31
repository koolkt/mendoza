import unittest
import subprocess
import socket
from time import sleep

TESTMSG = 'Hello World'
MSGLEN = len(TESTMSG)
PORT = 3000

# 220
# EHLO [127.0.0.1]
# 502
# HELO [127.0.0.1]
# 250
# MAIL FROM:<kool@kool.com>
# 250
# RCPT TO:<hello@test.com>
# 250
# DATA
# 354
# From: k <kool@kool.com>
# Subject: test
# To: hello@test.com
# Message-ID: <56FB5238.1050008@kool.com>
# Date: Wed, 30 Mar 2016 06:12:40 +0200
# User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101
#  Thunderbird/38.7.1
# MIME-Version: 1.0
# Content-Type: text/plain; charset=utf-8; format=flowed
# Content-Transfer-Encoding: 7bit

# Hello World
# .
# 250
# QUIT

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
        sleep(.3)
        chunks = []
        self.sock.setblocking(False)
        chunk = self.sock.recv(4096)
        res = chunk.decode()
        chunks.append(res)
        if res[-2] != '\r':
            chunk = self.sock.recv(4096)
            res = chunk.decode()
            chunks.append(res)
        if chunk == b'':
            raise RuntimeError("socket connection broken")
        return ''.join(chunks)


class TestBasicSmtp(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        print("Seting up..")
        subprocess.Popen(['./tests/test_smtp/bin/test2', str(PORT)], stdout=subprocess.DEVNULL)
        sleep(.1)

    @classmethod
    def tearDownClass(cls):
        subprocess.run(['/bin/bash', '-c', 'killall test2'], stdout=subprocess.DEVNULL)

    def setUp(self):
        self.s = MySocket()
        self.s.connect('localhost', PORT)

    def tearDown(self):
        self.s.close()

    def assertEqualRcv(self,string):
        res = self.s.myreceive()
        self.assertEqual(res, string)

    def assertOkRes(self):
        self.assertEqualRcv('250 localhost Ok\r\n')

    def test_server_send_mail(self):
        pass
        #self.assertEqualRcv('220 localhost ESMTP Mendoza\r\n')
        # self.s.mysend('HELO [127.0.0.1]\r\n')
        # self.assertOkRes()
        # self.s.mysend('MAIL FROM: thor@viking.net\r\n')
        # self.assertOkRes()
        # self.s.mysend('RCPT TO: leopold@kwame.mendoza.epitech.eu\r\n')
        # self.assertOkRes()
        # self.s.mysend('DATA\r\n')
        # self.assertEqualRcv('354 End data with <CR><LF>.<CR><LF>\r\n')
        # self.s.mysend('Hello World\n\r\n.\r\n')
        # self.assertOkRes()
        # self.s.mysend('QUIT\r\n')
        # self.assertEqualRcv('221 Bye\r\n')

if __name__ == '__main__':
    unittest.main()
