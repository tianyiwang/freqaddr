/*author: tianyi Wang*/


#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0

typedef struct prefixnode prefixnode;
typedef struct horinode horinode;
typedef struct verticalnode verticalnode;
prefixnode *createnode();
verticalnode *createvnode();
horinode *createhnode();
void insert(prefixnode *, size_t, horinode *, size_t);
void inserttofreq(verticalnode*);
struct prefixnode{
	verticalnode *ptr;
	prefixnode **branches;
	
};

prefixnode *createnode(){
	prefixnode *temp = malloc(sizeof (prefixnode));
	return temp;
	
}

struct verticalnode{
	size_t value;/*change to size_t*/
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



void insert(prefixnode *head, size_t  value, horinode *ll, size_t  orivalue){/*change back to size_t*/
	int branch = value %16;
	size_t  newvalue = value/16;
	/*if branches = null create branches*/
	if(head->branches == NULL){
		head->branches = malloc(16* sizeof (prefixnode*));
	}
	/*if branch = null create node*/
	if(head->branches [branch]== NULL){
		head->branches[branch]=createnode();
	}
	if(newvalue!=0){
		insert(head->branches[branch], newvalue, ll, orivalue);	
	}else{
		if(head->branches[branch]->ptr==NULL){
			verticalnode *temp = createvnode();
			head->branches[branch]->ptr=temp;
			temp->value = orivalue;
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
		ptr->parent->next->freq=ptr->parent->freq+1;
	}
	ptr->parent=ptr->parent->next;
	ptr->next=ptr->parent->bucket;
	ptr->parent->bucket=ptr;

}


int main(int argc, char ** argv){
	prefixnode* tree=createnode();
	horinode* ll=createhnode();
	ll->freq=1;
	FILE *fp = fopen(argv[3],"r");
	size_t addr;
	char c;
	if(fp!=NULL){
		c=fgetc(fp);
		c=fgetc(fp);
		while(c!=EOF){
		fscanf(fp, "%zx", &addr);
			insert(tree, addr,ll,addr);
			printf("askdjfkasdjf");
		}
	}
	return 0;
}

