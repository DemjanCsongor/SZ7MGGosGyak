#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#define MSGKEY 654321L

struct msgbuf{
    long mtype;
    char mtext[512];
}sndbuf,*msgp;

struct rmsgbuf{
    long mtype;
    char mtext[512];
}rcvbuf, *rmsgp;

struct msqid_ds ds, *buf;

int main()
{
    pid_t pid;
    int msgid;
    key_t key;
    int mtype,msgflg;
    int rtn, msgsz;
    key = MSGKEY;
    int count = 0;
    msgflg = 00666 | IPC_CREAT | MSG_NOERROR;
    msgid = msgget(key,msgflg);
    if(msgid == -1){
        perror("system call failed!");
    }
    pid = fork();
    if(pid==0){
        msgp = &sndbuf;
        msgp->mtype = 1;
        printf("Az msgid %d, %x : \n",msgid,msgid);
        while(1){
            count++;
            printf("Kérem az üzenetet: ");
            gets(msgp->mtext);
            msgsz = strlen(msgp->mtext)+1;
            rtn = msgsnd(msgid,(struct msgbuf *) msgp,msgsz, msgflg);
            printf("\nAz %d. msgsnd visszaadott %d-t", count,rtn);
            printf("\nA kiküldött üzenet: %s",msgp->mtext);
            int value = strcmp(msgp->mtext,"exit");
            printf("\n");
            if(value == 0) break;
        }
    }
    else{
        pid = wait(0);
        rmsgp = &rcvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;
        rtn = msgctl(msgid,IPC_STAT,buf);
        printf("\nAz üzenetek száma: %d",buf->msg_qnum);

        while(buf->msg_qnum){
            rtn = msgrcv(msgid,(struct msgbuf *)msgp,msgsz,mtype,msgflg);
            printf("\nA rtn: %d a vett üzenet: %s\n",rtn,msgp->mtext);
            rtn = msgctl(msgid,IPC_STAT,buf);
    }
    }

    return 0;
}
