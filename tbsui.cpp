#pragma execution_character_set("utf-8")
#include "tbsui.h"
#include "iconhelper.h"
#include "ui_tbsui.h"
#define  ITMEL(n)   ITMEL##n

tbsui::tbsui(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::tbsui)
{
	ui->setupUi(this);
	this->initForm();
	//init_sql();
}

tbsui::~tbsui()
{
	if (tbshd)
	{
		tbshd->stop();
		m_Thread.quit();
		m_Thread.wait();
		qDebug("22222222222233");
	}
	//database.close();
	//delete sql_query;
	delete ui;
}

void tbsui::init_sql(void)
{
	//1.create sql
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		database = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("TBSMAC.db");
	}

	//2.open sql
	if (!database.open())
	{
		qDebug() << "Error: Failed to connect database." << database.lastError();
	}

	//3.create from
	sql_query = new QSqlQuery();
	QString create_sql = "create table macValue (id int,MAC varchar(20))";
	sql_query->prepare(create_sql);
	if (!sql_query->exec())
	{
		qDebug() << "Error: Fail to create table." << sql_query->lastError();
	}
	else
	{
		qDebug() << "Table created!";
	}

	//4.select_sql

	QString select_sql = "select * from macValue";
	if (!sql_query->exec(select_sql))
	{
		qDebug() << sql_query->lastError();
	}
	else
	{
		if (!(sql_query->next()))
		{
			//5.insert_sql
			QString insert_sql = "insert into macValue values (?, ?)";
			sql_query->prepare(insert_sql);
			sql_query->addBindValue(1);
			sql_query->addBindValue("00:22:ab:00:00:00");
			if (!sql_query->exec())
			{
				qDebug() << sql_query->lastError();
			}
			else
			{
				qDebug() << "inserted one!";
			}
			//	sql_query->addBindValue(2);
			//	sql_query->addBindValue("00:22:ab:00:00:00");
			//	if (!sql_query->exec())
			//	{
			//		qDebug() << sql_query->lastError();
			//	}
			//	else
			//	{
			//		qDebug() << "inserted two!";
			//	}

		}
	}

	qDebug() << "init sql over";

}

void tbsui::updateMac_sql(QString qstrMac)
{
	QString update_sql = "update macValue set MAC = :MAC where id = :id";
	sql_query->prepare(update_sql);
	sql_query->bindValue(":MAC", qstrMac.toStdString().data());
	sql_query->bindValue(":id", 1);
	if (!sql_query->exec())
	{
		qDebug() << sql_query->lastError();
	}
	else
	{
		qDebug() << "one updated!";
	}
	//	sql_query->bindValue(":MAC", nqstrMac.toStdString().data());
	//	sql_query->bindValue(":id", 2);
	//	if (!sql_query->exec())
	//		qDebug() << sql_query->lastError();
	//	}
	//	else
	//	{
	//		qDebug() << "two updated!";
	//	}
}


bool tbsui::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick) {
		if (watched == ui->widgetTitle) {
			on_btnMenu_Max_clicked();
			return true;
		}
	}

	return QWidget::eventFilter(watched, event);
}

void tbsui::initForm()
{
	this->setProperty("form", true);
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	//QPixmap icon(":/image/logo.png");
	QPixmap icon(":/qss/psblack/uilogo/logo.png");
	ui->labIco->setPixmap(icon);
	ui->labIco->resize(icon.width(), icon.height());
	//IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf099), 30);
	IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
	IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
	IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
	// IconHelper::Instance()->setIcon(ui->lab_enico, QChar(0xf069), 30);
	 //ui->widgetMenu->setVisible(false);
	ui->widgetTitle->installEventFilter(this);
	ui->widgetTitle->setProperty("form", "title");
	ui->widgetTop->setProperty("nav", "top");
	//ui->labTitle->setText("TBS CAPTURE");
	ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
	this->setWindowTitle(ui->labTitle->text());
	//ui->stackedWidget->setStyleSheet("QLabel{font:10pt;}");
	//单独设置指示器大小
	int addWidth = 20;
	int addHeight = 10;
	int rbtnWidth = 15;
	int ckWidth = 13;
	int scrWidth = 12;
	int borderWidth = 3;
	QStringList qss;
	qss.append(QString("QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{width:%1px;}").arg(addWidth));
	qss.append(QString("QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,"
		"QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{width:%1px;height:%1px;right:2px;}").arg(addHeight));
	qss.append(QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth));
	qss.append(QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth));
	qss.append(QString("QScrollBar:horizontal{min-height:%1px;border-radius:%2px;}QScrollBar::handle:horizontal{border-radius:%2px;}"
		"QScrollBar:vertical{min-width:%1px;border-radius:%2px;}QScrollBar::handle:vertical{border-radius:%2px;}").arg(scrWidth).arg(scrWidth / 2));
	qss.append(QString("QWidget#widget_top>QToolButton:pressed,QWidget#widget_top>QToolButton:hover,"
		"QWidget#widget_top>QToolButton:checked,QWidget#widget_top>QLabel:hover{"
		"border-width:0px 0px %1px 0px;}").arg(borderWidth));
	qss.append(QString("QWidget#widgetleft>QPushButton:checked,QWidget#widgetleft>QToolButton:checked,"
		"QWidget#widgetleft>QPushButton:pressed,QWidget#widgetleft>QToolButton:pressed{"
		"border-width:0px 0px 0px %1px;}").arg(borderWidth));
	this->setStyleSheet(qss.join(""));
	//	connect(ui->tree_Dev, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(showSelectedImage(QTreeWidgetItem*, int)));
		//th = new threadTbs();
		//th->start();
	width_s = this->size().width();
	height_s = this->size().height();
	width = width_s;
	height = height_s;
	tbshd = NULL;
	tbshd = new TBShardware();
	tbshd->moveToThread(&m_Thread);
	connect(&m_Thread, SIGNAL(started()), tbshd, SLOT(start()));
	connect(&m_Thread, SIGNAL(finished()), tbshd, SLOT(deleteLater()));
	connect(&m_Thread, SIGNAL(finished()), this, SLOT(threadFinished()));
	m_Thread.start();
}




void tbsui::on_btnMenu_Min_clicked()
{
	showMinimized();
}

void tbsui::on_btnMenu_Max_clicked()
{
	static bool max = false;
	static QRect location = this->geometry();

	if (max) {
		this->setGeometry(location);
		width = width_s;
		height = height_s;
	}
	else {
		location = this->geometry();
		this->setGeometry(qApp->desktop()->availableGeometry());
		width = this->size().width();
		height = this->size().height();
	}

	this->setProperty("canMove", max);
	max = !max;
}

void tbsui::on_btnMenu_Close_clicked()
{
	if (tbshd)
	{
		tbshd->stop();
		m_Thread.quit();
		m_Thread.wait();
		tbshd = NULL;
	}
	close();
}

void tbsui::threadFinished()
{
	qDebug() << QString("%1->%2->%3")
		.arg(__FILE__)
		.arg(__LINE__)
		.arg(__FUNCTION__);
}

void tbsui::on_sli_H_valueChanged(int value)
{
	qDebug() << value;
	this->setStyleSheet(QString("font:%1pt;").arg(value));
	ui->labTitle->setFont(QFont("Microsoft Yahei", 20 - 10 + value));
	//qDebug()<<width<<"*"<<height;
	this->resize(width, height);
	QString qst = QString("QCheckBox::indicator{ width: %1px; height: %1px; }").arg(4 + value);//改变大小
}

