#ifndef TBSMESGDLG_H
#define TBSMESGDLG_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class TBSMesgDlg;
}

class TBSMesgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TBSMesgDlg(QWidget *parent = 0);
    ~TBSMesgDlg();
	void displayText(QString  qstmsg);
	void hideBtn(int left, int right, QString qstright);
	void setWinTitle(QString qsttitle);
private slots:
	void on_btn_Left_clicked();
	void on_btn_Right_clicked();
private:
    Ui::TBSMesgDlg *ui;
};

#endif // TBSMESGDLG_H
