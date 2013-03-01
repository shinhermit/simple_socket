inc=./headers
inc_path=-Iheaders -I../inc
src = ./sources
obj=../obj
cc=gcc
flags=-Wall -Wextra -g
cmd=$(cc) $(flags) $(inc_path) -c $(src)/$@.c; mv $@.o $(obj)
cmd_exe = $(cc) $(flags) $(inc_path) $(src)/$@.c $(obj)/* -o $@.out

calculus:
	$(cmd)

CalculusClient:
	$(cmd)

CalculusServer:
	$(cmd)

### execs
rpc_client:
	$(cmd_exe); mv $@.out ../

rpc_server:
	$(cmd_exe); mv $@.out ../

clean:
	rm -f *~ *# *.out
	rm -f $(inc)/*~ $(inc)/*# $(inc)/*.out
	rm -f $(src)/*~ $(src)/*# $(src)/*.out
	rm -f $(obj)/*
