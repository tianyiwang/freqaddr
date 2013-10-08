/*author: tianyi Wang*/


#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0

typedef struct prefixnode prefixnode;
typedef struct horinode horinode;
typedef struct verticalnode verticalnode;
struct prefixnode{
	verticalnode *ptr;
	prefixnode **branches;
	
};

prefixnode *createnode(){
	prefixnode *temp = malloc(sizeof (prefixnode));
	return temp;
	
}

struct verticalnode{
	int value;/*change to size_t*/
	verticalnode *next, *prev;
	horinode *parent;
};
verticalnode *createvnode(){
	verticalnode *temp = malloc(sizeof (verticalnode));
	return temp;
}

struct horinode{
	int freq;
	verticalnode *bucket;
	horinode *next;
};
horinode *createhnode(){
	horinode *temp = malloc(sizeof (horinode));
	return temp;
}



void insert(prefixnode *head, int value, horinode *ll){/*change back to size_t*/
	int branch = value %16;
	int newvalue = value/16;
	/*if branches = null create branches*/
	if(head->branches == NULL){
		head->branches = malloc(16* sizeof (prefixnode*));
	}
	/*if branch = null create node*/
	if(head->branches [branch]== NULL){
		head->branches[branch]=createnode();
	}
	if(newvalue!=0){
		insert(head->branches[branch], newvalue);	
	}else{
		if(head->branches[branch]->ptr==NULL){
			verticalnode *temp = createvnode();
			temp->parent = ll;
			temp->next=temp->parent->bucket;
			ll->bucket=temp;
		}else{
			inserttofreq(head->branches[branch]->ptr);
		}
	}
}

void inserttofreq(verticalnode *ptr){
	if(ptr->prev!=NULL){
		ptr->prev->next=ptr->next;
	}
	if(ptr->next!=NULL){
		ptr->next->prev=ptr->prev;
	}
	if(ptr->parent->next==NULL){
		ptr->parent->next=createhnode();
	}
	ptr->parent=ptr->parent->next;
	ptr.next=parent->bucket;
	ptr->parent->bucket=ptr;

}


int main(){
	prefixnode* tree=createnode();
	insert(tree, 34);
	insert(tree,5);
	printf("%d\n",tree->branches[2]->branches[2]->hasdata);
	printf("%d\n",tree->branches[5]->hasdata);
	return 0;
}

