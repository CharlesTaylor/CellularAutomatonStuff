#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define LEN 80
unsigned char rule;
char eval(char a, char b, char c){
	unsigned char mask = 0X01;
	unsigned char val = 0;
	unsigned int i;
	a=a&&mask;
	b=b&&mask;
	c=c&&mask;

	val = val | a;
	val= val << 1;
	val = val | b;
	val= val << 1;
	val = val | c;

	for(i=0;i<8;i++){
		if(i==val)
		{
			mask = mask << i;
			return (rule & mask)?1:0;
		}
	}

	return 0XFF;
}
int main(int argc, char** args){
	char toprint[LEN+1];
	char state[LEN];
	char nextstate[LEN];
	int loop = 10;
	toprint[LEN]='\0';

	srand(time(NULL));
	if(argc==1){
		rule=0XAA;
	}else{
		rule = ((unsigned char)atoi(args[1]));
		if(argc==3){
			loop=atoi(args[2]);
		}	
	}
	
	int i;
	int j;
	for(i =0;i<LEN;i++){
		state[i]= 0;

	}

	for(i =0;i<loop;i++){
		nextstate[0]=eval(0,state[0],state[1]);
		for(j =1;j<LEN-1;j++){
			nextstate[j]=eval(state[j+1],state[j],state[j-1]);
		}
		nextstate[LEN-1]=eval(state[LEN-2],state[LEN-1],0);
		for(j=0;j<LEN;j++){
			toprint[j]=state[j]?'#':' ';
			state[j]=nextstate[j];
		}	
		printf("%s\n",toprint);
	}
	return 0;
}
