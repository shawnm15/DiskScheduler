

#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/
#include <stdbool.h>
#include <limits.h>
#define N 8
int requests[8]={98,183,37,122,14,124,65,67};

int head;
char * direction;
int copy[8];

void swap(int *i,int *j);
void sort(int arr[], int n);
void LOOK_right();
void LOOK_left();
void SCAN_left();
void SCAN_right();
void FCFS(int head);

int sorted[8];
int buffer[8];
int buffer_scan[9];


void SCAN(int head,char * dir){
	printf("SCAN DISK SCHEDULING ALGORITHM\n\n");
	int i;
	if (strcmp(dir,"LEFT")==0){
		SCAN_left();
	}else if (strcmp(dir,"RIGHT")==0){
		SCAN_right();
	}

	int total=abs(buffer_scan[0]-head);
	for (i=1;i<sizeof(buffer_scan)/sizeof(int);i++){
		if (buffer_scan[i-1]!=0 && buffer_scan[i-1]!=199){
			printf("SCAN - servicing request: %d\n", buffer_scan[i-1]);
			total+=abs(buffer_scan[i]-buffer_scan[i-1]);
		}else if (buffer_scan[i-1]==0 || buffer_scan[i-1]==199){
			total+=abs(buffer_scan[i]-buffer_scan[i-1]);
		}
	}
	
	printf("SCAN - servicing request: %d\n", buffer_scan[8]);
	printf("SCAN - Total head movements = %d\n\n", total);
}

void SCAN_left(){
	int i,j,k,c=0,d=0;
	int temp_sort[8],t2[6],t1[3];

	for (i=0;i<N;i++){	
		temp_sort[i]=requests[i];
	}
	sort(temp_sort,N);
	
	int a=2;
	int b=0;
	for (j=0;j<6;j++){
		t2[j]=temp_sort[a];
		a++;
	}

	for (j=1;j>=0;j--){
		t1[j]=temp_sort[b];
		b++;
	}
	
	t1[2]=0;

	while (c!=3){
		buffer_scan[c]=t1[c];
		c++;
	}
	
	while (c!=9){
		buffer_scan[c]=t2[d];
		c++;
		d++;
	}
}

void SCAN_right(){
	
	int i,j,k,c=0,d=0;
	int temp_sort[8],t1[7],t2[2];

	for (i=0;i<N;i++){	
		temp_sort[i]=requests[i];
	}
	sort(temp_sort,N);

	int a=2;
	int b=0;

	for (j=0;j<=5;j++){
		t1[j]=temp_sort[a];
		a++;
	}
	
	t1[6]=199;
	
	for (j=1;j>=0;j--){
		t2[j]=temp_sort[b];
		b++;
	}

	while (c!=7){
		buffer_scan[c]=t1[c];
		c++;
	}
	
	while (c!=9){
		buffer_scan[c]=t2[d];
		c++;
		d++;
	}	
}


void LOOK(int head,char * dir){
	printf("LOOK DISK SCHEDULING ALGORITHM\n\n");

	int i;
	for (i=0;i<N;i++)
		sorted[i]=requests[i];

	sort(sorted,N);
	
	if (strcmp(dir,"LEFT")==0){
		LOOK_left();
	}else if (strcmp(dir,"RIGHT")==0){
		LOOK_right();
	}

	int total=abs(buffer[0]-head);
	for (i=1;i<sizeof(requests)/sizeof(int);i++){
		printf("LOOK - servicing request: %d\n", buffer[i-1]);
		total+=abs(buffer[i]-buffer[i-1]);

	}
	
	printf("LOOK - servicing request: %d\n", buffer[7]);
	printf("LOOK - Total head movements = %d\n", total);
}

void LOOK_left(){
	int i;
	
	for (i=0;i<N;i++){
		buffer[i]=sorted[i];
	}
	swap(&buffer[0],&buffer[1]);

}
void LOOK_right(){
	int j=0;
	while(sorted[j]<head){
		j++;
	}
	
	int i;
	int ind=2;
	
	for(i=0;i<N;i++){
		buffer[i]=sorted[ind];
		ind=(ind+1)%N;

	}
	
	swap(&buffer[6],&buffer[7]);
}


void SSTF(int head){
	printf("SSTF DISK SCHEDULING ALGORITHM\n\n");
       
	int temp[9],buffer_sstf[9];
	int i,j;
	int min,dist;
	int counter=0,position=0,total=0;
 	int c=0;
	temp[0]=head;

	for(i=1;i<=N;i++){
		temp[i]=requests[c];
		c++;
	}
	
	buffer_sstf[counter]=temp[0];
	counter++;
	
	for(i=0;i<N;i++){
 		min=INT_MAX;

 	 	for(j=i+1;j<=N;j++){
			dist=abs(temp[i]-temp[j]);
   
   			if(dist<min){
    				min=dist;
    				position=j;
   			}
  		}
  		total+=min;
  		
		swap(&temp[i+1],&temp[position]);	

		buffer_sstf[counter]=temp[i+1];
		counter++;
 	}

 	for(i=1;i<=N;i++){
 		printf("SSTF - servicing request: %d\n",buffer_sstf[i]);
	}
 	printf("SSTF Total head movements = %d\n\n",total);

}

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		fprintf(stderr,"Usage: ./a.out <head and direction>\n");
		return -1;
	}

	head=atoi(argv[1]);
	direction=(argv[2]);

	FCFS(head);
	SSTF(head);
	SCAN(head, direction);
	LOOK(head,direction);

	return 0;
}

void FCFS(int head){
	printf("FCFS DISK SCHEDULING ALGORITHM\n\n");

	int i;
	int total=requests[0]-head;
	for (i=1;i<sizeof(requests)/sizeof(int);i++){
		printf("FCFS - servicing request: %d\n", requests[i-1]);
		total+=abs(requests[i]-requests[i-1]);
	}
	printf("FCFS - servicing request: %d\n", requests[7]);
	printf("FCFS - Total head movements = %d\n\n", total);

}
void sort(int a[], int n){
	int i,temp,j;
	
  	for (i=1;i<n;i++){
       		temp=a[i];
       		j=i-1;
		
       		while(a[j]>temp && j>=0){
           		a[j+1]=a[j];
           		j-=1;
       		}
       		a[j+1]=temp;
  	}

}

void swap(int *i,int *j){
	int temp=*i;
	*i=*j;
	*j=temp;
}
