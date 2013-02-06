inc = inc
src = src
obj = obj
cc = gcc
flags = -Wall -Wextra -g
cmd_exe = $(cc) $(flags) -I$(inc) $(src)/$@.c $(obj)/* -o $@.out
cmd = $(cc) $(flags) -I$(inc) -c $(src)/$@.c; mv $@.o $(obj)

SocketUtility:
	$(cmd)

DatagramPacket:
	$(cmd)

DatagramSocket:
	$(cmd)

StreamSocket:
	$(cmd)

ServerSocket:
	$(cmd)

all_datagram: SocketUtility DatagramPacket DatagramSocket

all_stream: SocketUtility StreamSocket ServerSocket

all_classes:  SocketUtility DatagramPacket DatagramSocket StreamSocket ServerSocket

Test:
	$(cmd_exe)

dgrm_server: all_datagram
	$(cmd_exe)

dgrm_client: all_datagram
	$(cmd_exe)

dgrm_example: dgrm_client dgrm_server
	$(cmd_exe)

tcp_client: all_stream
	$(cmd_exe)

tcp_server: all_stream
	$(cmd_exe)

tcp_example: tcp_client tcp_server
	$(cmd_exe)

ChatServer: all_stream
	$(cmd_exe)

ChatClient: all_stream
	$(cmd_exe)

clean:
	rm -f *~ *# *.out
	rm -f $(inc)/*~ $(inc)/*# $(inc)/*.out
	rm -f $(src)/*~ $(src)/*# $(src)/*.out
