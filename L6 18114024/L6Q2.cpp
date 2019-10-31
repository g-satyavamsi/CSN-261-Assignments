/**
 * @file L6Q2.cpp
 * G.Satya Vamsi
 * @brief Binomial Heap
 * @date Oct 08,2019
 * 
 */
#include <bits/stdc++.h> 
using namespace std; 

int x=0;


struct Node 
{ 
	int val, degree; 
	Node *parent, *child, *sibling; 
}; 
 
Node *root = NULL; 


void binomialLink(Node *h1, Node *h2) 
{ 
	h1->parent = h2; 
	h1->sibling = h2->child; 
	h2->child = h1; 
	h2->degree = h2->degree + 1; 
} 

Node *createNode(int n) { 
	Node *new_node = new Node; 
	new_node->val = n; 
	new_node->parent = NULL; 
	new_node->sibling = NULL; 
	new_node->child = NULL; 
	new_node->degree = 0; 
	return new_node; 
} 

Node *mergeBHeaps(Node *h1, Node *h2) 
{ 
	if (h1 == NULL) 
		return h2; 
	if (h2 == NULL) 
		return h1; 

	
	Node *res = NULL; 
 
	if (h1->degree <= h2->degree) 
		res = h1; 

	else if (h1->degree > h2->degree) 
		res = h2; 

	while (h1 != NULL && h2 != NULL) 
	{ 
		if (h1->degree < h2->degree) 
			h1 = h1->sibling; 

		else if (h1->degree == h2->degree) 
		{ 
			Node *sib = h1->sibling; 
			h1->sibling = h2; 
			h1 = sib; 
		} 

		else
		{ 
			Node *sib = h2->sibling; 
			h2->sibling = h1; 
			h2 = sib; 
		} 
	} 
	return res; 
} 

Node *unionBHeaps(Node *h1, Node *h2) 
{ 
	if (h1 == NULL && h2 == NULL) 
	return NULL; 

	Node *res = mergeBHeaps(h1, h2); 

	Node *prev = NULL, *curr = res, *next = curr->sibling; 

	while (next != NULL) 
	{ 
		if ((curr->degree != next->degree) || 
				((next->sibling != NULL) && 
				(next->sibling)->degree == 
				curr->degree)) 
		{ 
			prev = curr; 
			curr = next; 
		} 

		else
		{ 
			if (curr->val <= next->val) 
			{ 
				curr->sibling = next->sibling; 
				binomialLink(next, curr); 
			} 
			else
			{ 
				if (prev == NULL) 
					res = next; 
				else
					prev->sibling = next; 
				binomialLink(curr, next); 
				curr = next; 
			} 
		} 
		next = curr->sibling; 
	} 
	return res; 
} 

ofstream outdata;

void binomialHeapInsert(int x) { 
	root = unionBHeaps(root, createNode(x)); 
} 

void display(Node *h) 
{ 
	while (h) 
	{   

        if(x<h->degree){
            x=h->degree;
            cout<<endl<<"Order "<<x<<": ";
            if(!h->child) 
            outdata<<h->val<<";"<<endl;
        }

        if(h->child){
            outdata<<h->val<<"--"<<h->child->val<<";"<<endl;
            
            if(h->child->sibling){
            outdata<<h->val<<"--"<<h->child->sibling->val<<";"<<endl;
            }
        }
        
		cout << h->val<<" ";
		display(h->child);        
		h = h->sibling;
	} 
} 

int main() 
{ 
    outdata.open("/home/satya/gra.dot");

    if( !outdata ) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    outdata<<"graph{"<<endl;

    int i,num,tot;
    cin>>tot;
    for(i=tot;i>0;i--){
        cin>>num;
        binomialHeapInsert(num);
    }
    
    x=root->degree;
    if(!root->child)
    outdata<<root->val<<";"<<endl;


	cout << "The heap is:\nOrder "<<x<<": "; 

	display(root); 
    
    outdata<<"}"<<endl;
    cout<<endl;
    outdata.close();
	return 0; 
} 
