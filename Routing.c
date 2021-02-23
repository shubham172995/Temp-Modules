#include<stdio.h>
#include "trie.h"

extern void make_trie(struct trie* root, const char contents[11][5][255], int i);
extern char* ifacelookup(struct trie* root, int address);

int main(){
	char* filename = "/proc/net/route";
	FILE* fp = fopen(filename, "r");
	char contents[11][5][255];
	char* temp;
	int i=0, j=0;
	while(fscanf(fp, "%s", contents[i][j])!=EOF){
		++i;
		if(i>=11){
			i=0;
			++j;
		}
		//printf("Hey\n");
	}
	fclose(fp);
	for(int i=0;i<5;i++){
		for(int j=0;j<11;j++){
			printf("%s ", contents[j][i]);
		}
		printf("\n");
	}
	struct trie root = *((struct trie*)malloc(sizeof(struct trie)));
	root.next[0].ptr = NULL;
	root.next[1].ptr = NULL;
	strcpy(root.iface, "");
	printf("Making trie\n");
	for(int i=1;i<5;i++){
		if(contents[0][i][0]==NULL)
			break;
		make_trie(&root, contents, i);
	}
	printf("Looking up\n");
	printf("%s\n", ifacelookup(&root, 1043089));
	return 0;
}