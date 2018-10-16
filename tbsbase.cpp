#include "tbsbase.h"

TBSbase::TBSbase()
{

}

TBSbase::~TBSbase()
{
}

#ifdef Q_OS_WIN //windows
SOCKET TBSbase::udpOpen(QString ipaddr, int ipport)
{
	SOCKET ufd;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	int timeout = 2000;
#else
int TBSbase::udpOpen(QString ipaddr, int ipport)
{
	int ufd = 0;
	struct timeval timeout = { 2,0 };
#endif
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	/*create Socket*/
	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		qDebug() << "fail to socket";
		return 0;
	}

	/*set sockaddr_in*/
	memset(&udpsockaddr, 0, sizeof(udpsockaddr));
	udpsockaddr.sin_family = AF_INET;
	udpsockaddr.sin_port = htons(ipport);
	udpsockaddr.sin_addr.s_addr = inet_addr(ipaddr.toStdString().data());
	len = sizeof(udpsockaddr);
	setsockopt(ufd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(ufd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	return ufd;
}

#ifdef Q_OS_WIN //windows
SOCKET TBSbase::udpClose(SOCKET ufd)
{
#else
int TBSbase::udpClose(int ufd)
{
#endif
	int n = 0;
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	if (ufd > 2) {
#ifdef Q_OS_WIN //windows
		closesocket(ufd);
		WSACleanup();
#else
		::close(ufd);
#endif
		return 0;
	}
	return ufd;
}


#ifdef Q_OS_WIN //windows
SOCKET TBSbase::udpOpen_no(QString ipaddr, int ipport)
{
	SOCKET ufd;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	int timeout = 0;
	unsigned long ul = 1;
#else

int TBSbase::udpOpen_no(QString ipaddr, int ipport)
{
	int ufd = 0;
	struct timeval timeout = { 0,0 };
#endif
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	/*create Socket*/
	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		qDebug() << "fail to socket";
		return 0;
	}
	/*set sockaddr_in*/
	memset(&udpsockaddr, 0, sizeof(udpsockaddr));
	udpsockaddr.sin_family = AF_INET;
	udpsockaddr.sin_port = htons(ipport);
	udpsockaddr.sin_addr.s_addr = inet_addr(ipaddr.toStdString().data());
	len = sizeof(udpsockaddr);
#ifdef Q_OS_WIN //windows
	ioctlsocket(ufd, FIONBIO, (unsigned long *)&ul);//设置成非阻塞模式。
#else
	int flag = fcntl(ufd, F_GETFL, 0);
	flag |= O_NONBLOCK;
	if (fcntl(ufd, F_SETFL, flag) < 0) {
		qDebug("fcntl");
		return ufd;
	}
#endif 
	return ufd;
}
#ifdef Q_OS_WIN //windows
SOCKET TBSbase::getudpfd(void)
#else
int TBSbase::getudpfd(void)
#endif
{
	return udpfd;
}


#ifdef Q_OS_WIN //windows
void TBSbase::setudpfd(SOCKET ufd)
#else
void TBSbase::setudpfd(int ufd)
#endif
{
	udpfd = ufd;
}

int TBSbase::readREG64ByUDP(int subAddr, unsigned char num, unsigned char *rdbuffer)
{
	int n = 0;
	int i = 0;
	int j = 0;
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	// 27bit address
	sendbuff[0] = 0xc0 + (u8)((subAddr & 0x07000000) >> 24);
	sendbuff[1] = (u8)((subAddr & 0x00ff0000) >> 16);
	sendbuff[2] = (u8)((subAddr & 0x0000ff00) >> 8);
	sendbuff[3] = (u8)((subAddr & 0x000000ff));
	n = sendto(udpfd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
		qDebug() << QString("%1->%2->%3:sendto timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	n = recvfrom(udpfd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
		qDebug() << QString("%1->%2->%3:recvfrom timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	for (i = 0; i < 12; i++) {
		//	qDebug("udp_REG64_rd recv:%d=%02x", i, (u8)recvbuff[i]);
		if ((i > 3) && (j < num)) {
			rdbuffer[j] = (u8)recvbuff[i];
			j++;
		}
	}
	return 0;
}

int TBSbase::writeREG64ByUDP(int subAddr, unsigned char num, unsigned char *wtbuffer)
{
	int n = 0;
	int i = 0;
	int j = 0;
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	// 27bit address
	sendbuff[0] = 0x00 + (u8)((subAddr & 0x07000000) >> 24);
	sendbuff[1] = (u8)((subAddr & 0x00ff0000) >> 16);
	sendbuff[2] = (u8)((subAddr & 0x0000ff00) >> 8);
	sendbuff[3] = (u8)((subAddr & 0x000000ff));
	for (i = 0; i < num; i++) {
		sendbuff[i + 4] = wtbuffer[i];
	}
	n = sendto(udpfd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
		qDebug() << QString("%1->%2->%3:sendto timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	memset(recvbuff, 0, 64);
	n = recvfrom(udpfd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
		qDebug() << QString("%1->%2->%3:recvfrom timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//for (int i = 0; i < 12; i++) {
	//qDebug("udp_REG64_wt:recv:%d=%02x", i, (u8)recvbuff[i]);
	//}
	return 0;

}

int TBSbase::readREG(int mode,
	int subAddr,
	unsigned char num,
	unsigned char *rdbuffer)
{
	switch (mode) {
	case 1:
		return readREG64ByUDP(subAddr, num, rdbuffer);
		break;
	default:
		break;
	}
}

int TBSbase::writeREG(int mode,
	int subAddr,
	unsigned char num,
	unsigned char *wtbuffer)
{
	switch (mode) {
	case 1:
		return writeREG64ByUDP(subAddr, num, wtbuffer);
		break;
	default:
		break;
	}
}

int TBSbase::readREG32FromExternalMemoryOnce(int m_addr,
	unsigned char * rdbuff,
	unsigned char num)
{
	int i = 0;
	int mode = 1;
	unsigned char  buff[8] = { 0 };
	if (num == 0) {
		qDebug() << QString("%1->%2->%3:error! (num == 0)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	else if (num > 8) {
		qDebug() << QString("%1->%2->%3:error! (num >8)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...check host free -->......................
	if (-1 == checkHostStatus(1)) {
		qDebug() << QString("%1->%2->%3:wait for host free timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...wt data & cs to low-->...................
	buff[0] = 0x31;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	writeREG(mode, 0x4000 + 0 * 4, 4, buff);	  //cs low;
	//...ck host received data & process-->........
	if (-1 == checkHostStatus(0)) {
		qDebug() << QString("%1->%2->%3:wait for host active timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
		return -1;
	}
	//...cs high................................
	writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
	//...check host work done-->..................
	if (-1 == waitForHostWorkDone())
	{
		qDebug() << QString("%1->%2->%3:wait host work done timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	readREG(mode, 0x4000 + 1 * 4, 4, &buff[0]);
	readREG(mode, 0x4000 + 2 * 4, 4, &buff[4]);
	for (i = 0; i < num; i++)
		rdbuff[i] = buff[i];
	return 0;
}

int TBSbase::writeREG32ToExternalMemoryOnce(int m_addr,
	unsigned char * wtbuff,
	unsigned char num)
{
	int i = 0;
	int mode = 0;
	u8 buff[8] = { 0 };
	if (num == 0) {
		qDebug() << QString("%1->%2->%3:error! (num == 0)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	else if (num > 8)
	{
		qDebug() << QString("%1->%2->%3:error! (num >8)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...check host free -->......................
	if (-1 == checkHostStatus(1)) {
		qDebug() << QString("%1->%2->%3:wait for host free timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...wt data & cs to low-->...................
	for (i = 0; i < num; i++) {
		buff[i] = wtbuff[i];
	}
	writeREG(mode, 0x4000 + 2 * 4, 4, &buff[4]);
	writeREG(mode, 0x4000 + 1 * 4, 4, &buff[0]);

	buff[0] = 0x30;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	writeREG(mode, 0x4000 + 0 * 4, 4, buff); //cs low;
	//...ck host received data & process-->........
	if (-1 == checkHostStatus(0)) {
		qDebug() << QString("%1->%2->%3:wait for host active timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
		return -1;
	}
	writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
	//...check host work done-->..................
	if (-1 == waitForHostWorkDone())
	{
		qDebug() << QString("%1->%2->%3:wait host work done timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	return 0;
}

int TBSbase::readFromExternalMemoryOnce(int mode,
	int m_addr,
	unsigned char * rdbuff,
	unsigned char num)
{
	switch (mode) {
	case 1:
		return readREG32FromExternalMemoryOnce(m_addr, rdbuff, num);
		break;
	default:
		break;
	}
	return 0;
}

int TBSbase::writeToExternalMemoryOnce(int mode,
	int m_addr,
	unsigned char * wtbuff,
	unsigned char num)
{
	switch (mode) {
	case 1:
		return writeREG32ToExternalMemoryOnce(m_addr, wtbuff, num);
		break;
	default:
		break;
	}
	return 0;
}

int TBSbase::readFromExternalMemory(int ram_addr,
	unsigned char * rdbff, 
	int rd_size)
{
	int i = 0;
	int k = 0;
	int g = 0;
	int ret = 0;
	int mode = 1;
	const int x8byte = 8;
	u8 buff[8] = {0};
	if (rd_size <= 8) {
		return readFromExternalMemoryOnce(mode,ram_addr, rdbff, rd_size);
	}
	else if(rd_size > 8){
		k = rd_size / x8byte;
		g = rd_size % x8byte;
		for (i = 0; i < k; i++) {
			ret = readFromExternalMemoryOnce(mode, (ram_addr+i*8), rdbff, x8byte);
			if (-1 == ret) {
				return ret;
			}
		}
		return readFromExternalMemoryOnce(mode, (ram_addr + i * 8), rdbff, g);
	}
	else {
		return 0;
	}
	return 0;
}

int TBSbase::writeToExternalMemory(int ram_addr,
	unsigned char * wtbff,
	int wt_size)
{
	int i = 0;
	int k = 0;
	int g = 0;
	int ret = 0;
	int mode = 1;
	const int x8byte = 8;
	u8 buff[8] = { 0 };
	if (wt_size <= 8) {
		return writeToExternalMemoryOnce(mode, ram_addr, wtbff, wt_size);
	}
	else if (wt_size > 8) {
		k = wt_size / x8byte;
		g = wt_size % x8byte;
		for (i = 0; i < k; i++) {
			ret = writeToExternalMemoryOnce(mode, (ram_addr + i * 8), wtbff, x8byte);
			if (-1 == ret) {
				return ret;
			}
		}
		return writeToExternalMemoryOnce(mode, (ram_addr + i * 8), wtbff, g);
	}
	else {
		return 0;
	}
	return 0;
}

int TBSbase::controlExternalMemory(int mode,
	int addr,
	unsigned char * buff,
	int size)
{
	if (READ == mode) {
		return readFromExternalMemory(addr, buff, size);
	}
	else if (WRITE == mode) {
		return writeToExternalMemory(addr,buff,size);
	}
	else {
		qDebug() << QString("%1->%2->%3:read write mode error!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
	}
	return 0;
}

int TBSbase::readREG32MonopolizeCPUStatus(int m_addr,
	unsigned char * rdbuff,
	unsigned char num)
{
	int i = 0;
	int mode = 1;
	unsigned char  buff[8] = { 0 };
	if (num == 0) {
		qDebug() << QString("%1->%2->%3:error! (num == 0)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	else if (num > 8) {
		qDebug() << QString("%1->%2->%3:error! (num >8)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...check host free -->......................
	if (-1 == checkHostStatus(1)) {
		qDebug() << QString("%1->%2->%3:wait for host free timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...wt data & cs to low-->...................
	buff[0] = 0x33;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	writeREG(mode, 0x4000 + 0 * 4, 4, buff);	  //cs low;
	//...ck host received data & process-->........
	if (-1 == checkHostStatus(0)) {
		qDebug() << QString("%1->%2->%3:wait for host active timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
		return -1;
	}
	//...cs high................................
	writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
	//...check host work done-->..................
	if (-1 == waitForHostWorkDone())
	{
		qDebug() << QString("%1->%2->%3:wait host work done timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	readREG(mode, 0x4000 + 1 * 4, 4, &buff[0]);
	readREG(mode, 0x4000 + 2 * 4, 4, &buff[4]);
	for (i = 0; i < num; i++)
		rdbuff[i] = buff[i];
	return 0;
}

int TBSbase::writeREG32MonopolizeCPUStatus(int m_addr, unsigned char * wtbuff, unsigned char num)
{
	int i = 0;
	int mode = 0;
	u8 buff[8] = { 0 };
	if (num == 0) {
		qDebug() << QString("%1->%2->%3:error! (num == 0)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	else if (num > 8)
	{
		qDebug() << QString("%1->%2->%3:error! (num >8)")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...check host free -->......................
	if (-1 == checkHostStatus(1)) {
		qDebug() << QString("%1->%2->%3:wait for host free timeout")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	//...wt data & cs to low-->...................
	for (i = 0; i < num; i++) {
		buff[i] = wtbuff[i];
	}
	writeREG(mode, 0x4000 + 2 * 4, 4, &buff[4]);
	writeREG(mode, 0x4000 + 1 * 4, 4, &buff[0]);

	buff[0] = 0x32;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	writeREG(mode, 0x4000 + 0 * 4, 4, buff); //cs low;
	//...ck host received data & process-->........
	if (-1 == checkHostStatus(0)) {
		qDebug() << QString("%1->%2->%3:wait for host active timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
		return -1;
	}
	writeREG(mode, 0x4000 + 3 * 4, 4, buff);	  //cs high;
	//...check host work done-->..................
	if (-1 == waitForHostWorkDone())
	{
		qDebug() << QString("%1->%2->%3:wait host work done timeout!")
			.arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
		return -1;
	}
	return 0;
}

int TBSbase::readMonopolizeCPUStatus(int mode,
	int m_addr,
	unsigned char * rdbuff,
	unsigned char num)
{
	switch (mode) {
	case 1:
		return readREG32MonopolizeCPUStatus(m_addr, 
			rdbuff, 
			num);
		break;
	default:
		break;
	}
	return 0;
}

int TBSbase::writeMonopolizeCPUStatus(int mode ,
	int m_addr,
	unsigned char * wtbuff,
	unsigned char num)
{
	switch (mode) {
	case 1:
		return writeREG32MonopolizeCPUStatus(m_addr,
			wtbuff,
			num);
		break;
	default:
		break;
	}
	return 0;
	return 0;
}

int TBSbase::checkHostStatus(int cs)
{
	int i = 0;
	int mode = 1;
	int time = 20;
	u8 tmp[4] = { 0 };

	for (i = 0; i < time; i++) {
		readREG(mode, 0x4000 + 0 * 4, 4, tmp);
		if ((tmp[0] & 0x01) == (u8)(cs)) {
			break;
		}
		else {
			QMSLEEP(1);
		}
	}
	if (time == i) {
		return -1;
	}
	return 0;
}

int TBSbase::waitForHostWorkDone()
{
	int i = 0;
	int mode = 1;
	int time = 20;
	u8 tmp[4] = { 0 };
	for (i = 0; i < time; i++)
	{
		readREG(mode, 0x4000 + 0 * 4, 4, tmp);

		if (0 != (tmp[0] & 0x01)) {
			break;
		}
		else {
			QMSLEEP(1);
		}
	}
	if (time == i) {
		return -1;
	}
	return 0;
}
