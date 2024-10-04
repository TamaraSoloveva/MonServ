/********************************************************************************
** Form generated from reading UI file 'portWrRdmquaxM.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PORTWRRDMQUAXM_H
#define PORTWRRDMQUAXM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "ui_MonServ.h"

QT_BEGIN_NAMESPACE

class Ui_Form_Port : public Ui_MainWindow
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_6;
    QLineEdit *lineEdit_7;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_34;
    QLineEdit *lineEdit_5;
    QComboBox *comboBox_15;
    QLabel *label_22;
    QLineEdit *lineEdit_12;
    QPushButton *pushButton_18;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *label_29;
    QLineEdit *lineEdit_10;
    QComboBox *comboBox_12;
    QLabel *label_23;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_19;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(591, 244);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        Form->setMinimumSize(QSize(0, 244));
        gridLayout_3 = new QGridLayout(Form);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox_6 = new QCheckBox(Form);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setMaximumSize(QSize(60, 17));
        checkBox_6->setLayoutDirection(Qt::LeftToRight);
        checkBox_6->setAutoFillBackground(false);
        checkBox_6->setTristate(false);

        horizontalLayout->addWidget(checkBox_6);

        lineEdit_7 = new QLineEdit(Form);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy);
        lineEdit_7->setMinimumSize(QSize(132, 22));
        lineEdit_7->setMaximumSize(QSize(132, 22));
        lineEdit_7->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEdit_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        frame = new QFrame(Form);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_34 = new QLabel(frame);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        sizePolicy.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_34, 0, 0, 1, 1);

        lineEdit_5 = new QLineEdit(frame);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(132, 22));
        lineEdit_5->setMaximumSize(QSize(132, 22));

        gridLayout->addWidget(lineEdit_5, 1, 0, 1, 1);

        comboBox_15 = new QComboBox(frame);
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->setObjectName(QString::fromUtf8("comboBox_15"));
        comboBox_15->setMinimumSize(QSize(120, 26));
        comboBox_15->setMaximumSize(QSize(120, 26));

        gridLayout->addWidget(comboBox_15, 1, 1, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_22, 2, 0, 1, 1);

        lineEdit_12 = new QLineEdit(frame);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        sizePolicy.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy);
        lineEdit_12->setMinimumSize(QSize(132, 22));
        lineEdit_12->setMaximumSize(QSize(132, 22));
        lineEdit_12->setReadOnly(true);

        gridLayout->addWidget(lineEdit_12, 3, 0, 1, 1);

        pushButton_18 = new QPushButton(frame);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_18->sizePolicy().hasHeightForWidth());
        pushButton_18->setSizePolicy(sizePolicy);
        pushButton_18->setMinimumSize(QSize(120, 26));
        pushButton_18->setMaximumSize(QSize(120, 26));

        gridLayout->addWidget(pushButton_18, 3, 1, 1, 1);


        gridLayout_3->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(Form);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_29 = new QLabel(frame_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_29, 0, 0, 1, 1);

        lineEdit_10 = new QLineEdit(frame_2);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        sizePolicy.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy);
        lineEdit_10->setMinimumSize(QSize(132, 22));
        lineEdit_10->setMaximumSize(QSize(132, 22));

        gridLayout_2->addWidget(lineEdit_10, 1, 0, 1, 1);

        comboBox_12 = new QComboBox(frame_2);
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->setObjectName(QString::fromUtf8("comboBox_12"));
        sizePolicy.setHeightForWidth(comboBox_12->sizePolicy().hasHeightForWidth());
        comboBox_12->setSizePolicy(sizePolicy);
        comboBox_12->setMinimumSize(QSize(120, 26));
        comboBox_12->setMaximumSize(QSize(120, 26));

        gridLayout_2->addWidget(comboBox_12, 1, 1, 1, 1);

        label_23 = new QLabel(frame_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy1);
        label_23->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_23, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(frame_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(132, 22));
        lineEdit_4->setMaximumSize(QSize(132, 22));

        gridLayout_2->addWidget(lineEdit_4, 3, 0, 1, 1);

        pushButton_19 = new QPushButton(frame_2);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setEnabled(true);
        pushButton_19->setMinimumSize(QSize(120, 26));
        pushButton_19->setMaximumSize(QSize(120, 26));

        gridLayout_2->addWidget(pushButton_19, 3, 1, 1, 1);


        gridLayout_3->addWidget(frame_2, 1, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(Form);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(50, 22));
        label_11->setMaximumSize(QSize(50, 22));

        horizontalLayout_7->addWidget(label_11);

        label_4 = new QLabel(Form);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_7->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        gridLayout_3->addLayout(horizontalLayout_7, 2, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        progressBar = new QProgressBar(Form);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(500, 21));
        progressBar->setValue(0);

        horizontalLayout_8->addWidget(progressBar);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_3->addLayout(verticalLayout, 3, 0, 1, 2);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270 \320\262 I/O", nullptr));
        checkBox_6->setText(QCoreApplication::translate("Form", "\320\237\320\276\320\262\321\202\320\276\321\200", nullptr));
        label_34->setText(QCoreApplication::translate("Form", "\320\220\320\264\321\200\320\265\321\201 ", nullptr));
        comboBox_15->setItemText(0, QCoreApplication::translate("Form", "1 \320\261\320\260\320\271\321\202", nullptr));
        comboBox_15->setItemText(1, QCoreApplication::translate("Form", "2 \320\261\320\260\320\271\321\202\320\260", nullptr));
        comboBox_15->setItemText(2, QCoreApplication::translate("Form", "4 \320\261\320\260\320\271\321\202\320\260", nullptr));
        comboBox_15->setItemText(3, QCoreApplication::translate("Form", "8 \320\261\320\260\320\271\321\202", nullptr));

        label_22->setText(QCoreApplication::translate("Form", "\320\224\320\260\320\275\320\275\321\213\320\265", nullptr));
        pushButton_18->setText(QCoreApplication::translate("Form", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        label_29->setText(QCoreApplication::translate("Form", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        comboBox_12->setItemText(0, QCoreApplication::translate("Form", "1 \320\261\320\260\320\271\321\202", nullptr));
        comboBox_12->setItemText(1, QCoreApplication::translate("Form", "2 \320\261\320\260\320\271\321\202\320\260", nullptr));
        comboBox_12->setItemText(2, QCoreApplication::translate("Form", "4 \320\261\320\260\320\271\321\202\320\260", nullptr));
        comboBox_12->setItemText(3, QCoreApplication::translate("Form", "8 \320\261\320\260\320\271\321\202", nullptr));

        label_23->setText(QCoreApplication::translate("Form", "\320\224\320\260\320\275\320\275\321\213\320\265", nullptr));
        pushButton_19->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_11->setText(QCoreApplication::translate("Form", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui_Port {
    class Form: public Ui_Form_Port {};
} // namespace Ui_Port

QT_END_NAMESPACE

#endif // PORTWRRDMQUAXM_H
