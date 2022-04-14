require 'socket'

# server settings
port = 3389
server = TCPServer.open('localhost',port)

# HTTP server object
class HTTPServer
  def initialize(session,request)
    @session = session
    @request = request
  end
  
  # load the entire filename of the input file, or sample.html if not specified
  def get_full_path
    filename = @request =~ /^GET\s\/+(\S+)/i ? $1 : ""
    if filename == ""
      filename = "sample.html"
    end
    filename = File.expand_path(filename,@defaultPath)
    return filename
  end
  
  def serve
    @fullPath = get_full_path
    src = nil
    begin
      if File.exists?(@fullPath) and File.file?(@fullPath)
        
        if @fullPath.index('') == 0
          content_type = get_content_type(@fullPath)
          @session.print "HTTP/1.1 200/OK\r\nContent-type: #{content_type}\r\n\r\n"
          src = File.open(@fullPath,"rb")
          while(not src.eof?)
            buffer = src.read(256)
            @session.write(buffer)
          end
        src.close
        src = nil
        else
          # should send 403 Forbidden Access
          @session.print "HTTP/1.1 404/Object Not Found\r\nContent-type: text/html\r\n\r\n"
          @session.print "<html> <head> <title> Not Found </title> </head> <body> Not Found </body> </html>"
        end
      else
          @session.print "HTTP/1.1 404/Object Not Found\r\nContent-type: text/html\r\n\r\n"
          @session.print "<html> <head> <title> Not Found </title> </head> <body> Not Found </body> </html>"
      end
    ensure
      src.close unless src == nil
      @session.close
    end
  end
end

# start server, continually runs
loop do
  session = server.accept
  request = session.gets
  # multi-thread/client support
  Thread.start(session,request) do |session,request|
    HTTPServer.new(session,request).serve
  end
end
