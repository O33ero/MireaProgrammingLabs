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
	addr.sin_port = htons(724);
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



	// EPOLL INSTANT ///////


	int efd = epoll_create(5);

	struct epoll_event listener;
	listener.events = EPOLLIN;
	listener.data.fd = sd;

	if (epoll_ctl(efd, EPOLL_CTL_ADD, sd, &listener) < 0)
	{
		perror("epoll control error..\n");
		return -1;
	}

	socklen_t client;

	struct epoll_event events[5];
	struct epoll_event connev;
	struct sockaddr_in cliaddr;

	int events_cout = 1;


	while(1)
	{	
		int nfds = epoll_wait(efd, events, 5, 35000);

		if (nfds == 0)
			break;
		for (int i = 0; i < nfds; i++)
		{
			if (events[i].data.fd == sd)
			{
				client = sizeof(cliaddr);
				cd = accept(sd, (struct sockaddr*) &cliaddr, &client);

				if (cd < 0)
				{
					perror("problems with accept..\n");
					continue;
				}


				connev.data.fd = cd;
				connev.events = EPOLLIN | EPOLLOUT;

				if (!epoll_ctl(efd, EPOLL_CTL_ADD, cd, &connev) < 0)
			    {
			     perror("Epoll fd add");
			     close(cd);
			     continue;
			    }

			    events_cout++;
			}
			else
			{
				int cd = events[i].data.fd;

				
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


				FILE* file;

				file = fopen(name_file, "wb");
				// 4) FILE TRANSFER //////////////////////////////////

				printf("download start...\n");


				while (1)
				{
					read(cd, &ch, 1);
					//printf("*** %c *** \n", ch);
					fputc(ch, file);
					size = size - 1;

					if (size == 0)
					{
						printf("download end...\n");
						printf("received byte = %d...\n", size_file);
						break;
					}

				}

				

				fclose(file);
				epoll_ctl(efd, EPOLL_CTL_DEL, cd, &connev);
				events_cout--;
				close(cd);
			}
		}		
	}



	close(cd);
	close(sd);

	return 0;
}