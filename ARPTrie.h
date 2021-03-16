#include "b.h"

struct trie {
    struct ref {
        struct trie* ptr;
    } next[2];
    int count;
    char iface[255];
};

/*int indexof(char c){
    if(c=='0')
        return 0;
    else if(c=='1')
        return 1;
    else return -1;
}*/

void
make_trie(struct trie* root, const char contents[6][100][255], int i) {
    struct trie* n = root;
    // printf("Root's address %X\n", root);
    uint32_t address = inet_addr(contents[0][i]);
    /*for (int j = 0; j < 8; j++) {
        if (contents[1][i][j] == '0')
            address = address * 16 + 0;
        else if (contents[1][i][j] == '1')
            address = address * 16 + 1;
        else if (contents[1][i][j] == '2')
            address = address * 16 + 2;
        else if (contents[1][i][j] == '3')
            address = address * 16 + 3;
        else if (contents[1][i][j] == '4')
            address = address * 16 + 4;
        else if (contents[1][i][j] == '5')
            address = address * 16 + 5;
        else if (contents[1][i][j] == '6')
            address = address * 16 + 6;
        else if (contents[1][i][j] == '7')
            address = address * 16 + 7;
        else if (contents[1][i][j] == '8')
            address = address * 16 + 8;
        else if (contents[1][i][j] == '9')
            address = address * 16 + 9;
        else if (contents[1][i][j] == 'A')
            address = address * 16 + 10;
        else if (contents[1][i][j] == 'B')
            address = address * 16 + 11;
        else if (contents[1][i][j] == 'C')
            address = address * 16 + 12;
        else if (contents[1][i][j] == 'D')
            address = address * 16 + 13;
        else if (contents[1][i][j] == 'E')
            address = address * 16 + 14;
        else if (contents[1][i][j] == 'F')
            address = address * 16 + 15;
    }*/
    // address = ntohl(address);
    // printf("%X %s %s\n", address, contents[1][i], contents[0][i]);
    while (address) {
        int rem = address % 2;
        address >>= 1;
        if (n->next[rem].ptr == NULL) {
            // printf("Printing address %X\n", n);
            struct trie* temp = ((struct trie*)malloc(sizeof(struct trie)));
            temp->next[0].ptr = NULL;
            temp->next[1].ptr = NULL;
            temp->count = rem;
            //printf("%d", rem);
            strcpy(temp->iface, "");
            n->next[rem].ptr = temp;
        }
        n = n->next[rem].ptr;
    }
    strcpy(n->iface, contents[5][i]);
    // printf("\n%s %X %X %X\n", n->iface, n, n->next[0].ptr, n->next[0].ptr);
}

char*
ifacelookup(struct trie* root, uint32_t address) {
    struct trie* n = root;
    int rem = address % 2;
    // printf("okay\n");
    // while(strcmp("", n->iface)==0){
    while (n->next[rem].ptr) {
        // printf("okay yes\n");
        address /= 2;
        n = n->next[rem].ptr;
        printf("%d", n->count);
        rem = address % 2;
        // printf("\n%s %X\n", n->iface, n);
    }
    // printf("\n%X %X %X %X\n", address, n, 	n->next[0].ptr, n->next[1].ptr);
    // n=n->next[address%2].ptr;
    printf("\nIn lookup %s\n", n->iface);
    return n->iface;
}