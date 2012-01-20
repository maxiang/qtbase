/*
*********************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the autotests of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
*********************************************************************
*/

/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created: Fri Sep 4 10:17:13 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *findWhat;
    QLineEdit *led;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *sourceText;
    QCheckBox *translations;
    QCheckBox *matchCase;
    QCheckBox *comments;
    QCheckBox *ignoreAccelerators;
    QVBoxLayout *vboxLayout1;
    QPushButton *findNxt;
    QPushButton *cancel;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName(QString::fromUtf8("FindDialog"));
        FindDialog->resize(414, 170);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FindDialog->sizePolicy().hasHeightForWidth());
        FindDialog->setSizePolicy(sizePolicy);
        hboxLayout = new QHBoxLayout(FindDialog);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        findWhat = new QLabel(FindDialog);
        findWhat->setObjectName(QString::fromUtf8("findWhat"));

        hboxLayout1->addWidget(findWhat);

        led = new QLineEdit(FindDialog);
        led->setObjectName(QString::fromUtf8("led"));

        hboxLayout1->addWidget(led);


        vboxLayout->addLayout(hboxLayout1);

        groupBox = new QGroupBox(FindDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sourceText = new QCheckBox(groupBox);
        sourceText->setObjectName(QString::fromUtf8("sourceText"));
        sourceText->setChecked(true);

        gridLayout->addWidget(sourceText, 1, 0, 1, 1);

        translations = new QCheckBox(groupBox);
        translations->setObjectName(QString::fromUtf8("translations"));
        translations->setChecked(true);

        gridLayout->addWidget(translations, 2, 0, 1, 1);

        matchCase = new QCheckBox(groupBox);
        matchCase->setObjectName(QString::fromUtf8("matchCase"));

        gridLayout->addWidget(matchCase, 0, 1, 1, 1);

        comments = new QCheckBox(groupBox);
        comments->setObjectName(QString::fromUtf8("comments"));
        comments->setChecked(true);

        gridLayout->addWidget(comments, 0, 0, 1, 1);

        ignoreAccelerators = new QCheckBox(groupBox);
        ignoreAccelerators->setObjectName(QString::fromUtf8("ignoreAccelerators"));
        ignoreAccelerators->setChecked(true);

        gridLayout->addWidget(ignoreAccelerators, 1, 1, 1, 1);


        vboxLayout->addWidget(groupBox);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        findNxt = new QPushButton(FindDialog);
        findNxt->setObjectName(QString::fromUtf8("findNxt"));
        findNxt->setDefault(true);
        findNxt->setFlat(false);

        vboxLayout1->addWidget(findNxt);

        cancel = new QPushButton(FindDialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        vboxLayout1->addWidget(cancel);

        spacerItem = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);


        hboxLayout->addLayout(vboxLayout1);

#ifndef QT_NO_SHORTCUT
        findWhat->setBuddy(led);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(led, findNxt);
        QWidget::setTabOrder(findNxt, cancel);
        QWidget::setTabOrder(cancel, comments);
        QWidget::setTabOrder(comments, sourceText);
        QWidget::setTabOrder(sourceText, translations);
        QWidget::setTabOrder(translations, matchCase);

        retranslateUi(FindDialog);
        QObject::connect(cancel, SIGNAL(clicked()), FindDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QApplication::translate("FindDialog", "Find", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        FindDialog->setWhatsThis(QApplication::translate("FindDialog", "This window allows you to search for some text in the translation source file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        findWhat->setText(QApplication::translate("FindDialog", "&Find what:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        led->setWhatsThis(QApplication::translate("FindDialog", "Type in the text to search for.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("FindDialog", "Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sourceText->setWhatsThis(QApplication::translate("FindDialog", "Source texts are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sourceText->setText(QApplication::translate("FindDialog", "&Source texts", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        translations->setWhatsThis(QApplication::translate("FindDialog", "Translations are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        translations->setText(QApplication::translate("FindDialog", "&Translations", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        matchCase->setWhatsThis(QApplication::translate("FindDialog", "Texts such as 'TeX' and 'tex' are considered as different when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        matchCase->setText(QApplication::translate("FindDialog", "&Match case", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        comments->setWhatsThis(QApplication::translate("FindDialog", "Comments and contexts are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        comments->setText(QApplication::translate("FindDialog", "&Comments", 0, QApplication::UnicodeUTF8));
        ignoreAccelerators->setText(QApplication::translate("FindDialog", "Ignore &accelerators", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        findNxt->setWhatsThis(QApplication::translate("FindDialog", "Click here to find the next occurrence of the text you typed in.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        findNxt->setText(QApplication::translate("FindDialog", "Find Next", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        cancel->setWhatsThis(QApplication::translate("FindDialog", "Click here to close this window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        cancel->setText(QApplication::translate("FindDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FINDDIALOG_H
