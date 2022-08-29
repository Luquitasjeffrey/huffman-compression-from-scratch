//main.c

#include "InfoPrinter.c"
int main(){
	char input[65536];
	memset(input,0,65536);
	scanf("%s", input);
	CHARLIST list=_initcharlist(input);
	int i=0;
	list=maketree(list);
	Non_compressed_data(input, list);
	Compressed_data(list, input);
	printf("\n\n");
	system("pause");
	return 0;
}
