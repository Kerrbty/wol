#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "wol.h"

static void fill_magic_buf(void *magic_buf, void *mac)
{
    int i;
    char *ptr;

    ptr = (char*)magic_buf;
    memset(ptr, 0xFF, 6);
    ptr += 6;

    for(i = 0; i < 16; ++i) 
    {
        memcpy(ptr, mac, 6);
        ptr += 6;
    }
}

static unsigned char makebyte(const char* str)
{
    unsigned char b = 0;
    for (int i=0; i<2; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            b = (b<<4)|(str[i]-'0');
        }
        else if ((str[i]|0x20)>='a' && (str[i]|0x20)<='f')
        {
            b = (b<<4)|((str[i]|0x20)-'a'+10);
        }
    }
    return b;
}

static unsigned char* macstr_2_bytes(const char* str, unsigned char* mac)
{
    const char* q = str;
    unsigned char* p = mac;
    for (int i=0; i<6; i++)
    {
        *p++ = makebyte(q);
        q += 2;
        if (*q == ':' || *q == '-')
        {
            q++;
        }
    }
    return mac;
}

// 发送WOL启动机器 
int send_wol(const char* szMac, const char* szIP, unsigned short port)
{
    int s;
    int packet_num = 3;
    unsigned char mac[6] = {0};
    struct sockaddr_in address;
    char magic_buf[6 + 6 * 16] = {0};

    macstr_2_bytes(szMac, mac);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        printf("Failed to initialize socket, code %d\n", errno);
        return -1;
    }

    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(szIP);
    address.sin_port = htons(port);

    if (address.sin_addr.s_addr == 0xFFFFFFFF)
    {
        int optval = 1;
        setsockopt(s, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));
    }

    fill_magic_buf(magic_buf, mac);
    while (packet_num-- > 0) 
    {
        if ( sendto(s, magic_buf, sizeof(magic_buf), 0,
            (struct sockaddr *)&address, sizeof(address)) < 0) 
        {
            unsigned int ipaddr = address.sin_addr.s_addr;
            printf("Failed to send ip (%d.%d.%d.%d:%u) wake-up packet, code %d\n", 
                (unsigned char)ipaddr,
                (unsigned char)(ipaddr>>8),
                (unsigned char)(ipaddr>>16),
                (unsigned char)(ipaddr>>24),
                port, 
                errno);
            close(s);
            return -1;
        }
        sleep(1);
    }
    printf("Wake-up packet sent successfully.\n");
    close(s);
    return 0;
}