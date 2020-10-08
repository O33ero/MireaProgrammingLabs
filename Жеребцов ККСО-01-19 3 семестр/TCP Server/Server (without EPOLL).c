#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <errno.h>
#include <malloc.h>
#include <sys/epoll.h>


int main(int argv[], char* argc[])
{

	int sd, cd;
	struct sockaddr_in addr;
	uint8_t ch;

	//SOCKET CREATE
	sd = socket(AF_INET, SOCK_STREAM, 0);

	if (sd < 0)
	{
		perror("socket");
		return -1;
	}

	// ADDR CREATE
	bzero(&addr, sizeof(addr)); 

	addr.sin_family = AF_INET;
	addr.sin_port = htons(6075);
	addr.sin_addr.s_addr = inet_addr("10.0.2.15");

	// BIND 
	if (bind(sd, (struct sockaddr *) &addr, sizeof(addr)))
	{
		perror("bind");
		close(sd);
		return -1;
	}
	
	// LISTEN
	if (listen(sd, 5))
	{
		perror("listen");
		close(sd);
		return -1;
	}



	






















	// ACCEPT CONNECTION
	cd = accept(sd, NULL, NULL);

	if (cd < 0)
	{
		perror("accept");
		close(sd);
		return -1;
	}


	// TRANSFER

	uint32_t size, size_name, size_file;

	int i;
	uint32_t k;
		

	// 1) SIZE OF NAME //////////////////////////////////

	k = 1;
	size = 0;

	for (i = 0; i < 4; i++)
	{
		read(cd, &ch, 1);

		size = size + ch * k;

		k = k * 256;
	}

	size_name = size;
	printf("received info about name of file = %d byte...\n", size);


	// 2) SIZE OF FILE /////////////////////////////////////

	k = 1;
	size = 0;

	for (i = 0; i < 4; i++)
	{
		read(cd, &ch, 1);

		size = size + ch * k;

		k = k * 256;
	}

	size_file = size;
	printf("received info about size of file = %d byte...\n", size);

	// 3) NAME TRANSFER //////////////////////////////////

	char name_file[size_name + 1];
	bzero(name_file, size_name);

	for (i = 0; i < size_name; i++)
	{
		read(cd, &ch, 1);
		name_file[i] = ch; 
	}

	name_file[size_name] = '\0';

	printf("received name of file = %s...\n", name_file);

	// for (i = 0; i < sizeof(name_file))

	FILE* file;

	file = fopen(name_file, "wb");
	// 4) FILE TRANSFER //////////////////////////////////

	printf("download start...\n");


	while (1)
	{
		read(cd, &ch, 1);

		fputc(ch, file);
		size = size - 1;

		if (size == 0)
		{
			printf("download end...\n");
			printf("received byte = %d...\n", size_file);
			break;
		}

	}

	close(cd);
	close(sd);

	return 0;
}