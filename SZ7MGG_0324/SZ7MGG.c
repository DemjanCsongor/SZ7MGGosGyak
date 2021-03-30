#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>


int main()
{
    int fd,ret;
    char buf[32];
    buf[0]=0;

    fd=open("SZ7MGG.txt",O_RDWR);

    if(fd==-1) {
        perror("open() hiba!");
        exit(-1);
    }

    ret=read(fd,buf,32);
    printf("read() olvasott %d byteot, ami a kovetkezo:\n%s",ret,buf);

    ret=lseek(fd,0,SEEK_SET);
    printf("\nlseek() mondja : %d\n",ret);

    ret=write(fd,buf,6);
    printf("write() mondja : %d\n",ret);

    close(fd);

    return 0;
}
