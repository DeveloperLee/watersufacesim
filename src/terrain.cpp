#include "terrain.h"

#include <

Terrain::Terrain() : m_numRows(500), m_numCols(m_numRows),m_time()
{
    m_time.start();
}


/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float Terrain::randValue(int row, int col)
{
    return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getPosition(int row, int col)
{
    glm::vec3 position;
    position.x = 100 * row/m_numRows - 5;
    position.y = 0;
    position.z = 100 * col/m_numCols - 5;

    // TODO: Adjust position.y using value noise.

     float divider = 20.f;

     for(int i=0;i<3;i++){

         float f = pow(2,i);

         float scaledRow = row / (divider / f);
         float scaledColumn = col / (divider / f);

         int nearestRowStart = std::floor(scaledRow);
         int nearestRowEnd = nearestRowStart+1;
         int nearestColumnStart = std::floor(scaledColumn);
         int nearestColumnEnd = nearestColumnStart+1;  //Nearest vertex points

         float topLeft = randValue(nearestRowStart,nearestColumnStart);
         float topRight = randValue(nearestRowStart,nearestColumnEnd);
         float bottomLeft = randValue(nearestRowEnd,nearestColumnStart);
         float bottomRight = randValue(nearestRowEnd,nearestColumnEnd);

         float hRatio = glm::fract(scaledColumn);
         float vRatio = glm::fract(scaledRow);

         float hCubicRatio = hRatio * hRatio * (3 - 2 * hRatio);
         float vCubicRatio = vRatio * vRatio * (3 - 2 * vRatio);

         float hTopInterVal = glm::mix(topLeft,topRight,hCubicRatio);
         float hBottomInterVal = glm::mix(bottomLeft,bottomRight,hCubicRatio);
         float interVal = glm::mix(hTopInterVal,hBottomInterVal,vCubicRatio);
         position.y  += interVal / f;


     }

    return position;
}


/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getNormal(int row, int col)
{
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.

    glm::vec3 center = getPosition(row,col);
    glm::vec3 vertices[9];
    glm::vec3 sum = glm::vec3(0.f,0.f,0.f);

    for(int i=-1;i<=1;i++){
        vertices[i+1] = getPosition(row-1,col+i);
     }

    for(int i=-1;i<=1;i++){
        vertices[5+i] = getPosition(row+1,col-i);
    }

    vertices[3] = getPosition(row,col+1);
    vertices[7] = getPosition(row,col-1);
    vertices[8] = getPosition(row-1,col-1);

    for(int i=0;i<8;i++){
         glm::vec3 e1 = glm::vec3(vertices[i].x-center.x,vertices[i].y-center.y,vertices[i].z-center.z);
         glm::vec3 e2 = glm::vec3(vertices[i+1].x-center.x,vertices[i+1].y-center.y,vertices[i+1].z-center.z);
         glm::vec3 normal = glm::normalize(glm::cross(e1,e2));
         sum+= normal;
    }

    return glm::vec3(sum.x/8.f, sum.y/8.f, sum.z/8.f);
}


/**
 * Initializes the terrain by storing positions and normals in a vertex buffer.
 */
void Terrain::init()
{
    // TODO: Change from GL_LINE to GL_FILL in order to render full triangles instead of wireframe.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Initialize OpenGLShape.
    m_shape.create();
}


/**
 * Draws the terrain.
 */
void Terrain::draw()
{
    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++)
    {
        for (int col = m_numCols - 1; col >= 0; col--)
        {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }
    m_shape.setVertexData(&data[0][0], 2 * sizeof(glm::vec3) * numVertices, GL_TRIANGLE_STRIP, numVertices);
    m_shape.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
    m_shape.setAttribute(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), sizeof(glm::vec3));
    m_shape.draw();
}
