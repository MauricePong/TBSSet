/********************************************************************************
** Form generated from reading UI file 'tbsui.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TBSUI_H
#define UI_TBSUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tbsui
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labIco;
    QLabel *labTitle;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetMenu;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Close;
    QPushButton *btnMenu_Max;
    QStackedWidget *stackedWidget;
    QWidget *page2;
    QGridLayout *gridLayout_4;
    QSlider *sli_H;
    QWidget *UpdateWdiget;
    QGridLayout *gridLayout;

    void setupUi(QDialog *tbsui)
    {
        if (tbsui->objectName().isEmpty())
            tbsui->setObjectName(QStringLiteral("tbsui"));
        tbsui->resize(1000, 683);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbsui->sizePolicy().hasHeightForWidth());
        tbsui->setSizePolicy(sizePolicy);
        tbsui->setLayoutDirection(Qt::LeftToRight);
        tbsui->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(tbsui);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widgetTitle = new QWidget(tbsui);
        widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(widgetTitle);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        labIco = new QLabel(widgetTitle);
        labIco->setObjectName(QStringLiteral("labIco"));
        labIco->setStyleSheet(QStringLiteral(""));
        labIco->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labIco);

        labTitle = new QLabel(widgetTitle);
        labTitle->setObjectName(QStringLiteral("labTitle"));
        labTitle->setStyleSheet(QStringLiteral(""));
        labTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labTitle);

        widgetTop = new QWidget(widgetTitle);
        widgetTop->setObjectName(QStringLiteral("widgetTop"));
        horizontalLayout_3 = new QHBoxLayout(widgetTop);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_2->addWidget(widgetTop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widgetMenu = new QWidget(widgetTitle);
        widgetMenu->setObjectName(QStringLiteral("widgetMenu"));
        gridLayout_2 = new QGridLayout(widgetMenu);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 3);

        btnMenu_Min = new QPushButton(widgetMenu);
        btnMenu_Min->setObjectName(QStringLiteral("btnMenu_Min"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy2);
        btnMenu_Min->setMinimumSize(QSize(30, 30));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Min, 0, 1, 1, 1);

        btnMenu_Close = new QPushButton(widgetMenu);
        btnMenu_Close->setObjectName(QStringLiteral("btnMenu_Close"));
        sizePolicy2.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy2);
        btnMenu_Close->setMinimumSize(QSize(30, 30));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Close, 0, 3, 1, 1);

        btnMenu_Max = new QPushButton(widgetMenu);
        btnMenu_Max->setObjectName(QStringLiteral("btnMenu_Max"));
        sizePolicy2.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy2);
        btnMenu_Max->setMinimumSize(QSize(30, 30));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Max, 0, 2, 1, 1);


        horizontalLayout_2->addWidget(widgetMenu);


        verticalLayout->addWidget(widgetTitle);

        stackedWidget = new QStackedWidget(tbsui);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page2 = new QWidget();
        page2->setObjectName(QStringLiteral("page2"));
        gridLayout_4 = new QGridLayout(page2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        sli_H = new QSlider(page2);
        sli_H->setObjectName(QStringLiteral("sli_H"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sli_H->sizePolicy().hasHeightForWidth());
        sli_H->setSizePolicy(sizePolicy3);
        sli_H->setMinimum(6);
        sli_H->setMaximum(72);
        sli_H->setValue(10);
        sli_H->setSliderPosition(10);
        sli_H->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(sli_H, 0, 0, 1, 1);

        UpdateWdiget = new QWidget(page2);
        UpdateWdiget->setObjectName(QStringLiteral("UpdateWdiget"));
        UpdateWdiget->setEnabled(true);
        sizePolicy.setHeightForWidth(UpdateWdiget->sizePolicy().hasHeightForWidth());
        UpdateWdiget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(UpdateWdiget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_4->addWidget(UpdateWdiget, 1, 0, 1, 1);

        stackedWidget->addWidget(page2);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(tbsui);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tbsui);
    } // setupUi

    void retranslateUi(QDialog *tbsui)
    {
        tbsui->setWindowTitle(QApplication::translate("tbsui", "Form", nullptr));
        labIco->setText(QString());
        labTitle->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("tbsui", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("tbsui", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        btnMenu_Max->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tbsui: public Ui_tbsui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TBSUI_H
