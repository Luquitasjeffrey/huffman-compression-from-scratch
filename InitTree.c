//infotranslate.h
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#ifndef InitTree_C_
#define InitTree_C_

#ifdef __cplusplus
extern "C"{
#endif


typedef struct HCODE{
	short int h_int:2;
}HCODE;

typedef struct CHAR{
	unsigned char character;
	unsigned int  occurence;
	short int     addr;
	HCODE		  huffmancode[32];
}CHAR;

typedef struct CHARLIST{
	CHAR chars[256];
	short int size;	
}CHARLIST;

CHARLIST _initcharlist(char text[65536]){
	CHARLIST out;
	
	//seting zero
	void SetZERO(void){
		out.size=0;
		int i=0;
		for(; i<=255; i++){
			out.chars[i].character=0;
			out.chars[i].occurence=0;
			out.chars[i].addr=-1;
			int j;
			for(j=0; j<=31; j++){
				out.chars[i].huffmancode[j].h_int=-1;
			}
		}
	}
	
	//nested function 0
	bool assigned(unsigned char a, int*arrayposition){
		int i=0;
		for(; i<out.size; i++){
			if(a==out.chars[i].character){
				*arrayposition=i;
				return 1;
			}
		}
		return 0;
	}
	//nested function 1
	void fill(){	
	int i=0;
	while(text[i]!=0){
		int position;
		if(assigned(text[i], &position)){
			out.chars[position].occurence+=1;
		}
		else{
			out.chars[out.size].character=text[i];
			out.chars[out.size].occurence++;
			out.size++;
		}
		i++;
	}
}
	//nested function 2
	bool __sorted(){
		int i=0;
		for(;i<out.size-1; i++){
			if(out.chars[i].occurence>out.chars[i+1].occurence){
			return 0;
			}
		}
		return 1;
	}
	//nested function 3
	void sort(){
		while(!__sorted()){	
			int i=0;
			for(; i<out.size-1; i++){
				if(out.chars[i].occurence>out.chars[i+1].occurence){
					CHAR carry=out.chars[i];
					out.chars[i]=out.chars[i+1];
					out.chars[i+1]=carry;
				}
			}
		}
	}
	//function itself
	SetZERO();
	fill();
	sort();
	return out;
}


#ifdef __cplusplus
}
#endif//cplusplus
#endif//header
