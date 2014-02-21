#!/usr/bin/env ruby

require 'socket'
sock = TCPSocket.new('localhost', 3333)
sock.write 'TESTC'
# puts sock.read(5) # Since the response message has 5 bytes.
sock.close

