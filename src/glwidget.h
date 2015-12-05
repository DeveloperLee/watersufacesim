#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>
#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif


#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include <memory>
#include <openglshape.h>
#include <QTime>



class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
//    void wheelEvent(QWheelEvent *e);

protected slots:

    /** Repaints the canvas. Called 60 times per second by m_timer. */
    void tick();

private:
    void rebuildMatrices();

    /** ID for the shader program. */
    GLuint m_program;

    glm::mat4 m_model, m_view, m_projection,m_fragView;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_angleZ, m_zoom;

    QPoint m_prevMousePos;

    /** Time related **/
    QTimer m_timer;
    QTime  m_time;

    float m_fps;

    /** These vertices are just used for rendering fullscreen quad **/
    GLfloat m_quadVertices[8] =
    {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
     };

    OpenGLShape* m_shape;

    /** Shader parameters **/
    glm::vec2 m_screenDimension;
    bool m_renderFog, m_renderCloud;
    float m_cloudThickness;
};

#endif // GLWIDGET_H
