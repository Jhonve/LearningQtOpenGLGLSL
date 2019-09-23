/********************************************************************************
** Form generated from reading UI file 'LearningGLSL.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNINGGLSL_H
#define UI_LEARNINGGLSL_H

#include <MainOpenGLWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <TestOsgWidget.h>

QT_BEGIN_NAMESPACE

class Ui_LearningGLSLClass
{
public:
    QWidget *centralWidget;
    MainOpenGLWidget *MOpenGLWidget;
    TestOsgWidget *OpenSGWidget;

    void setupUi(QMainWindow *LearningGLSLClass)
    {
        if (LearningGLSLClass->objectName().isEmpty())
            LearningGLSLClass->setObjectName(QString::fromUtf8("LearningGLSLClass"));
        LearningGLSLClass->resize(1050, 530);
        centralWidget = new QWidget(LearningGLSLClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MOpenGLWidget = new MainOpenGLWidget(centralWidget);
        MOpenGLWidget->setObjectName(QString::fromUtf8("MOpenGLWidget"));
        MOpenGLWidget->setGeometry(QRect(10, 10, 512, 512));
        OpenSGWidget = new TestOsgWidget(centralWidget);
        OpenSGWidget->setObjectName(QString::fromUtf8("OpenSGWidget"));
        OpenSGWidget->setGeometry(QRect(530, 10, 512, 512));
        LearningGLSLClass->setCentralWidget(centralWidget);

        retranslateUi(LearningGLSLClass);

        QMetaObject::connectSlotsByName(LearningGLSLClass);
    } // setupUi

    void retranslateUi(QMainWindow *LearningGLSLClass)
    {
        LearningGLSLClass->setWindowTitle(QApplication::translate("LearningGLSLClass", "LearningGLSL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearningGLSLClass: public Ui_LearningGLSLClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNINGGLSL_H
