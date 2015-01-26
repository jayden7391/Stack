#include<iostream>

#define ERROR_NUMBER -1
//function prototype

//Start of user code
#include <float.h>
typedef struct ptr_list ptr_L;
typedef struct vertex VTX;
typedef struct edge EDGE;
int Total_Used_Memory = 0;
struct ptr_list{//linked list definition
	int i;
	ptr_L *p;
};

struct vertex{
	int x,y;
	ptr_L *p;
};

struct edge{
	int v1, v2;
	int cost;
};

VTX *V = NULL;
EDGE *E = NULL;
int V_Num = 0, E_Num=0;
ptr_L *ptr_L_pool = NULL;
int ptr_L_cnt = 0;
int Total_Used_memory = 0;
class stack{

public:
	int pop_ptr_L(ptr_L **S);
	void push_ptr_L(ptr_L **S, int i);
	ptr_L *addFILO_ptr_L(ptr_L **S, ptr_L **S_end, int sym);
	int getFILO_ptr_L(ptr_L **S, ptr_L **S_end);
	ptr_L *Alloc_ptr_L(void);
	void Free_ptr_L(ptr_L *ptr);
	void Free_ptr_L_pool(void);
};

void stack::push_ptr_L(ptr_L **S, int i){
	ptr_L *L;

	L = Alloc_ptr_L();
	L->i = i;

	L->p = *S;
	*S = L;
	return;
}

int stack::pop_ptr_L(ptr_L **S){
	int i;
	ptr_L *tS;

	i = (*S)->i;
	tS = *S;
	if((*S)->p==NULL)
		*S = NULL;
	else
		*S=(*S)->p;

	Free_ptr_L(tS);
	return(i);
}

ptr_L *stack::addFILO_ptr_L(ptr_L **S, ptr_L **S_end, int sym){
	ptr_L *L;

	L = Alloc_ptr_L();
	L->i = sym;
	if(*S=NULL)
		*S = L;
	else
		(*S)->p=L;
	*S = L;
	return(L);
}

int stack::getFILO_ptr_L(ptr_L **S, ptr_L **S_end){
	int sym;
	ptr_L *tS;

	sym = (*S)->i;
	tS = *S;
	if((*S)->p == NULL)
		*S =NULL;
	else
		*S = (*S)->p;
	Free_ptr_L(tS);
	return(sym);
}

ptr_L *stack::Alloc_ptr_L(void){
	ptr_L *ptr;

	if(ptr_L_pool == NULL){
		ptr = new ptr_L;
		Total_Used_Memory += sizeof(ptr_L);
		ptr->i = ERROR_NUMBER;
	}
	else{
		ptr = ptr_L_pool;
		ptr_L_pool = ptr->p;
	}
	ptr->p = NULL;
	++ptr_L_cnt;
	return(ptr);
}

void stack::Free_ptr_L(ptr_L *ptr){
	ptr->i = ERROR_NUMBER;
	ptr->p = ptr_L_pool;
	ptr_L_pool = ptr;
	--ptr_L_cnt;
}

void stack::Free_ptr_L_pool(void){
	ptr_L *p;

	p = ptr_L_pool;
	while(p != NULL){
		ptr_L_pool = p->p;
		free(p);
		p = ptr_L_pool;
		Total_Used_Memory -= sizeof(ptr_L);
	}
	ptr_L_pool = NULL;
}

int main(void){
	stack s;
	ptr_L **p = NULL;
	int i = 0;
	for(i = 0; i < 10; i++)
		s.push_ptr_L(p, i);
	for(i = 0; i<10; i++)
		s.pop_ptr_L(p);
	return 0;
}