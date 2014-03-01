#!/usr/bin/env ruby

require 'socket'
sock = TCPSocket.new('localhost', 3333)
sock.write 'echo01'
# puts sock.read(5) # Since the response message has 5 bytes.
sleep(0.5)
sock.write 'TESTC'
sock.write 'echo01'
sock.close

