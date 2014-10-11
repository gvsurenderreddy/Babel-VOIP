/********************************************************************************
** Form generated from reading UI file 'qtnetwork_tests.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTNETWORK_TESTS_H
#define UI_QTNETWORK_TESTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtnetwork_testsClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtnetwork_testsClass)
    {
        if (qtnetwork_testsClass->objectName().isEmpty())
            qtnetwork_testsClass->setObjectName(QStringLiteral("qtnetwork_testsClass"));
        qtnetwork_testsClass->resize(600, 400);
        centralWidget = new QWidget(qtnetwork_testsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 110, 261, 101));
        qtnetwork_testsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtnetwork_testsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        qtnetwork_testsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtnetwork_testsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qtnetwork_testsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtnetwork_testsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtnetwork_testsClass->setStatusBar(statusBar);

        retranslateUi(qtnetwork_testsClass);

        QMetaObject::connectSlotsByName(qtnetwork_testsClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtnetwork_testsClass)
    {
        qtnetwork_testsClass->setWindowTitle(QApplication::translate("qtnetwork_testsClass", "qtnetwork_tests", 0));
        pushButton->setText(QApplication::translate("qtnetwork_testsClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class qtnetwork_testsClass: public Ui_qtnetwork_testsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTNETWORK_TESTS_H
