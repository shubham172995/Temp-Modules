#include "ARPTrie.h"
#include <stdio.h>
#include <arpa/inet.h>


extern void
make_trie(struct trie* root, const char contents[6][100][255], int i);
extern char*
ifacelookup(struct trie* root, uint32_t address);

int
main() {
    char* filename = "/proc/net/arp";
    FILE* fp = fopen(filename, "r");
    char contents[6][100][255];
    char* temp;
    int i = 0, j = 0;
    char temp1[20];
    for(i=0;i<9;i++){
        fscanf(fp, "%s", temp1);
        //printf("%s\n", temp1);
    }
    i=0;
    while (fscanf(fp, "%s", contents[i][j]) != EOF) {
        //printf("%d %d %s\n", i, j, contents[i][j]);
        ++i;
        if (i >= 6) {
            i = 0;
            ++j;
        }
        // printf("Hey\n");
    }
    //printf("OUT\n");
    fclose(fp);
    for(int i=0;i<100;i++){
        uint32_t temp=0;
        if(strlen(contents[0][i])){
            //printf("Length is %d\n", strlen(contents[0][i]));
            temp = inet_addr(contents[0][i]);
        }
        printf("%X\n", temp);
    }
    //printf("HEY\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 6; j++) {
            if(strlen(contents[j][i]))
                printf("%s ", contents[j][i]);
        }   
        printf("\n");
    }
    struct trie root = *((struct trie*)malloc(sizeof(struct trie)));
    root.next[0].ptr = NULL;
    root.next[1].ptr = NULL;
    strcpy(root.iface, "");
    printf("Making trie\n");
    for (int i = 0; i < 100; i++) {
        if (strlen(contents[0][i]) == 0)
            break;
        make_trie(&root, contents, i);
    }
    printf("Looking up\n");
    printf("%s\n", ifacelookup(&root, 3055397056));
    return 0;
}