#include "tbshardware.h"

TBShardware::TBShardware()
{
	m_bRun = true;
	runmode = 0;
	readmode = 0;
	writemode = 0;
	tbsmsg = new TBS_Msg_Type();
	tbsmsg->type = 0;
	tbsmsg->btnL = 0;
	tbsmsg->btnR = 0;
	tbsmsg->btnRtext = QString("OK");
	tbsmsg->tilie = QString("");
	tbsmsg->displaytext = QString("");
}

TBShardware::~TBShardware()
{
	if (tbsmsg) {
		delete tbsmsg;
	}
}
void TBShardware::start()
{
	int ret = -1;
	//while (1) {
	QMutexLocker locker(&m_Mutex);
		switch (runmode) {
		case TBS_READ_FUNC:
			ret = readBuffer(readmode);
			break;
		case TBS_WRITE_FUNC:
			ret = writeBuffer(writemode);
			break;
		default:
			ret = -1;
			break;
		}
		runmode = 0;
		if (0 == ret) {
			tbsmsg->type = 1;
			tbsmsg->btnL = 0;
			tbsmsg->btnR = 1;
			tbsmsg->btnRtext = QString("OK");
			tbsmsg->tilie = QString("information");
			tbsmsg->displaytext = QString("Success");
			emit sigDisplayMsgUI(tbsmsg);
		}
		else if (-1 == ret) {
			tbsmsg->type = 1;
			tbsmsg->btnL = 0;
			tbsmsg->btnR = 1;
			tbsmsg->btnRtext = QString("OK");
			tbsmsg->tilie = QString("error");
			tbsmsg->displaytext = QString("Failure");
			emit sigDisplayMsgUI(tbsmsg);
		}
		else if (1 == ret) {
			tbsmsg->type = 1;
			tbsmsg->btnL = 0;
			tbsmsg->btnR = 0;
			tbsmsg->btnRtext = QString("");
			tbsmsg->tilie = QString("information");
			tbsmsg->displaytext = QString("Configuring now,please wait..");
			emit sigDisplayMsgUI(tbsmsg);
		}
	//	if (false == m_bRun) {
	//		break;
	//	}
		//qDebug() << QString("%1->%2->%3->%4")
		//	.arg(__FILE__)
		//	.arg(__LINE__)
		//	.arg(__FUNCTION__)
		//	.arg((int)QThread::currentThreadId());
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

