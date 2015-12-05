#include "openglshape.h"

void OpenGLShape::create()
{
    // Generates a VBO and VAO for this shape.
    glGenBuffers(1, &m_vboID);
    glGenVertexArrays(1, &m_vaoID);
    glGenTextures(1,&m_textureID);
}

void OpenGLShape::destroy()
{
    // Deletes the VBO and VAO.
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
    glDeleteTextures(1,&m_textureID);
}

void OpenGLShape::setVertexData(float *data, GLsizeiptr size, GLenum drawMode, int numVertices)
{
    m_drawMode = drawMode;
    m_numVertices = numVertices;

    // Stores vertex data in VBO.
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLShape::setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, size_t pointer)
{
    // Bind VAO and VBO.
    glBindVertexArray(m_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Defines the specified vertex attribute with respect to the VBO's data store.
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, (void*) pointer);

    // Unbind VAO and VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLShape::bindTexture(QImage img){

    glBindTexture(GL_TEXTURE_2D,m_textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,img.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glBindTexture(0,m_textureID);
}

void OpenGLShape::draw()
{
    glBindVertexArray(m_vaoID);
    glBindTexture(GL_TEXTURE_2D,m_textureID);
    glDrawArrays(m_drawMode, 0, m_numVertices);
    glBindTexture(0,m_textureID);
    glBindVertexArray(0);
}
