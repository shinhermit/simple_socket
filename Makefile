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

Test:
	$(cmd_exe)

serveur:
	$(cmd_exe)

client:
	$(cmd_exe)

example: client serveur
	$(cmd_exe)

clean:
	rm -f *~ *# *.out
	rm -f $(inc)/*~ $(inc)/*# $(inc)/*.out
	rm -f $(src)/*~ $(src)/*# $(src)/*.out
