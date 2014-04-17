#!/usr/bin/env ruby

require 'socket'
sock = TCPSocket.new('localhost', 3344)
sock.write ARGV[0]
sleep(0.5)
sock.close

