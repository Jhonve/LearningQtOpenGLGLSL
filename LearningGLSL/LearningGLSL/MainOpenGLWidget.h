#pragma once
#include "QtWidgets/qopenglwidget.h"
#include "qopenglfunctions_4_5_core.h"
#include "qopenglfunctions.h"
#include "qopenglbuffer.h"
#include "qopenglvertexarrayobject.h"

#include "qdebug.h"
#include "qmatrix4x4.h"
#include "qevent.h"

#include <Shader.h>

class MainOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	MainOpenGLWidget(QWidget *parent = 0);
	~MainOpenGLWidget();

	static bool isTransparent() { return m_transparent; };
	static void setTransparent(bool t) { m_transparent = t; };

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void cleanup();

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void keyPressEvent(QKeyEvent *e);

private:
	Shader *m_shader;
	QOpenGLFunctions_4_5_Core *m_core;

	int m_xRot;
	int m_yRot;
	int m_zRot;
	QPoint m_lastPos;	// mouse's last position
	int m_projMatrixLoc;	// vertices' projection matrix location
	int m_mvMatrixLoc;		// vertices' move matrix location
	QMatrix4x4 m_proj;	// project matrix
	QMatrix4x4 m_camera;	// camera transform matrix
	QMatrix4x4 m_world;		// world transform matrix
	static bool m_transparent;

	bool m_is_reload;
};