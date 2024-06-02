#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    char app[20];
    char notification[20];
    struct node* front;
    struct node* back;
};
struct node* first=NULL;
struct node* last=NULL;
struct node* prev=NULL;
struct node* create(struct node*);  //to create double linked list
void displayd(); //to display double linked list
struct node* insertion(struct node*,char[],char[],struct node **); //insertion
struct node* insertb(struct node*,char[],char[],struct node **);//insertion at beginning
struct node* deletion(struct node*,char[],char []);//deletion
struct node* Clear(struct node*);//clear all notifications
struct node* delete(struct node*);//delete a node in double linked list
struct node* search(struct node*,char[]); // search a node

struct snode
{
    char tab[20];
    struct snode* link;
};
struct snode* head=NULL;
struct snode* insert(struct snode*,char[]);
void displays();//to display linked list
int count(char[]);//count a app in linked list(double)
void deleteh(char[],struct snode*);//delete a node in linked list
void deleteall(struct snode*);//clear all tabs in history

int main()
{
    char block[20];
    first=create(first);
    while(1)
    {
        printf("\n1.Display the present notification task bar\n");
        printf("2.Want to block any app notification\n");
        printf("3.New notification came\n");
        printf("4.Clear a particular notification\n");
        printf("5.Open a particular notification\n");
        printf("6.Clear all notifications\n");
        printf("7.Exit\n");
        
        int choice,choice1;
        printf("Enter the choice:");
        scanf("%d",&choice);
    
        switch(choice)
        {
            case 1:
                printf("Notications in notication bar\n");
                displayd();
                break;
            
            case 2:
            {
                printf("Enter the app notification to block:");
                scanf(" %[^\n]s",block);
                break;
            }
            
            case 3:
            {
                char item[20];
                char note[20];
                printf("Enter the app notification came just now:");
                scanf("%s",item);
                if(strcmp(item,block)==0)
                {
                    printf("This app notification is blocked\n");
                }
                else
                {
                    printf("Enter the notification message theme:");
                    scanf(" %[^\n]s",note);
                    first=insertion(first,item,note,&prev);
                }
                
                break;
            }
        
            case 4:
            {
                char item[20];
                printf("Enter the app notification to delete from task bar:");
                scanf(" %[^\n]s",item);
                int count1=count(item);
                if(count1>1)
                {
                    char dataa[20];
                    printf("Enter the notification message theme:");
                    scanf(" %[^\n]s",dataa);
                    deletion(first,item,dataa);
                }
                else
                {
                    char data[20];
                    deletion(first,item,data);
                }
                break;
            }
        
            case 5:
            {
                char item[20];
                printf("Enter the app notification u supposed to see:");
                scanf(" %[^\n]s",item);
                struct node* temp=first;
                struct node* node=NULL;
                struct node* ptr1=search(temp,item);
                int test=0;
                while(temp!=NULL)
                {
                    if(strcmp(temp->app,item)==0)
                    test=-1;
                    temp=temp->front;
                }
                if (test == -1) {
                    printf("%s has opened.\n",item);
                }
            if(test==-1)
            {
                head=insert(head,item);
                struct snode* ptr=head;
                printf("A tab is created in History bar\n");
                printf("U can check and delete the history\n");
                while(choice1!=4)
                {
                    printf("\n1.Display the history bar\n");
                    printf("2.Delete any tab from history bar\n");
                    printf("3.Clear all notifications\n");
                    printf("4.Exit\n");
                    
                    
                    printf("Enter the choice:");
                    scanf("%d",&choice1);
                    
                    switch(choice1)
                    {
                        case 1:
                            printf("Tabs in History bar:\n");
                            displays();
                            break;
                            
                        case 2:
                        {
                            char delete[20];
                            printf("Enter the app notification to delete from history bar:");
                            scanf(" %[^\n]s",delete);
                            deleteh(delete,ptr);
                            break;
                        }
                        
                        case 3:
                        {
                          deleteall(ptr);
                          break;
                        }
                        
                        case 4:
                        {
                            printf("\n");
                            printf("came back from history bar\n");
                            printf("*************************");
                            printf("\n");
                            break;
                        }
                        
                        default :
                            printf("Invalid choice\n");
                            printf("\n");
                            break;
                    }
                }
                while(strcmp(ptr1->app,item)==0)
                {
                    node=ptr1;
                    ptr1=ptr1->back;
                    delete(node);
                    node=NULL;
                }
            }
            
            else
            {
                printf("No such notification exists in notification bar\n");
            }
                break;
            }
        
            case 6:
            {
                struct node* ptr=first;
                while(ptr!=NULL)
                {
                    ptr=Clear(ptr);
                }
                printf("All notications are cleared\n");
                break;
            }
        
            case 7:
                printf("\n");
                printf("came back from Notification bar\n");
                printf("*************************");
                return 0;
                
            default:
                printf("Invalid choice\n");
                printf("\n");
        }
    }
    return 0;
}

struct node* create(struct node* start)
{
    
    int size;
    printf("Enter number of notifications in task bar:");
    scanf("%d",&size);
    for(int i=0;i<size;i++)
    {
        struct node* ptr=(struct node*)malloc(sizeof(struct node));
        if(ptr==NULL)
        {
            printf("overflow\n");
            return NULL;
        }
        printf("Enter the notification%d app:",i+1);
        scanf(" %[^\n]s",ptr->app);
        printf("Enter the notification message:");
        scanf(" %[^\n]s",ptr->notification);
        start=insertion(start,ptr->app,ptr->notification,&prev);
    }
    return start;
}

struct node* insertion(struct node* start,char item[],char data[],struct node** pre)
{
        struct node * ptr1=search(start,item);
        struct node * temp=NULL;
        if(ptr1==NULL)
        {
            start=insertb(start,item,data,&prev);
        }
        else 
        {
            while(strcmp(ptr1->app,item)==0)
            {
                start=insertb(start,item,ptr1->notification,&prev);
                temp=ptr1;
                ptr1=ptr1->back;
                delete(temp);
                temp=NULL;
            }
            start=insertb(start,item,data,&prev);
        }
}

struct node* delete(struct node* ptr)
{
    if(ptr->front!=NULL)
    {
        ptr->front->back=ptr->back;
        ptr->back->front=ptr->front;
    }
    else if(ptr->front==NULL)
    {
        ptr->back->front=NULL;
    }
    free(ptr);
    ptr=NULL;
}

struct node* insertb(struct node* start,char item[],char data[],struct node ** pre)
{    
        struct node*  ptr=(struct node*)malloc(sizeof(struct node));
        strcpy(ptr->app,item);
        strcpy(ptr->notification,data);
        ptr->front=NULL;
        ptr->back=NULL;
        if((*pre)==NULL)
        {
        	(*pre)=ptr;
        }
        else
        {
        	ptr->front=(*pre);
        	(*pre)->back=ptr;
        	(*pre)=ptr;
        }
        start=ptr;
        return start;    
}

struct node * search(struct node* start,char item[])
{
    struct node* ptr=NULL;
    if(start==NULL || start->front==NULL||strcmp(start->app,item)==0)
        return NULL;
    else 
    {
        while(strcmp(start->app,item)!=0)
        {
            start=start->front;
            ptr=start;
            if(start==NULL)
            return NULL;
         
        }  
        while(ptr->front!=NULL&&strcmp(ptr->front->app,item)==0)
        {
            ptr=ptr->front;
          
        }  
    }
    
    return ptr;
}

struct node* deletion(struct node* start,char item[],char data[])
{
    struct node* ptr=start;
    int count1=0;
    count1=count(item);
    if(count1>1)
    {
        while(ptr!=NULL)
      {
        if(strcmp(ptr->app,item)==0)
        {
            if(strcmp(ptr->notification,data)==0)
            {
                if(ptr->back==NULL)
                {
                    first=ptr->front;
                    free(ptr);
                    ptr=NULL;
                    break;
                }
                if(ptr->front!=NULL)
                {
                    ptr->front->back=ptr->back;
                    ptr->back->front=ptr->front;
                    free(ptr);
                    ptr=NULL;
                    break;
                }
                else
                {
                    ptr->back->front=NULL;
                    free(ptr);
                    ptr=NULL;
                    break;
                }
                
        
            }
        }
        ptr=ptr->front;
      }
    }
    else if(count1==1)
    {
  
        while(ptr!=NULL)
      {
      	
        if(strcmp(ptr->app,item)==0)
        {
            if(ptr->back==NULL)
            {
                first=ptr->front;
                free(ptr);
                ptr=NULL;
                break;
            }
                
            if(ptr->front!=NULL)
            {
                ptr->front->back=ptr->back;
                ptr->back->front=ptr->front;
                free(ptr);
                ptr=NULL;
                break;
            }
            if(ptr->front==NULL)
            {
                ptr->back->front=NULL;
                free(ptr);
                ptr=NULL;
                break;
            }
        }
          ptr=ptr->front;
      }
    }
    return 0;
}

int count(char item[])
{
    struct node* ptr=first;
    int count=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->app,item)==0)
        {
            count=count+1;
        }
        ptr=ptr->front;
    }
    return count;
}

struct snode* insert(struct snode* start,char item[])
{
    struct snode* ptr=(struct snode*)malloc(sizeof(struct snode*));
    strcpy(ptr->tab,item);
    ptr->link=start;
    start=ptr;
    return start;
}

void displays()
{
    struct snode* ptr=head;
    printf("\n--------------------------\n");
    while(ptr!=NULL)
    {
        printf("app:%s\n",ptr->tab);
        printf("--------------------------\n");
        ptr=ptr->link;
    }
}

struct node* Clear(struct node* ptr)
{
    struct node* temp;
        if(ptr == NULL)  
            printf("\nNotification bar is empty\n");  
        else   
        {  
            temp=ptr;
            ptr=ptr->front;
            free(temp);
            temp=NULL;
        }
        first=ptr;
    
        return ptr;
}

void deleteh(char item[],struct snode* ptr)
{
    struct snode* temp;
        if(strcmp(ptr->tab,item)==0)
        {
            temp=(ptr);
            (ptr)=(ptr)->link;
            free(temp);
            head=ptr;
        }
        else 
        {
            struct snode* current=ptr;
            while(current->link!=NULL)
            {
                if(strcmp(current->link->tab,item)==0)
                {
                    temp=current->link;
                    current->link = current->link->link;
                    free(temp);
                    break;
                }
                
                else
                    current=current->link;
            }   
        }
}

void deleteall(struct snode* ptr)
{
    struct snode* temp;
    if(ptr == NULL)  
    {  
        printf("\nHistory bar is empty\n");
    }  
    while(ptr!=NULL)
    {
        temp= ptr;  
        ptr = temp->link;  
        free(temp);  
    }
    head=NULL;
}

void displayd()
{
    struct node* ptr=first;
    printf("\n--------------------------\n");
    while(ptr!=NULL)
    {
        printf("App                   :%s\nApp Notification theme:%s\n",ptr->app,ptr->notification);
        printf("--------------------------\n");
        ptr=ptr->front;
    }
}

