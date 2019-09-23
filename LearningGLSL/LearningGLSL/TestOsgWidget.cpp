#include "TestOsgWidget.h"

#include <osgDB/ReadFile>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <iostream>
#include <string>

TestOsgWidget::TestOsgWidget(QWidget* parent)
	:OSGWidget(parent)
{
	getCamera()->setViewport(new osg::Viewport(0, 0, width(), height()));
	getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width()) / static_cast<double>(height()), 1.0f, 10000.0f);
	getCamera()->setGraphicsContext(getGraphicsWindow());
	setThreadingModel(osgViewer::Viewer::SingleThreaded);

	m_start_time = 0.0;
	m_end_time = 0.0;
	m_sleep_time = 0.0;

	osg::ref_ptr<osg::Node> loaded_model = osgDB::readNodeFile("Data/OSGData/fountain.osgt");

	setCameraManipulator(new osgGA::TrackballManipulator);
	addEventHandler(new osgViewer::WindowSizeHandler);
	addEventHandler(new osgViewer::StatsHandler);
	setSceneData(loaded_model.get());
}

TestOsgWidget::~TestOsgWidget()
{

}

void TestOsgWidget::paintGL()
{
	m_start_time = m_timer.tick();
	frame();

	m_end_time = m_timer.tick();

	m_sleep_time = 1.0 / 60.0 - m_timer.delta_s(m_start_time, m_end_time);

	if (m_sleep_time < 0)
	{
		m_sleep_time = 0.0;
	}

	OpenThreads::Thread::microSleep(m_sleep_time * 1000000);

	double time_show = m_timer.tick();
	// std::cout << "frames: " << m_timer.delta_s(m_start_time, time_show) << std::endl;

	update();
}