#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <time.h>
#include <arpa/inet.h>
#include "sys/types.h"
#include <netinet/ip.h>
#include <netinet/tcp.h>
#define NETMAP_WITH_LIBS
#include <net/netmap_user.h>
#define SIZE_ETHERNET 14


typedef unsigned int __u32;

int main(){
        char netmap_ifname1[64];
        const char *interface1 = "re0";
        unsigned int ring_id1;
        struct nm_desc* d1;
        snprintf(netmap_ifname1, sizeof(netmap_ifname1), "netmap:%s", interface1);
        const char* interface2 = "ue1";
        char netmap_ifname2[64];
        unsigned int ring_id2;
        struct nm_desc* d2;
        snprintf(netmap_ifname2, sizeof(netmap_ifname2), "netmap:%s", interface2);
        d1 = nm_open(netmap_ifname1, NULL, 0, 0);
        if(!d1){
                perror("nm_open()\n");
                exit(2);
        }
        d2 = nm_open(netmap_ifname2, NULL, 0, 0);
        if(!d2){
                perror("nm_open() 2\n");
                exit(2);
        }
        struct netmap_ring *ring_in, *ring_out;
        unsigned int i, len;
        char *buf;
        printf("beginning the processss!");
        //ioctl(d1->fd, NIOCRXSYNC);
        //ioctl(d2->fd, NIOCTXSYNC);

        printf("Entering the phase where you get packets from 10.0.0.10 and sending to myself\n");
        while(1){
                sleep(3);
                printf("Calling ioctl for rx sync and return value is %d\n", ioctl(d1->fd, NIOCRXSYNC));
                int ri1 = d1->cur_rx_ring;
        int ri2 = d2->cur_tx_ring;
        ring_in = NETMAP_RXRING(d1->nifp, ri1);
        ring_out = NETMAP_TXRING(d2->nifp, ri2);
        while(!nm_ring_empty(ring_in)){
                i = ring_in->cur;
                u_int idx = ring_in->slot[i].buf_idx;
                buf = (char *)NETMAP_BUF(ring_in, idx);
                len = ring_in->slot[i].len;

                printf("Lengths are %d and %d", len, ring_in->nr_buf_size);
                ring_in->head = ring_in->cur = nm_ring_next(ring_in, i);
                
                struct ip *temp;
                //printf("Hello guys. The sizes are %d and %d\n", sizeof(ip_info->saddr));
                temp = (struct iphdr *)(buf + SIZE_ETHERNET);
                /*ip_info->saddr = temp->saddr;
                //ip_info->daddr = temp->daddr;
                ip_info->protocol = temp->protocol;
                //ip_info->ihl = temp->ihl;
                ip_info->tos = temp->tos;
                ip_info->check = temp->check;
                ip_info->tot_len = temp->tot_len;*/

                printf("\nI got the packet. Here are some values %d %d\n", temp->ip_len, temp->ip_src);

                //__u32 *newSrc = (__u32*)malloc(sizeof(__u32));

                //nat(buf, newSrc, temp);

                int k = ring_out->cur;
                printf("Running nm_inject and the return value is %d", nm_inject(d2, buf, len));

                printf("The return value of ioctl for tx sync is %d\n", ioctl(d2->fd, NIOCTXSYNC));

        }
        }
        return 0;
}