#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/stat.h>


  
int main(int argc[], char* argv[]) 
{ 


    // INPUT ARGUMENTS
    if (argc > 1)
    {
        printf("ip = %s\nfile = %s\n\n", argv[1], argv[2]);
    }
    else
    {
        printf("missing input data...\n");
        return -1;       
    }

    //SOCKET CREATE
    int sd, cd; 
    struct sockaddr_in addr, cli; 
    
    sd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sd == -1) 
    { 
        printf("socket creation failed...\n"); 
        return -1; 
    } 
    else
        printf("socket successfully created...\n");


    // ADDR CREATE
    bzero(&addr, sizeof(addr));
  
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = inet_addr(argv[1]); 
    addr.sin_port = htons(724); 
  

    // CONNECT
    if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0) 
    {
        printf("connection with the server failed...\n"); 
        return -1; 
    } 
    else
        printf("connected to the server..\n"); 


    // TRANSFER
    FILE* file;
    file = fopen(argv[2], "rb" );
    

    uint8_t byte[256];
    uint8_t size_file[4];
    uint8_t size_name[4];
    uint32_t size, k, l, n;
    int i; 

    // 1) SIZE OF NAME //////////////////////////////////

    size = strlen(argv[2]);

    n = size;

    for (i = 0; i < 4; i++)
    {
        size_name[i] = size % 256;
        size = size / 256;
    }

    write(sd, size_name, 4);

    printf("send info about name of file = %d byte...\n", n);


    // 2) SIZE OF DATA //////////////////////////////////
    struct stat f;
    stat(argv[2], &f);

    size = f.st_size;

    k = size;
    l = size;

    for (i = 0; i < 4; i++)
    {
        size_file[i] = size % 256;
        size = size / 256;
    }

    write(sd, size_file, sizeof(size_file));

    printf("send info about size of file = %d byte...\n", k);

    // 3) NAME TRANSFER //////////////////////////////////

    char name_file[n + 1];
    bzero(name_file, n);

    for (i = 0; i < n; i++)
    {
        name_file[i] = argv[2][i];
    }

    name_file[n] = '\0';

    write(sd, name_file, n );

    printf("send name of file = %s...\n", name_file);


    // 4) FILE TRANSFER //////////////////////////////////
    printf("dowload start...\n");

    for (;;) {
        
        bzero(&byte, sizeof(byte)); 

        for(int i = 0; i < 256; i++)
        {  
            byte[i] = fgetc(file);

            k--;

            if (k == 0)
                break;
        }


        write(sd, byte, sizeof(byte));

        if (k == 0)
        {
            printf("download end...\n");
            printf("send byte = %d...\n", l);

            break;
        }

        bzero(&byte, sizeof(byte)); 

    } 
    
    fclose(file);
    close(sd); 
} 