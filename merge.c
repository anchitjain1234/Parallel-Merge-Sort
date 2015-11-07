//
// Created by anchit on 31/10/15.
//

#include "merge.h"
int length;
void display(int *arr,int length)
{
    int i;
    for(i=0;i<length;i++)
        printf("%d    ",arr[i]);
    printf("\n");
}

void merge(int start,int mid,int end,int *arr)
{
    int *temp1,*temp2,l1,l2,*mod=arr,*t1,*t2;
    l1=mid-start+1;
    l2=end-mid;
    mod=arr+start;

    temp1=(int *)malloc(sizeof(int)*(l1));
    temp2=(int *)malloc(sizeof(int)*(l2));

    t1=temp1;
    t2=temp2;
    if(temp1==NULL || temp2==NULL)
        err("Error in memory allocation\n");

    memcpy(temp1,arr+start,l1*sizeof(int));
    memcpy(temp2,arr+mid+1,l2*sizeof(int));

   printf("\n\nIn merge start=%d end=%d and pid=%d\n",start,end,getpid());
   printf("Initially \n");
   display(arr,length);
//    printf("temp1\n");
//    display(temp1,l1);
//    printf("temp2\n");
//    display(temp2,l2);

    while(l1>0 && l2>0)
    {
        if(*temp1<*temp2)
        {
            *mod=*temp1;
            temp1++;
            l1--;
        }
        else
        {
            *mod=*temp2;
            temp2++;
            l2--;
        }
        mod++;
    }

    if(l1>0)
    {
        while(l1>0)
        {
            *mod=*temp1;
            temp1++;
            l1--;
            mod++;
        }
    }
    else
    {
        while(l2>0)
        {
            *mod=*temp2;
            temp2++;
            l2--;
            mod++;
        }
    }
   	printf("finally\n");
   	display(arr,length);
   	free(t1);
   	free(t2);
}

void mergesort(int start,int end,int *array)
{
    int mid=(start+end)/2;
    pid_t pid1,pid2;
    if(end==start)
        return;

    pid1=fork();
    if(pid1<0)
        err("Error in forking\n");
    else if(pid1 == 0)
    {
//        printf("Entering in pid1 start=%d end=%d\n",start,mid);
//        display(array,6);
        mergesort(start,mid,array);
        exit(0);
    }
    else
    {
        pid2=fork();
        if(pid2<0)
            err("Error in forking\n");
        else if(pid2==0)
        {
//            printf("Entering in pid2 start=%d end=%d\n",mid+1,end);
//            display(array,6);
            mergesort(mid+1,end,array);
            exit(0);
        }
    }
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    merge(start,mid,end,array);
//    printf("In start=%d end=%d\n",start,end);
//    display(array,6);
    return;
}

int main(int argc,char *argv[])
{
    FILE *fp;
    int n,shm_id,*shm_arr,i;

    fp=fopen("input.txt","r");
    if(fp==NULL)
        err("Error in opening input.txt");
    fscanf(fp,"%d",&n);
    length=n;

    if ((shm_id = shmget(IPC_PRIVATE, n*sizeof(int), IPC_CREAT | 0666)) == -1)
        err("Error in creating shared memory\n");

    if ((shm_arr = shmat(shm_id, NULL, 0)) == (int *) -1)
        perror("Error in attaching shared memory\n");

    for (i = 0; i < n; ++i) {
        fscanf(fp,"%d",&shm_arr[i]);
    }

   printf("Original array in pid=%d\n",getpid());
   display(shm_arr,length);
    mergesort(0,n-1,shm_arr);
    printf("sorted arry in pid=%d\n",getpid());
    display(shm_arr,length);

    if(shmdt(shm_arr)==-1)
        perror("Error in detaching shared memory\n");

    if(shmctl(shm_id,IPC_RMID,NULL)==-1)
        err("Error in removing shared memory\n");

    return 0;
}