#ifndef _WAKE_ON_LAN_PACKETS_HEADER_H_
#define _WAKE_ON_LAN_PACKETS_HEADER_H_

// ·¢ËÍWOLÆô¶¯»úÆ÷ 
int send_wol(const char* szMac, const char* szIP, unsigned short port = 9);

#endif // _WAKE_ON_LAN_PACKETS_HEADER_H_