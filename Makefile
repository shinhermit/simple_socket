inc = inc
src = src
obj = obj
rpc=computing_server
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

all_sock_classes:  SocketUtility DatagramPacket DatagramSocket StreamSocket ServerSocket

### computing_server

calculus:
	cd $(rpc); make $@

CalculusClient:
	cd $(rpc); make $@

CalculusServer: calculus
	cd $(rpc); make $@

all_calculus: CalculusClient CalculusServer

### execs
Test:
	 $(cc) $(flags) -I$(inc) $(src)/$@.c -o $@.out

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

rpc_server: all_stream CalculusServer
	cd $(rpc); make $@

rpc_client: all_stream CalculusClient
	cd $(rpc); make $@

clean:
	rm -f *~ *# *.out
	rm -f $(inc)/*~ $(inc)/*# $(inc)/*.out
	rm -f $(src)/*~ $(src)/*# $(src)/*.out
	rm -f $(obj)/*
	cd ./computing_server; make clean
