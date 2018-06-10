#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
struct Stack{	
	int top;
    unsigned kapasite;
    char* s;
};
struct Variables{
	char degisken;
	double deger;
};

FILE *dosyaAc(FILE *fp,char *dosyaAdi){
	fp = fopen(dosyaAdi,"r");
		if(!fp){
			printf("Dosya Acilamadi");
		}
	return fp;	
}

 
struct Stack* createStack(unsigned kapasite){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->kapasite = kapasite;
    stack->top = -1;
    stack->s = (char*) malloc(stack->kapasite * sizeof(char));
    //stack->s[0]='\0';
    return stack;
}
 
int isFull(struct Stack* stack){return stack->top == stack->kapasite - 1;}
 
int isEmpty(struct Stack* stack){return stack->top == -1;}
 
void push(struct Stack* stack, char item){
    if (isFull(stack))
        return;
    stack->s[++stack->top] = item;
    //stack->s[stack->top+1]='\0';
    printf("%c pushed to stack\n", item);
}
 
char pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->s[stack->top--];
}

int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char *infixToPost(char*buffer,struct Stack *stack, struct Variables *variables){
	int n,i=0,p=0,dindis=-1,bindis;
	char *postfix,c;
	postfix = (char*) calloc(100,sizeof(char));
	while(variables[i].degisken && dindis==-1){
		if(variables[i].degisken==buffer[0])
			dindis=i;		
		i++;				
	}
	if(dindis==-1){
		variables[i].degisken=buffer[0];
		dindis=i;
	}
	
	i=0;
	while(buffer[i++]!=61);
	bindis=i;
	printf("\n bindis =%d \n",bindis);
	for(i=bindis;i<strlen(buffer);i++){
		printf("Suan okunan:%c\n",buffer[i]);		
		switch(buffer[i]){
			case '(' :
				push(stack,'(');
				break;
			
			case ')' :
				do{	
					c=pop(stack);
					
					if(c=='+' || c=='-' ||c=='*' || c=='/' ){
						postfix[p]=c;
						postfix[++p]=32;
						p++;	
					}
					printf("sayac\n");	
				}
				while(c!='(');
				
				break;
			
			case '+' :case '-' :
					c=pop(stack);
					push(stack,c);	

				if(c=='(')
					push(stack,buffer[i]);
				while(c=='+'||c=='-'){
					c=pop(stack);
					postfix[p]=c;
					postfix[++p]=32;
					p++;
					printf("%c Islemi eklendi\n",c);
				}
				push(stack,buffer[i]);		
				break;
			case '*' :case '/' :
					c=pop(stack);
					push(stack,c);	
					printf("\n%c\n",buffer[i]);
				if(c=='(' || c =='+'||c=='-')			
					push(stack,buffer[i]);
				if(!isEmpty(stack))
					push(stack,buffer[i]);
				break;
			case '=' :
				
				break;
			case ';' :
				
				break;
			case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
				postfix[p]=buffer[i];
				postfix[++p]=32;
				p++;
				printf("Sayi eklendi\n");
				break;
			default:
				printf("");
				break;	
		}
		if(isOperand(buffer[i])){
				postfix[p]=buffer[i];
				postfix[++p]=32;
				p++;
				printf("Degisken eklendi\n");	
			}
		
		postfix[p+1]='\0';
		
		printf("Postfix: %s Yigin: %s\n",postfix,stack->s);
	}
	
	while(!isEmpty(stack)){
		c=pop(stack);
		postfix[p++]=c;
		postfix[p+1]='\0';
		printf("Postfix: %s Yigin: %s\n",postfix,stack->s);
	}
	return postfix;	
}

int main() {
	FILE *fp;
	struct Stack* stack = createStack(100);
	struct Variables* variables = (struct Variables*)  calloc (30,sizeof(struct Variables));
	char buffer[100];
	
 	
	fp=dosyaAc(fp,"input.txt");
	while(!feof(fp)){
		printf("ad");
		fgets(buffer,100,fp);
		infixToPost(buffer,stack,variables);
	}
	
	
/*	if(postfix[0]=='\0')
		printf("NULL?");

	printf("\n\n\nPostfix:%s\n",postfix);*/

	
	
	return 0;
}
