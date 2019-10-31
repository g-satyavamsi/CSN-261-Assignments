/**
 * @file L6Q3.cpp
 * G.Satya Vamsi
 * @brief Graph
 * @date Oct 08,2019
 * 
 */
#include<bits/stdc++.h>
#include<malloc.h>
using std::cout;
using std::cin;
#define max 10

struct node
{
    int vertex;
    struct node *next;
};
typedef struct node* nodeptr;
typedef struct queue
{
    int front,rear;
    int arr[max];
}item1;
typedef struct stack
{
    int top;
    int arr[max];
}item2;


nodeptr getnode(){
    nodeptr p=(nodeptr)malloc(sizeof(struct node));
    p->next=NULL;
    return p;
}

int empty(struct stack *s){
    if(s->top==-1)
        return 1;

    else
        return 0;
}

void push(struct stack *s,int x){
    if(s->top==max-1)
        cout<<"\n Queue Overflow";
    
    else{
        s->top++;
        s->arr[s->top]=x;
    }
}

int pop(struct stack *s){
    int x;
    if(empty(s))
        cout<<"\n Queue Overflow..!";
    else{
        x=s->arr[s->top];
        s->top--;
    }
    return x;
}

int qempty(struct queue *q){
    if(q->front > q->rear)
        return 1;
    else
        return 0;
}

void insertq(struct queue *q,int x){
    if(q->rear==max-1)
        cout<<"\nQueue Overflow..1";

    else{
        q->rear++;
        q->arr[q->rear]=x;
    }
}

int removeq(struct queue *q){
    int x;
    if(qempty(q))
        cout<<"\nQueue Overflow..!";

    else{
        x=q->arr[q->front];
        q->front++;
    }
    return x;
}

void init(nodeptr head[],int n){
    int v;
    for(v=1;v<=n;v++)
    head[v]=NULL;
}

void initialise_visit(int visited[],int n){
    int i;
    for(i=1;i<=n;i++)
        visited[i]=0;
}

void create(nodeptr head[]){
    nodeptr adj;
    char ch='y';
    int i,v1,v2,v,c;
    nodeptr new1,p;
    cout<<"\n0.Directed";
    cout<<"\n1.UnDirected";
    cout<<"\nEnter Your Choice:\t";
    cin>>c;

    do{
        cout<<"\n Enter The Edge Between Two Vertices: also decide to add a edge(y) or not(n)\t";
        cin>>v1>>v2;
        new1=getnode();
        new1->vertex=v2;
        p=head[v1];
        if(p==NULL)
            head[v1]=new1;
        else{
            while(p->next!=NULL)
                p=p->next;
            p->next=new1;
        }
        if(c==1)  
        {
            new1=getnode();
            new1->vertex=v1;
            p=head[v2];
            if(p==NULL)
                head[v2]=new1;
            else{
                while(p->next!=NULL)
                    p=p->next;
                p->next=new1;
            }
        }
        cin>>ch;
    }while(ch=='y'||ch=='Y');
}


void DFSR(nodeptr head[],int start,int visited[]){
    nodeptr adj;
    visited[start]=1;
    cout<<"\t"<<start;
    adj=head[start];

    while(adj!=NULL){
        if(visited[adj->vertex]==0)
            DFSR(head,adj->vertex,visited);
        adj=adj->next;
    }
}

void DFSN(nodeptr head[],int start,int visited[]){
    nodeptr adj;
    struct stack s;
    int v;
    s.top=-1;
    push(&s,99);
    visited[start]=1;
    cout<<"\n"<<start;
    push(&s,start);
    do
    {
        adj=head[start];
        while(adj!=NULL){
            if(visited[adj->vertex]==0){
                visited[adj->vertex]=1;
                cout<<"\t"<<adj->vertex;
                push(&s,adj->vertex);
                start=adj->vertex;
                break;
            }
            else
                adj=adj->next;
        }

        if(adj==NULL)
            start=pop(&s);
    }while(!empty(&s));
}

void BFS(nodeptr head[],int start,int visited[]){
    nodeptr adj;
    struct queue q;
    int v;
    q.front=0;
    q.rear=-1;
    
    insertq(&q,start);
    visited[start]=1;
    while(!qempty(&q)){
        v=removeq(&q);
        cout<<"\n"<<v;
        adj=head[v];
        while(adj!=NULL){
            if(visited[adj->vertex]==0){
                insertq(&q,adj->vertex);
                visited[adj->vertex]=1;
            }
            adj=adj->next;
        }
    }
}

int x;

void dfs1Util(int node, int count, bool visited[],int& maxCount, nodeptr head[]) { 
    nodeptr adj;
    visited[node] = 1; 
    count++;
    adj=head[node];

    while(adj!=NULL){
        if (visited[adj->vertex]==0){ 
            if (count >= maxCount){ 
                maxCount = count; 
                x = adj->vertex; 
            } 
            dfs1Util(adj->vertex, count, visited, maxCount, head); 
            } 
        adj=adj->next;
    }
} 

void dfs1(int node, int n, nodeptr head[], int& maxCount) { 
    bool visited[n + 1]; 
    int count = 0;  
    for (int i = 1; i <= n; ++i) 
        visited[i] = 0; 
    dfs1Util(node, count + 1, visited, maxCount, head);
} 

int diameter(nodeptr head[], int n) { 
    int maxCount = INT_MIN; 
    dfs1(1, n, head, maxCount); 
    dfs1(x, n, head, maxCount); 

    return maxCount; 
} 


bool isCyclicUtil(int v, bool visited[], int parent,nodeptr head[]) 
{ 
    visited[v] = true; 
    nodeptr adj;
    adj=head[v];
    while(adj!=NULL){
        if (!visited[adj->vertex]){ 
            if (isCyclicUtil(adj->vertex, visited, v,head)) 
                return true; 
    }

    else if (adj->vertex != parent) 
        return true; 

    adj=adj->next;
    }
    return false;
} 

bool iscyclic(nodeptr head[],int n) {
    int i,u;
    bool *visited = new bool[n]; 
    for ( i = 0; i < n; i++) 
        visited[i] = false; 

    for ( u = 0; u < n; u++) 
        if (!visited[u]) 
            if (isCyclicUtil(u, visited, -1,head)) 
                return true; 

    return false;
}

int main()
{
    char c='y';
    int ch,start,n,visited[10];
    nodeptr head[10];
    do{
    cout<<"\n1. Create\n2.Set edge\n3.Depth First Search(Rec)\n4.Depth First Search(Non-Rec)\n5.Breadth First Search\n6.Whether it is cyclic\n7.Diameter";

    printf("\nEnter Your Choice:\t");
    cin>>ch;
    switch(ch){
        case 1:
        cout<<"\nNo. of Vertices In Graph:";
        cin>>n;
        init(head,n);
        create(head);
        break;

        case 2:
        int i,v1,v2,v,c;
        nodeptr new1,p;
        cout<<"\nEdge Between Two Vertices: also decide to add a edge(y) or not(n)";
        cin>>v1>>v2;
        new1=getnode();
        new1->vertex=v2;
        p=head[v1];
        if(p==NULL)
            head[v1]=new1;
        else{
            while(p->next!=NULL)
                p=p->next;
            p->next=new1;
        }
            
        new1=getnode();
        new1->vertex=v1;
        p=head[v2];
        if(p==NULL)
            head[v2]=new1;
        else{
            while(p->next!=NULL)
                p=p->next;
            p->next=new1;
        }
            
        break;

        case 3:
        cout<<"\nEnter The Vertex From Which You Want To Start Traversal";
        cin>>start;
        initialise_visit(visited,n);
        cout<<"\nRecursive Depth First Search Is\n";
        DFSR(head,start,visited);
        break;

        case 4:
        cout<<"\nEnter The Vertex From Which You Want To Start Traversal";
        cin>>start;
        initialise_visit(visited,n);
        cout<<"\nNon-Recursive Depth First Search Is\n";
        DFSN(head,start,visited);
        break;

        case 5:
        cout<<"\nEnter The Vertex From Which You Want To Start Traversal";
        cin>>start;
        initialise_visit(visited,n);
        BFS(head,start,visited);
        break;

        case 6:
        if(iscyclic(head,n))
            cout<<"Graph contains cycle\n";
            
        else
            cout<<"Graph doesn't contain cycle\n"; 
        break;
        case 7:
            cout<<diameter(head,n);
            
        break;	
    }
    cout<<"Do you want to continue?";
    scanf("\n");
    cin>>c;
    }while(c=='Y'||c=='y');
}