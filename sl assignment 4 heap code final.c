
#include<stdio.h>
#include<stdlib.h>
//first fit.      // 12 14 56 78 43  

struct freeblock  //structures for all the memory avalaible for allocating
{    int icon;
	 int size1; 
	 struct freeblock* next;        
}*head1=NULL, *prev1=NULL;                                        
struct allocblock   //structure of a memory block after allocation
{
	 int size2;
	 struct allocblock* next;           
	 int id;
}*head2=NULL, *prev2=NULL;

void free_block(int s1)           
{
	struct freeblock* lptr;
	lptr=(struct freeblock*)malloc(sizeof(struct freeblock));
	lptr->size1=s1;//size of the block
	if(head1==NULL)
	{
		head1=lptr;
	}
	else
	{
		prev1->next=lptr; //it has the pointer to last allocated free block
		
	}
	prev1=lptr;
}
void alloc_block(int s2)    
{
	struct allocblock* lptr;
	lptr=(struct allocblock*)malloc(sizeof(struct allocblock));
	lptr->size2=s2;
	lptr->next=NULL;
	printf("\n enter the block id ");
    scanf("%d",&lptr->id);
	struct freeblock* nptr;
	nptr=head1;
	
	while(nptr!=NULL)   //firstfit   
	{
		if(lptr->size2<=nptr->size1)
		{
			break;//we are breaking the loop beacause i would like to allocate with first fit
		}
		nptr=nptr->next;
	}
	if(nptr!=NULL)
	{   
	    nptr->icon=lptr->id;
		nptr->size1=nptr->size1-lptr->size2;
		if(head2==NULL)
		{
			head2=lptr;
		}
		else
		{
			prev2=head2;
			while(prev2->next!=NULL)
			{
				prev2=prev2->next;
			}
			prev2->next=lptr;
		}
	}
	else
	{
		printf("\n the requested memory cannot be allocated");
	}
}
void freeallocated(int n)   // 
{                                  // 45  78  
	struct allocblock* lptr;
	lptr=head2;
	struct allocblock* nptr;
	nptr=NULL;
	while(lptr!=NULL)
	{
		if(lptr->id==n)
		{
			break;
		}
		nptr=lptr;
		lptr=lptr->next;
	}
	if(lptr==NULL)
	{
		printf("\n the memory cannot be freed as it is not there");
	}
	else if(lptr==head2)
	{
		head2=head2->next;
	}
	else
	{
		nptr->next=lptr->next;
	}
	struct freeblock* npptr;
	npptr=head1;
	while(npptr!=NULL)
	{
		if(npptr->icon==lptr->id)
		{
			npptr->size1=npptr->size1+lptr->size2;
			break;
		}
		npptr=npptr->next;
	}
}
void printfree()
{
	struct freeblock* lptr;
	lptr=head1;
	while(lptr!=NULL)
	{                                      
		printf("\n size is %d",lptr->size1);
		head1=head1->next;
	}
	
}
void printallocblock()
{
	struct allocblock* nptr;
	nptr=head2;
	while(nptr!=NULL)                    
	{
		printf("\n size %d",nptr->size2);
		printf("\t id %d",nptr->id);
		nptr=nptr->next;
	}
}
int main()
{
	int len1;
	int len2;
	printf("\n enter the no of free blocks");
	scanf("%d",&len1);
	printf("\n enter the no of blocks to be allocated");
	scanf("%d",&len2);
	int arr1[len1];
	int arr2[len2],i;
	printf("\n enter the size of free blocks");
	for(i=0;i<len1;i++)
	{
		scanf("%d",&arr1[i]);
	}
	printf("\n enter the size of blocks to be allocated");
	for(i=0;i<len2;i++)
	{
		scanf("%d",&arr2[i]);
	}
	for(i=0;i<len1;i++)
	{
		free_block(arr1[i]); 
	}
	
	for(i=0;i<len2;i++)
	{
		alloc_block(arr2[i]);
		
	}
	printf("\n allocated blocks block id and their sizes");
	printallocblock();
	freeallocated(2);
	printf("\n allocated blocks block id and its size after freeing a certain block");
	printallocblock();
	
}