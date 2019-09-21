#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LearningGLSL.h"

class LearningGLSL : public QMainWindow
{
	Q_OBJECT

public:
	LearningGLSL(QWidget *parent = Q_NULLPTR);

private:
	Ui::LearningGLSLClass ui;
};
