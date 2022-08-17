//huffman compression algorithm
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct charinfo{
	unsigned char	character;
	unsigned long long int 	occurence;
	unsigned int 	alloc;
	short int		huffmancode[8];
}charinfo;
typedef struct charlist{
	charinfo charlist[64];
	unsigned short int	size;
	short int			predecessor;
	short int			SucesorRitgt;
	short int			SucesorLeft;
	short int			completed;
	
}charlist;

typedef struct MASTER{
charlist MASTER[128]; //in the worst case scenario i will need 127 mini-trees		
}MASTER;
//global variable


charlist SetZERO(void){
	charlist SetList;
	SetList.predecessor=-1;
	SetList.SucesorRitgt=-1;
	SetList.completed=-1;
	SetList.SucesorLeft=-1;
	SetList.size=0;
	for(int i=0; i<=64; i++){
		SetList.charlist[i].character=NULL;
		SetList.charlist[i].occurence=0;
	}
	
	return SetList;
}

charlist initialize_charlist(unsigned char input[4096], unsigned int* NumberOfChars){
	charlist output=SetZERO();
	int i=0,numberofchars=0;
	while((input[i]!=NULL || input[i+1]!=NULL)){
		int j=0;
		bool assigned=0;
		while(j<numberofchars){
			if(input[i]==output.charlist[j].character){
				assigned=1;
				output.charlist[j].occurence++;
			}
			j++;
		}
		if(!assigned){
			output.charlist[j].character=input[i];
			output.charlist[j].alloc=j;
			output.charlist[j].occurence++;
			numberofchars++;
		}
		i++;
	}
	*NumberOfChars=numberofchars-1;
	output.size=numberofchars;
	output.completed=0;
	return output;
}

bool sorted(charlist sort, unsigned int number){
for(int i=0; i<number; i++){
if(sort.charlist[i].occurence>sort.charlist[i+1].occurence){
	return 0;
}
}
return 1;
}

charlist SORT(charlist CharsList, unsigned int NumberOfChars){
	while(!sorted(CharsList,NumberOfChars)){
	for(int i=0; i<NumberOfChars; i++){
		if(CharsList.charlist[i].occurence>CharsList.charlist[i+1].occurence){
			charinfo carry=CharsList.charlist[i+1];
			CharsList.charlist[i+1]=CharsList.charlist[i];
			CharsList.charlist[i]=carry;
		}
	}
}
		return CharsList;
}

void non_compressed_data(charlist CharList, unsigned int NumberOfChars, unsigned char text[4096]){
	printf("\nThis is the non compressed data:");
	unsigned int a=NumberOfChars,k=0;
	while(a>=1){
		a=a/2;
		k++;
	}
	unsigned int length=0;
	int k2=0;
	while(text[k2]!=NULL){
		k2++;
	}
	k2--;
	printf("\nDictionary:");
	for(int i=0; i<=NumberOfChars; i++){
		int ii=i;
		printf("\n%c=",CharList.charlist[i].character);
		for(int j=0; j<k; j++){
			printf("%i",(ii%2));
			ii=ii/2;
		}
	}
	printf("\nNon compressed text is:\n");
	for(int i=0; i<=k2; i++){
		int ii=0;
		while(text[i]!=CharList.charlist[ii].character){
			ii++;
		}
		for(int j=0; j<k; j++){
			printf("%i",(ii%2));
			ii=ii/2;
		}
	}
}



short int is_complete(charlist check, MASTER tree){
	
	if(check.SucesorLeft!=-1 && check.SucesorRitgt!=-1){	
	if((tree.MASTER[check.SucesorLeft].completed==1) && (tree.MASTER[check.SucesorRitgt].completed==1)){
		return 1;
	}
}	
	if(check.size==1){
		return 1;
	}
	return 0;
}

unsigned int CharListSum(charlist a, unsigned int since, unsigned int until){
	unsigned int sum=0;
	for(int i=since; i<=until; i++){
		sum=sum+a.charlist[i].occurence;
	}
	return sum;
}

unsigned int CrackTree(charlist halflist, int stop){
	unsigned int i=0;
	while(CharListSum(halflist, 0, i)<=CharListSum(halflist, i+1, stop)){
		i++;
	}
	if(i==stop){
		i--;
	}
	return i;
}




MASTER select_next(unsigned int* Outs, unsigned int* reference, MASTER tree){
	//first the function will check if the tree is not complete
	
	for(int i=0; i<=4; i++){
		for(int j=*Outs; j>=0; j--){
			tree.MASTER[j].completed=is_complete(tree.MASTER[j], tree);
		}
	}
	//if MASTER[0] is complete the function will do nothing;
	*Outs+=2;
	//then "climb" the tree until you reach a non completed ramification
	//go right all i can until i reach or a zero tree (completed=-1)
	if(tree.MASTER[0].completed==0){
	short int i=0;
	//climbing the tree
	while(tree.MASTER[i].SucesorLeft!=-1){ //it doesnt matters if i use right or left.
		if(tree.MASTER[tree.MASTER[i].SucesorRitgt].completed <=0){
			i=tree.MASTER[i].SucesorRitgt;
		}
		else{
			i=tree.MASTER[i].SucesorLeft;
		}
		
		//i suspected.
	}
	*reference=i;
}	
	return tree;
}

charlist MakeHuffmannTree(unsigned int Outs, unsigned int reference, MASTER tree){
	/*
	A "mother" tree is completed if its only one character long OR if all its "successor" pseudo trees are completed.
	the father tree is the MASTER tree that contains all the pseudo trees, and to be complete must been complete all its "sons".
	MakeHuffmannTree() will be a recursive function that will calls itself until the "father" tree is completed.
	it will start going right until its complete, and it will always go to the rightest possible ramification.
	MASTER[128] will be the allocation where the function will write.
	MASTER[0] is the father tree, and it´s untouchable until all the ramifications are complete
	*/
	//printf("\ncracking tree");
	
	while(tree.MASTER[0].completed!=1){
	int i=CrackTree(tree.MASTER[reference], tree.MASTER[reference].size);
	tree.MASTER[Outs].predecessor=reference;
	tree.MASTER[Outs].size=i;
	tree.MASTER[Outs].SucesorLeft=-1;
	tree.MASTER[Outs].SucesorRitgt=-1;
	tree.MASTER[Outs+1].predecessor=reference;
	tree.MASTER[Outs+1].size=tree.MASTER[reference].size-i;
	tree.MASTER[Outs+1].SucesorLeft=-1;
	tree.MASTER[Outs+1].SucesorRitgt=-1;
	tree.MASTER[reference].SucesorLeft=Outs;
	tree.MASTER[reference].SucesorRitgt=Outs+1;
	for(int j=0; j<=i; j++){
		tree.MASTER[Outs].charlist[j]=tree.MASTER[reference].charlist[j];
	}
	for(int j=i; j<=tree.MASTER[reference].size; j++){
		tree.MASTER[Outs+1].charlist[j-i]=tree.MASTER[reference].charlist[j];
	}
	
	tree.MASTER[Outs].completed=is_complete(tree.MASTER[Outs],tree);
	tree.MASTER[Outs+1].completed=is_complete(tree.MASTER[Outs+1],tree);
	tree.MASTER[reference].completed=is_complete(tree.MASTER[reference],tree);
	tree=select_next(&Outs, &reference, tree);
	//printf("\ninfinite loop...");
	//printf("recursion... %i and %i, sizes: %i, %i, %i", Outs, reference, tree.MASTER[reference].size, tree.MASTER[Outs].size, tree.MASTER[Outs+1].size);
}

	short int root[8];
	for(int p=0; p<=Outs; p++){
		if(tree.MASTER[p].size==1){	
		//printf("\n%c=",  tree.MASTER[p].charlist[0].character);
		int I=0;
		int i=p;
		int l=tree.MASTER[p].charlist[0].alloc;
		tree.MASTER[0].charlist[l]=tree.MASTER[p].charlist[0];
		//printf(" %c",  tree.MASTER[0].charlist[l].character);
		//printf("(%i)",l);
		for(int j=0; j<=8; j++){
			tree.MASTER[0].charlist[l].huffmancode[j]=-1;
		}
		while(i!=0){
			
			if(tree.MASTER[tree.MASTER[i].predecessor].SucesorRitgt==i){
				//esto se leería en orden inversoo
				//printf("1");
				tree.MASTER[0].charlist[l].huffmancode[I]=1;
			}
			else{
				//printf("0");
				tree.MASTER[0].charlist[l].huffmancode[I]=0;
			}
			
			i=tree.MASTER[i].predecessor;
			I++;
			//printf("\n%i",i);
		}
		tree.MASTER[0].charlist[l].character=tree.MASTER[p].charlist[0].character;
	}
	}
	for(int p=0; p<=Outs; p++){
		if(tree.MASTER[p].size==1){
	tree.MASTER[0].charlist[tree.MASTER[p].charlist[0].alloc].character=tree.MASTER[p].charlist[0].character;		
	}
}
	
	
	
	
	return tree.MASTER[0];	
}


void compress_data(charlist ListSorted, unsigned char text[4096]){
	
	if(1){
	MASTER tree;
	for(int i=1; i<=127; i++){
		tree.MASTER[i]=SetZERO();
		tree.MASTER[i].completed=-1;
	}
	tree.MASTER[0]=ListSorted;
	ListSorted=MakeHuffmannTree(1, 0, tree);
	}
	
	printf("\nthe dictionary is (little endian):");
	for(int j=0; j<ListSorted.size; j++){
		printf("\n%c= ",ListSorted.charlist[j].character);
		int p=0;
		while(ListSorted.charlist[j].huffmancode[p]!=-1){
			printf("%i",ListSorted.charlist[j].huffmancode[p]);
			p++;
		}
	}

	int i=0;
	
	printf("\n\nthe compressed text is:\n");
	while(text[i]!=NULL){
		int j=0;
		while(ListSorted.charlist[j].character!=text[i]){
			j++;
		}
		int l=0;
		while(ListSorted.charlist[j].huffmancode[l+1]!=-1){
			l++;
		}
		for(; l>=0; l--){
			printf("%i", ListSorted.charlist[j].huffmancode[l]);
		}
		i++;
	}
	
	//printf("\ntree1\n%i\n%i",tree.MASTER[1].size,tree.MASTER[2].size); //ok, i will assume it works
}



int main(void){
	unsigned char input[4096];
	memset(input,NULL,4096);
	system("color 2");
	printf("input text:\n");
	scanf("%s",input);
	unsigned int NumberOfChars;
	charlist CharList=initialize_charlist(input, &NumberOfChars);
	CharList=SORT(CharList,NumberOfChars);
	non_compressed_data(CharList,NumberOfChars,input);
	printf("\nthe tree size is: %u",CharList.size);
	/*
	unsigned int a=CrackTree(CharList, 0, NumberOfChars);
	printf("\nthe tree breakpoint is: %u and the partial sums are %u and %u", a, CharListSum(CharList, 0, a), CharListSum(CharList, a+1, NumberOfChars));
	*/
	
	compress_data(CharList, input);
	printf("\n");
	system("pause");
	return 0;
}
