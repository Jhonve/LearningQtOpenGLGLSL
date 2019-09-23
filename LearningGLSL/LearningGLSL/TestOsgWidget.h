#pragma once

#include "OSGWidget.h"

class TestOsgWidget : public osgViewer::Viewer, public OSGWidget
{
public:
	TestOsgWidget(QWidget* parent = 0);
	~TestOsgWidget();

	void paintGL();

protected:
	osg::Timer m_timer;
	double m_start_time;
	double m_end_time;
	
	double m_sleep_time;
};