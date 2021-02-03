require 'socket'

s = TCPSocket.new "127.0.0.1", 8080

s.write("/home/kali/Documents/github/server-client-example-sys-socket.h/source/Multithread server/#{ARGV[0]}.txt")

s.each_line do |line|
    puts line
end

s.close