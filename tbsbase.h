#ifndef TBSBASE_H
#define TBSBASE_H
#define NOMINMAX
#define RWNO  128

#include <QDebug>
#include <QDialog>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QDialog>
#include <QTreeWidgetItem>
#include <QMutex>
#include <QThread>
#include <QObject>
#ifdef Q_OS_WIN //windows
#include <windows.h>
#include <conio.h>
#include <initguid.h>
#include <ks.h>
#include <ksmedia.h>
#include <bdatypes.h>
#include <bdamedia.h>
#include <bdaiface.h>
#include <tuner.h>
#include <atlbase.h>
#include <comdef.h>
#include <winsock.h>
#define  QMSLEEP(n)  Sleep(n)

#else           //linux
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <linux/dvb/frontend.h>
#define  QMSLEEP(n)  usleep(1000*n)

#endif
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#ifndef WRITE
#define WRITE            0
#endif
#ifndef READ
#define READ             1
#endif

class RD_WT_PARM {
public:
	int rw;
};

class TBSbase
{
public:
	explicit TBSbase();
	~TBSbase();
#ifdef Q_OS_WIN //windows
	SOCKET  udpOpen(QString ipaddr, int ipport);
	SOCKET  udpClose(SOCKET ufd);
	SOCKET  udpOpen_no(QString ipaddr, int ipport);
	SOCKET  getudpfd(void);
	void    setudpfd(SOCKET ufd);
#else
	int		udpOpen(QString ipaddr, int ipport);
	int		udpClose(int ufd);
	int		udpOpen_no(QString ipaddr, int ipport);
	int		getudpfd(void);
	void    setudpfd(int ufd);
#endif

	int readREG64ByUDP(int subAddr,
		unsigned char num,
		unsigned char *rdbuffer);

	int writeREG64ByUDP(int subAddr,
		unsigned char num,
		unsigned char *wtbuffer);

	int readREG(int mode,
		int subAddr,
		unsigned char num,
		unsigned char *rdbuffer);

	int writeREG(int mode,
		int subAddr,
		unsigned char num,
		unsigned char *rdbuffer);

	int readREG32FromExternalMemoryOnce(int m_addr,
		unsigned char * rdbuff,
		unsigned char num);

	int writeREG32ToExternalMemoryOnce(int m_addr,
		unsigned char * wtbuff,
		unsigned char num);

	int readFromExternalMemoryOnce(int mode,
		int m_addr,
		unsigned char * rdbuff,
		unsigned char num);

	int writeToExternalMemoryOnce(int mode,
		int m_addr,
		unsigned char * wtbuff,
		unsigned char num);
	int readFromExternalMemory(int ram_addr,
		unsigned char *rdbff,
		int rd_size);
	int writeToExternalMemory(int ram_addr,
		unsigned char *wtbff,
		int wt_size);
	int controlExternalMemory(int mode,
		int addr,
		unsigned char *buff,
		int size);
	int readREG32MonopolizeCPUStatus(int m_addr,
		unsigned char * rdbuff,
		unsigned char num);
	int writeREG32MonopolizeCPUStatus(int m_addr,
		unsigned char * wtbuff,
		unsigned char num);
	int readMonopolizeCPUStatus(int mode,int m_addr, 
		unsigned char * rdbuff,
		unsigned char num);
	int writeMonopolizeCPUStatus(int mode,int m_addr,
		unsigned char * wtbuff, 
		unsigned char num);

	int checkHostStatus(int cs);
	int waitForHostWorkDone();
private:
	struct sockaddr_in udpsockaddr;
#ifdef Q_OS_WIN //windows
	//net
	SOCKET		udpfd;
	WSADATA		wsaData;
	int			len;
#else
	int			udpfd;
	socklen_t	len;
#endif
};

#endif // TBSBASE_H
