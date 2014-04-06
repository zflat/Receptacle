#!/usr/bin/env ruby

require 'socket'
sock = TCPSocket.new('localhost', 3333)
sock.write 'SimpleForm'
sleep(0.5)
sock.close

