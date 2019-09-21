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

QT_BEGIN_NAMESPACE

class Ui_LearningGLSLClass
{
public:
    QWidget *centralWidget;
    MainOpenGLWidget *OpenGLWidgetMain;

    void setupUi(QMainWindow *LearningGLSLClass)
    {
        if (LearningGLSLClass->objectName().isEmpty())
            LearningGLSLClass->setObjectName(QString::fromUtf8("LearningGLSLClass"));
        LearningGLSLClass->resize(532, 530);
        centralWidget = new QWidget(LearningGLSLClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OpenGLWidgetMain = new MainOpenGLWidget(centralWidget);
        OpenGLWidgetMain->setObjectName(QString::fromUtf8("OpenGLWidgetMain"));
        OpenGLWidgetMain->setGeometry(QRect(10, 10, 512, 512));
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
