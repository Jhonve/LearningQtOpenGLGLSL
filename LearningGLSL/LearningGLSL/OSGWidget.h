#pragma once

#include "QtWidgets/qopenglwidget.h"
#include <osgViewer/Viewer>

#include "qevent.h"

class OSGWidget : public QOpenGLWidget
{
public:
	OSGWidget(QWidget *parent = 0);
	virtual ~OSGWidget();

	osgViewer::GraphicsWindow* getGraphicsWindow()
	{
		return m_gw.get();
	}
	const osgViewer::GraphicsWindow* getGraphicsWindow() const
	{
		return m_gw.get();
	}

protected:

	virtual void resizeGL(int width, int height);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);

	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_gw;
};