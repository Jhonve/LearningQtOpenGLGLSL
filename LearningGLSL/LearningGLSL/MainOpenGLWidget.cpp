#include "MainOpenGLWidget.h"
#include <QmouseEvent>
#include <qcoreapplication.h>

#include <string>
#include <iostream>

#include <QFileDialog>

GLuint PDVBO, PDVAO, PLVBO, PLVAO;

bool MainOpenGLWidget::m_transparent = false;

MainOpenGLWidget::MainOpenGLWidget(QWidget *parent)
	:QOpenGLWidget(parent),
	m_xRot(0),
	m_yRot(0),
	m_zRot(0)
{
	if (m_transparent)
	{
		QSurfaceFormat fmt = format();
		fmt.setAlphaBufferSize(8);
		setFormat(fmt);
	}
}

MainOpenGLWidget::~MainOpenGLWidget()
{
	cleanup();
}

QSize MainOpenGLWidget::minimumSizeHint() const
{
	return QSize(256, 256);
}

QSize MainOpenGLWidget::sizeHint() const
{
	return QSize(512, 512);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
	{
		angle += 360 * 16;
	}
	while (angle > 360 * 16)
	{
		angle -= 360 * 16;
	}
}

void MainOpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot)
	{
		m_xRot = angle;
		emit xRotationChanged(angle);
		update();
	}
}

void MainOpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot)
	{
		m_yRot = angle;
		emit yRotationChanged(angle);
		update();
	}
}

void MainOpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot)
	{
		m_zRot = angle;
		emit zRotationChanged(angle);
		update();
	}
}

void MainOpenGLWidget::cleanup()
{
	if (&m_shader->shader_program == nullptr)
	{
		return;
	}
	makeCurrent();
	delete &m_shader->shader_program;
	doneCurrent();
}

void MainOpenGLWidget::initializeGL()
{
	// shader part
	m_core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
	m_shader = new Shader("ShaderFiles/vertex_shader_source.vert", "ShaderFiles/fragment_shader_source.frag");

	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
		0.5f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // Bottom Right
	};

	m_core->glGenVertexArrays(1, &PDVAO);
	m_core->glGenBuffers(1, &PDVBO);
	m_core->glBindVertexArray(PDVAO);
	m_core->glBindBuffer(GL_ARRAY_BUFFER, PDVBO);
	m_core->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 * 6), vertices, GL_STATIC_DRAW);
	m_core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	m_core->glEnableVertexAttribArray(0);
	m_core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	m_core->glEnableVertexAttribArray(1);

	m_core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// set camera
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -2);

	m_is_reload = false;
}

void MainOpenGLWidget::resizeGL(int width, int height)
{
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
}

void MainOpenGLWidget::paintGL()
{
	m_core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_core->glEnable(GL_DEPTH_TEST);
	m_core->glEnable(GL_CULL_FACE);

	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
		0.5f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // Bottom Right
	};

	if (m_is_reload)
	{
		m_core->glGenVertexArrays(1, &PDVAO);
		m_core->glGenBuffers(1, &PDVBO);
		m_core->glBindVertexArray(PDVAO);
		m_core->glBindBuffer(GL_ARRAY_BUFFER, PDVBO);
		m_core->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 * 6), vertices, GL_STATIC_DRAW);
		m_core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
		m_core->glEnableVertexAttribArray(0);
		m_core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		m_core->glEnableVertexAttribArray(1);

		m_is_reload = false;
	}

	m_world.setToIdentity();
	m_world.rotate(m_xRot / 16.0f, 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	m_shader->use();
	m_core->glBindVertexArray(PDVAO);
	m_projMatrixLoc = m_shader->shader_program.uniformLocation("projMatrix");
	m_mvMatrixLoc = m_shader->shader_program.uniformLocation("mvMatrix");

	m_shader->shader_program.setUniformValue(m_projMatrixLoc, m_proj);
	m_shader->shader_program.setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	m_core->glPointSize(5);
	// m_core->glDrawArrays(GL_TRIANGLES, 0, 3);
	m_core->glDrawArrays(GL_POINTS, 0, 3);

	m_shader->shader_program.release();
}

void MainOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		close();
	default:
		break;
	}
}

void MainOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void MainOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton)
	{
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton)
	{
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}
	else if (event->buttons() & Qt::MidButton)
	{
		m_camera.translate((GLfloat)dx / 600, -1 * (GLfloat)dy / 600, 0);
		update();
	}
	m_lastPos = event->pos();
}

void MainOpenGLWidget::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
	{
		m_camera.translate(0, 0, 0.05f);
		update();
	}
	else
	{
		m_camera.translate(0, 0, -0.05f);
		update();
	}
}