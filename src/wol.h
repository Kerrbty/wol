#ifndef _WAKE_ON_LAN_PACKETS_HEADER_H_
#define _WAKE_ON_LAN_PACKETS_HEADER_H_

// 发送WOL启动机器 
int send_wol(const char* szMac, const char* szIP, unsigned short port = 9);

#endif // _WAKE_ON_LAN_PACKETS_HEADER_H_