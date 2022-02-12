#include <iostream>
#include <stdio.h>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<string>
#define STACKSIZE 1000
#include <math.h>
#include<map>
typedef union
{
    float fData;
    char  cData;
} Item;
typedef struct
{
    int top;
    Item items[STACKSIZE];
} Stack;
typedef struct Node
{
    char *key;
    float value;
    struct Node* left;
    struct Node* right;
} Node;
typedef struct
{
    float value;
    char*key;
} HeapNode;
Stack *intialize()
{
    Stack *s=(Stack *) malloc(sizeof(Stack));
    s->top=0;
    return s;
}
void push(Stack *s,Item value)
{
    s->items[s->top++]=value;
}
Item pop(Stack *s)
{
    return s->items[--s->top];
};
Item top(Stack *s)
{
    return s->items[s->top-1];
};
int  isEmpty(Stack *s)
{
    return s->top==0?1:0;
}
int  isfull(Stack *s)
{
    return s->top<STACKSIZE?0:1;
}
int isoperator(char str[])
{
    if((strlen(str)==1)&&(str[0]=='+'||str[0]=='-'||str[0]=='*'||str[0]=='/'||str[0]=='^'))
    {
        return 1;
    }
    else
        return 0;
}
bool isDigit(char * s)
{
    if(isdigit(*s))
        return true;
    else if(strlen(s)==2 && s[0]=='-' && s[0]!='('&& s[0]!=')')
        return true;
    else
        return false;
}
Node* newNode(char * str,float val)
{
    Node * n=(Node*)malloc(sizeof( Node));
    n->key=(char *)malloc(strlen(str)+1);

    strcpy(n->key,str);
    n->value=val;
    n->left=n->right=NULL;
    return n;
}
float getVal(Node* Node)
{
    return Node->value;
}
void freeNode(Node* Node)
{
    free(Node->key);

    free(Node);
}

int count(Node* n)
{
    if (n)
        return 1+count(n->left)+count(n->right);
    return 0;
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
void printTree(Node *t)
{
    if (t!=NULL)
    {
        printTree(t->left);
        cout<<t->key << " = " << t->value<<endl;
        printTree(t->right);
    }

}
Node* insert(Node* Node, char * key, float val)
{
    /* 1.  Perform the normal BST insertion */
    if (Node == NULL)
        return(newNode(key,val));

    if (strcasecmp(Node->key,key)>0)
        Node->left  = insert(Node->left, key,val);
    else if (strcasecmp(Node->key,key)<0)
        Node->right = insert(Node->right, key,val);
    else // Equal keys are updated in BST
        Node->value=val;

    return Node;
}
Node* Search(Node* root,char* key)

{
    if (root==NULL)
        return NULL;
    if (strcasecmp(root->key,key)==0)
        return root;
    else if(strcasecmp(root->key,key)>0)
        return Search(root->left,key);
    else
        return Search(root->right,key);
}
int heapSize=0;
//Top Down heap construction
//to heapify element by element after insertion
void HeapifyUp(HeapNode*H,int i)
{
    if(i!=1)
    {
        int p = (i)/2;
        if(H[p].value<H[i].value)
        {
            swap(H[i],H[p]);
            HeapifyUp(H,p);
        }
    }
}
//Function to convert BST into heap
HeapNode* BSTToMinHeap(Node* root,HeapNode* heap)
{
    if (root== NULL)
        return NULL;
    // recur on left subtree
    BSTToMinHeap(root->left,heap);
    // recur on right subtree
    BSTToMinHeap(root->right,heap);
    //insert in heap
    heapSize++;
    heap[heapSize].key=root->key;
    heap[heapSize].value=root->value;
    HeapifyUp(heap,heapSize);
    return heap;
}
//Bottom Up heap construction
HeapNode* MaxHeapify(HeapNode* H,int size,int i)
{
    int left,right,largest;
    left=i*2;
    right=i*2+1;
    if(left<=size&&H[left].value>H[i].value)
        largest=left;
    else
        largest=i;
    if(right<=size&&H[right].value>H[largest].value)
        largest=right;
    if(largest!=i)
    {
        swap(H[i],H[largest]);
        MaxHeapify(H,size,largest);
    }
    return H;
}
//sorting the heap
HeapNode* heapSort(HeapNode* H)
{
    int count=heapSize;
    while(count)
    {
        swap(H[1],H[count]);
        count--;
        MaxHeapify(H,count,1);
    }
    return H;
}
void printHeap(HeapNode* H)
{
    H=heapSort(H);
    for(int i=1; i<=heapSize; i++)
        cout<<H[i].key<<" = "<<H[i].value<<endl;
}
Item evaluate(Item a, Item b,char op)
{
    Item  res;
    switch(op)
    {
    case'+' :
        res.fData= a.fData+b.fData;
        break;
    case'-' :
        res.fData= a.fData-b.fData;
        break;
    case'*' :
        res.fData= a.fData*b.fData;
        break;
    case'/' :
        res.fData= a.fData/b.fData;
        break;
    case '^':
        res.fData=(float) pow((double)a.fData,(double)b.fData);
        break;

    }
    return res;
}
float evaluatPos(char * pos,Node * root)
{
    Stack *s=intialize();
    Item x;
    char*str='\0';
    str=strtok(pos," ");
    Node* current=NULL;
    while(str!=NULL)
    {
        if(!isoperator(str))
        {
            if(isDigit(str))
            {
                x.fData=(float)atof(str);
            }
            else
            {
                current=Search(root,str);
                if(current==NULL)
                {
                    cout<<"Error! Invalid Expression"<<endl;
                    exit(0);
                    x.fData=atof(str);
                    break;
                }
                x.fData=getVal(current);
            }

            push(s,x);

        }
        else
        {
            Item a=pop(s);
            Item b=pop(s);
            push(s,evaluate(b,a,*str));
        }
        str =strtok(NULL," ");
    }
    x=pop(s);
    return x.fData;
}
int priority(char c)
{
    switch (c)
    {
    case '(':
        return 4;
    case '^':
        return 3;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;

    }
    return 0 ;
}
//function to separate the infix with spaces
char* seperate (char *str)
{
    char*seperate=(char* )malloc(256);
    int counter=1;
    seperate[0]='\0';
    char *loop=str;
    char string1[2]="";
    char buffer[2]="";
    //looping over the string
    while(*loop!='\0')
    {
        string1[0]=loop[0];
        //if it's digit then add it
        if(string1[0]=='('||string1[0]==')')
        {
            if(!isoperator(buffer))
                str=strcat(seperate," ");
            str=strcat(seperate,string1);
            str=strcat(seperate," ");
        }

        else if(!isoperator(string1))
        {
            strcat(seperate,string1);
        }
        //if it is operator
        else if (isoperator(string1))
        {
            //handling negative numbers and subtraction
            if(string1[0]=='-'&&buffer!='\0'&& isoperator(buffer))
            {
                //if the char is negative and previous char was also operator then it's negative number
                str=strcat(seperate," ");
                str=strcat(seperate,string1);
            }
            //else it will be subtraction or any other operator so will add it directly
            else
            {
                if(buffer[0]!=')')
                    str=strcat(seperate," ");
                str=strcat(seperate,string1);
                str=strcat(seperate," ");
            }
        }

        strcpy(buffer,string1);
        loop++;
        counter++;
    }
    strcat(seperate,"");
    return seperate;
}
//convert from infix to postfix
void infixToPostfix(char* str,char* postfix)
{
    char*infix=(char*)malloc(256);
    infix=seperate(str);
    Stack *s = intialize();
    Item x;
    char srting1[2]="";
    postfix[0]='\0';
    char * token = strtok(infix, " ");
    while(token!=NULL)
    {
        if (token[0]==')')
        {
            while (!isEmpty(s)&& top(s).cData!='(')
            {
                srting1[0]=pop(s).cData;
                postfix=strcat(postfix,srting1);
                postfix=strcat(postfix," ");

            }
            pop(s);
        }
        else if( !isoperator(token)&& token[0]!='(')
        {
            postfix=strcat(postfix,token);
            postfix=strcat(postfix," ");
        }
        else if(isEmpty(s))
        {
            x.cData=token[0];
            push(s,x);
        }
        else
        {
            while(!isEmpty(s)&& priority(top(s).cData) >= priority(token[0])&& top(s).cData!='(')
            {

                srting1[0]=pop(s).cData;
                postfix=strcat(postfix,srting1);
                postfix=strcat(postfix," ");


            }
            x.cData=token[0];
            push(s,x);
        }
        token = strtok(NULL, " ");
    }
    while(!isEmpty(s))
    {
        srting1[0]=pop(s).cData;
        postfix=strcat(postfix,srting1);
        postfix=strcat(postfix," ");
    }
}
//removing spaces from string before separating it
void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
    // incremented
    str[count] = '\0';
}
//function to handle invalid expressions
bool HasSpecialCharacters(char *str)
{

   while(*str!='\0')
   {
       if(!isalpha(*str))
       return true;
    str++;
   }
   return false;
}
Node* LOAD()
{
    Node* root= NULL;
    FILE *f1;
    char *s=(char*)malloc(80);
    char z[90];
    char *l=(char*)malloc(20);
    f1=fopen("Src.txt","r");

    if (f1!=NULL)
    {
         printf("-- file input -- \n");
        while (!feof(f1))
        {
            fscanf(f1,"%[^=]=",s);
            removeSpaces(s);
            if(!HasSpecialCharacters(s)){
            fscanf(f1,"%[^\n]\n",z);
            removeSpaces(z);
            printf("%s = %s\n",s,z);
            infixToPostfix(z,l);
            float f=evaluatPos(l,root);
            root=insert(root,s,f);
            }
            else {
                cout<<"Error! Invalid Expression"<< endl;
                exit(0);
            }
        }
        printf("\n");
        fclose(f1);
    }
    else
        printf("\n Error loading file");
    return root;
}
int main(int argc, char**argv)
{
    Node* root=LOAD();
    cout<<"-- Sorting with variable Name --"<<endl;
    printf("\n");
    printTree(root);
    HeapNode* heap=(HeapNode*)malloc(count(root));
    heap=BSTToMinHeap(root,heap);
    printf("\n");
    cout<<"-- Sorting with value --"<<endl;
    printf("\n");
    printHeap(heap);
    printf("\n");
    return 0;
}
