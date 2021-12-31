// test.cpp : 定义控制台应用程序的入口点。
//

#include "wol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkMacAddr(const char* str)
{
    size_t len = strlen(str);
    if ( len>=12 && len<=17 )
    {
        unsigned int i=0;
        for (; i<len; i++)
        {
            if (str[i] == ':' || str[i] == '-')
            {
                continue;
            }
            else if (str[i]>='0' && str[i]<='9')
            {
                continue;
            }
            else if ((str[i]|0x20)>='a' && (str[i]|0x20)<='f')
            {
                continue;
            }
            else
            {
                break;
            }
        }
        if (i == len)
        {
            return true;
        }
    }
    return false;
}

bool checkIpAddr(const char* str)
{
    size_t len = strlen(str);
    int ndot = 0;
    if ( len>=7 && len<=15 )
    {
        unsigned int i=0;
        for (; i<len; i++)
        {
            if (str[i] == '.')
            {
                ndot++;
                continue;
            }
            else if (str[i]>='0' && str[i]<='9')
            {
                continue;
            }
            else
            {
                break;
            }
        }
        if (i == len && ndot==3)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    const char* szMac = NULL;
    const char* szIP = NULL;
    unsigned short port = 9;
    printf("Wake-On-LAN Utility %s\r\nCopyright (C) 2000-2013 by kerrbty - All Rights Reserved\r\n\r\n", "1.10");
    for (int i=1; i<argc; i++)
    {
        if (
            strcmp(argv[i], "/?") == 0 ||
            strcmp(argv[i], "-?") == 0 ||
            strcmp(argv[i], "--help") == 0
            )
        {
            szMac = NULL;
            szIP = NULL;
            port = 0;
            break;
        }
        else if (checkMacAddr(argv[i]))
        {
            szMac = argv[i];
        }
        else if (checkIpAddr(argv[i]))
        {
            szIP = argv[i];
        }
        else
        {
            int nport = strtoul(argv[i], NULL, 10);
            if (nport>0 && nport<65536)
            {
                port = nport;
            }
        }
    }

    // ip 没填就广播 
    if (szIP == NULL)
    {
        szIP = "255.255.255.255";
    }

    if ( szMac == NULL )
    {
        puts("Usage:  wol mac_address [adapter_ip] [port]");
        puts("Example: wol 3c7f45d9e56a");
        puts("Example: wol 8C-EC-4B-C0-C3-6A 192.168.2.100");
        puts("Example: wol f1:dc:84:e6:2a:c9 192.168.0.1 12287");
        return -1;
    }

    send_wol(szMac, szIP, port);
    return 0;
}