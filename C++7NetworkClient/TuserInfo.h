#pragma once

//本机环境为小端序
struct TUserInfo
{
	char pszUser[32];
	char pszPassword[32];
	char pszAddressIp[64];
	short nPort; 
	char pRsv[2];
};

struct TMsgHead
{
	char cHead;
	char pRsv[3];
	int nLen;
};
