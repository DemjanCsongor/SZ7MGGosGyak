#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main()
{
    int shmid;
    int rtn;
    int cmd;
    key_t key;
    int size = 512;
    int shmflg;
    pid_t pid;
    key = SHMKEY;
    struct vmi {
	int  hossz;
	char szoveg[512-sizeof(int)];
    } *segm;
    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;


    pid = fork();
    if(pid==0){
        shmflg = 0;
        if((shmid=shmget(key,size,shmflg))< 0){
        printf("\nNincs meg szegmens!");
        shmflg = 00666 | IPC_CREAT;
        if((shmid=shmget(key,size,shmflg))<0){
            perror("\nSikeretelen shmget system call!");
            exit(-1);
        }
    } else printf("Már van szegmens!");
    }
    else{
        pid = wait(0);
        shmflg = 0;
        if ((shmid=shmget( key, size, shmflg)) < 0) {
            perror("\n Az shmget system-call sikertelen!");
            exit(-1);
        }
        shmflg = 00666 | SHM_RND;
        segm = (struct vmi *)shmat(shmid, NULL, shmflg);
        if (segm == (void *)-1) {
        perror(" Sikertelen attach");
        exit (-1);
        }

        if (strlen(segm->szoveg) > 0)
        printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);

        printf("\n Uj szoveget kerek!\n");
        gets(segm->szoveg);
        printf("\n Az uj szoveg: %s\n",segm->szoveg);
        segm->hossz=strlen(segm->szoveg);

        shmdt(segm);

        do {
        printf("\n Add meg a parancs szamat ");
        printf("\n 0 IPC_STAT (status) ");
        printf("\n 1 IPC_RMID (torles)   >  ");
        scanf("%d",&cmd);
        } while (cmd < 0 && cmd > 1);

        switch (cmd)
        {
            case 0: rtn = shmctl(shmid, IPC_STAT, buf);
            printf("\n  Segm. meret: %d",buf->shm_segsz);
            printf("\n  Utolso shmop-os proc. pid: %d\n ",buf->shm_lpid);
            break;
            case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
            printf("\n Szegmens torolve\n");
            break;
        }
    }
    return 0;
}
