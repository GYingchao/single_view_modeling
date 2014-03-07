/********************************************************************************
** Form generated from reading UI file 'singleviewmodeling.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEVIEWMODELING_H
#define UI_SINGLEVIEWMODELING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <imagedisplayer.h>

QT_BEGIN_NAMESPACE

class Ui_singleViewModelingClass
{
public:
    QAction *actionLoadImage;
    QWidget *centralWidget;
    ImageDisplayer *imageWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *singleViewModelingClass)
    {
        if (singleViewModelingClass->objectName().isEmpty())
            singleViewModelingClass->setObjectName(QString::fromUtf8("singleViewModelingClass"));
        singleViewModelingClass->resize(1133, 865);
        actionLoadImage = new QAction(singleViewModelingClass);
        actionLoadImage->setObjectName(QString::fromUtf8("actionLoadImage"));
        centralWidget = new QWidget(singleViewModelingClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imageWidget = new ImageDisplayer(centralWidget);
        imageWidget->setObjectName(QString::fromUtf8("imageWidget"));
        imageWidget->setGeometry(QRect(-1, -1, 1131, 801));
        singleViewModelingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(singleViewModelingClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1133, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        singleViewModelingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(singleViewModelingClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        singleViewModelingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(singleViewModelingClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        singleViewModelingClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoadImage);

        retranslateUi(singleViewModelingClass);

        QMetaObject::connectSlotsByName(singleViewModelingClass);
    } // setupUi

    void retranslateUi(QMainWindow *singleViewModelingClass)
    {
        singleViewModelingClass->setWindowTitle(QApplication::translate("singleViewModelingClass", "singleViewModeling", 0, QApplication::UnicodeUTF8));
        actionLoadImage->setText(QApplication::translate("singleViewModelingClass", "loadImage", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("singleViewModelingClass", "file", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class singleViewModelingClass: public Ui_singleViewModelingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEVIEWMODELING_H
