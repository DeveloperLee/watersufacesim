#include "glwidget.h"

#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include "Settings.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent), m_program(0),
      m_angleX(0), m_angleY(0.5f),m_angleZ(0), m_zoom(1.f),
      m_timer(this),m_fps(40.0f)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));
    m_timer.start(1000.0f / m_fps);
    m_screenDimension = glm::vec2(width(),height());
    m_shape = new OpenGLShape();
}

GLWidget::~GLWidget()
{
    m_shape->destroy();
    delete m_shape;
}

void GLWidget::initializeGL()
{
    ResourceLoader::initializeGlew();
    resizeGL(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    m_program = ResourceLoader::createShaderProgram(":/shaders/shader.vert", ":/shaders/shader.frag");
    m_shape->create();
    m_shape->setVertexData(m_quadVertices,sizeof(m_quadVertices),GL_TRIANGLE_STRIP,4);
    m_shape->setAttribute(0,2,GL_FLOAT,GL_FALSE,0,0);

    QImage img(":/resources/noise.png","PNG");
    m_shape->bindTexture(img);

    m_time.start();

    rebuildMatrices();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind shader program.
    glUseProgram(m_program);

    // Set uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

    // Set resolution to fragment shader
    glUniform2i(glGetUniformLocation(m_program, "resolution"), m_screenDimension.x, m_screenDimension.y);
    glUniform1f(glGetUniformLocation(m_program, "currentTime"), m_time.elapsed() / 1000.0);
    glUniform1f(glGetUniformLocation(m_program, "cloudThickness"), settings.cloudThickness);
    glUniform1f(glGetUniformLocation(m_program, "shadowHardness"), settings.shadowHardness);
    glUniform1f(glGetUniformLocation(m_program, "bigwave"), settings.bigWave);
    glUniform1f(glGetUniformLocation(m_program, "smallwave"), settings.smallWave);
    glUniform2f(glGetUniformLocation(m_program, "wavespeed"), settings.waveSpeedX, settings.waveSpeedY);
    glUniform1f(glGetUniformLocation(m_program, "camX"), settings.camX);
    glUniform1f(glGetUniformLocation(m_program, "camY"), settings.camY);
    glUniform1f(glGetUniformLocation(m_program, "wideAngle"), settings.wideAngle);
    glUniform1i(glGetUniformLocation(m_program, "renderFog"), settings.enableFog);
    glUniform1i(glGetUniformLocation(m_program, "renderShadow"), settings.enableShadow);
    glUniform1i(glGetUniformLocation(m_program, "renderCloud"), settings.enableCloud);
    glUniform1i(glGetUniformLocation(m_program, "renderLens"), settings.enableLens);
    glUniform1i(glGetUniformLocation(m_program, "renderSnow"), settings.enableSnow);
    glUniform1i(glGetUniformLocation(m_program, "renderRain"), settings.enableRain);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "fragMVP"), 1, GL_FALSE, glm::value_ptr(m_projection * m_fragView * m_model));

    // Render fullscreen quad
    m_shape->draw();

    // Unbind shader program.
    glUseProgram(0);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    //Update the resolution vector
    m_screenDimension.x = w;
    m_screenDimension.y = h;
    rebuildMatrices();
}

void GLWidget::reloadTexture(QString filename)
{
    QImage texture(filename);
    m_shape->bindTexture(texture);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_angleX += 10 * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 10 * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::rebuildMatrices()
{
    m_model = glm::mat4(1.f);
    m_view = glm::translate(glm::vec3(0, 0, -m_zoom));
    m_projection = glm::perspective(0.8f, (float)width()/height(), 0.1f, 100.f);

    m_fragView = glm::translate(glm::vec3(0, 0, -m_zoom)) *
                 glm::rotate(m_angleX,glm::vec3(0,1,0)) *
                 glm::rotate(m_angleY, glm::vec3(0,1,0));
    update();

}

/** Repaints the canvas. Called 60 times per second. */
void GLWidget::tick()
{
    update();
}
