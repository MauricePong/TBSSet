#ifndef TBSUI_H
#define TBSUI_H
#include "tbsbase.h"
#include "appinit.h"
#include "tbshardware.h"
#if WINDOWSSPACE

#endif
namespace Ui {
class tbsui;
}

class tbsui : public QDialog
{
    Q_OBJECT

public:
    explicit tbsui(QWidget *parent = 0);
    ~tbsui();
	void init_sql(void);
	void updateMac_sql(QString qstrMac);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::tbsui *ui;
    int width;
    int height;
    int width_s;
    int height_s;
	QMessageBox *qbox;
	QSqlDatabase database;
	QSqlQuery *sql_query;
	QThread m_Thread;
	TBShardware *tbshd;
private slots:
    void initForm();
	void threadFinished();

    void on_sli_H_valueChanged(int value);
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif //
