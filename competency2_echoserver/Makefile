executables = client server llw
objFiles = client.o server.o
utilFiles = Utils.c UtilsLinkedList.c
impFiles = Client.c Server.c $(utilFiles)

all: $(impFiles) 
	gcc -Wall -g -o client Client.c $(utilFiles)
	gcc -Wall -g -o server Server.c $(utilFiles)
	
#client.o: Client.c Utils.c UtilsLinkedList.c
#	gcc -Wall -g -o $@ $^
#
#server.o: Server.c Utils.c UtilsLinkedList.c
#	gcc -Wall -g -o $@ $^

llw: LinkedListWrapper.c UtilsLinkedList.c
	gcc -Wall -g -o $@ $^
	
.PHONY : clean
clean:
	rm $(objFiles) $(executables)
