#include "OSGWidget.h"

OSGWidget::OSGWidget(QWidget * parent)
	:QOpenGLWidget(parent)
{
	m_gw = new osgViewer::GraphicsWindowEmbedded(0, 0, width(), height());
	setFocusPolicy(Qt::ClickFocus);
}

OSGWidget::~OSGWidget()
{
	
}


void OSGWidget::resizeGL(int width, int height)
{
	m_gw->getEventQueue()->windowResize(0, 0, width, height);
	m_gw->resized(0, 0, width, height);
}

void OSGWidget::mousePressEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case(Qt::LeftButton): 
		button = 1; 
		break;
	case(Qt::MidButton): 
		button = 2; 
		break;
	case(Qt::RightButton):
		button = 3; 
		break;
	case(Qt::NoButton): 
		button = 0; 
		break;
	default: 
		button = 0; 
		break;
	}
	m_gw->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case(Qt::LeftButton): 
		button = 1; 
		break;
	case(Qt::MidButton): 
		button = 2;
		break;
	case(Qt::RightButton):
		button = 3; 
		break;
	case(Qt::NoButton): 
		button = 0; 
		break;
	default: 
		button = 0; 
		break;
	}
	m_gw->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
}

void OSGWidget::mouseMoveEvent(QMouseEvent* event)
{
	m_gw->getEventQueue()->mouseMotion(event->x(), event->y());
}


void OSGWidget::wheelEvent(QWheelEvent* event)
{
	m_gw->getEventQueue()->mouseScroll(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN);
}

void OSGWidget::keyPressEvent(QKeyEvent* event)
{
	m_gw->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol) *(event->text().toUtf8().data()));
}

void OSGWidget::keyReleaseEvent(QKeyEvent* event)
{
	m_gw->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol) *(event->text().toUtf8().data()));
}