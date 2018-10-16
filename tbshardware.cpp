#include "tbshardware.h"

TBShardware::TBShardware()
{
	m_bRun = true;
	runmode = 0;
	readmode = 0;
	writemode = 0;
}

TBShardware::~TBShardware()
{

}
void TBShardware::start()
{
	while (1) {
		QMutexLocker locker(&m_Mutex);
		switch (runmode) {
		case TBS_READ_FUNC:
			readBuffer(readmode);
			break;
		case TBS_WRITE_FUNC:
			writeBuffer(writemode);
			break;
		default:
			QMSLEEP(1);
			break;
		}
		runmode = 0;
		if (false == m_bRun) {
			break;
		}
		qDebug() << QString("%1->%2->%3")
			.arg(__FILE__)
			.arg(__LINE__)
			.arg(__FUNCTION__);
	}

}

void TBShardware::stop()
{
	QMutexLocker locker(&m_Mutex);
	m_bRun = false;
}

int TBShardware::readBuffer(int rmode)
{
	switch (rmode) {
	case 0:
		break;
	default:
		break;
	}
	return 0;
}

int TBShardware::writeBuffer(int wmode)
{
	switch (wmode) {
	case 0:
		break;
	default:
		break;
	}
	return 0;
}

int TBShardware::getRunMode()
{
	return runmode;
}


void TBShardware::setRunMode(int mode)
{
	runmode = mode;
}

int TBShardware::getReadMode()
{
	return readmode;
}

void TBShardware::setReadMode(int mode)
{
	readmode = mode;
}

int TBShardware::getWriteMode()
{
	return writemode;
}

void TBShardware::setWriteMode(int mode)
{
	writemode = mode;
}

#ifdef Q_OS_WIN //windows
SOCKET TBShardware::gethdudpfdMode()
{
	return getudpfd();
}

void TBShardware::sethdudpfdMode(SOCKET f_hdudpfd)
{
	setudpfd(f_hdudpfd);
}
SOCKET TBShardware::openNetSocket(QString ip, int port)
{
	return udpOpen(ip, port);
}
SOCKET TBShardware::closeNetSocket(SOCKET socketfd)
{
	return udpClose(socketfd);
}
#else
int TBShardware::gethdudpfdMode()
{
	return getudpfd();
}
void TBShardware::sethdudpfdMode(int f_hdudpfd)
{
	setudpfd(f_hdudpfd);
}
int TBShardware::openNetSocket(QString ip, int port)
{
	return udpOpen(ip, port);
}
int TBShardware::closeNetSocket(int socketfd)
{
	return udpClose(socketfd);
}
#endif




RD_WT_PARM  TBShardware::getHardWareParm(void)
{
	return rwparm;
}

void TBShardware::setHardWareParm(RD_WT_PARM  rw)
{
	rwparm = rw;
}

