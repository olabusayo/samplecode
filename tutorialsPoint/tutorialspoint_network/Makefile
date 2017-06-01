objects = client server tcp
implFiles = client.c server.c Utils.c

tcp: $(implFiles)
	gcc -o client client.c Utils.c
	gcc -o server server.c
#gcc -o tcp $(implFiles)

.PHONY : clean
clean:
	rm $(objects)
