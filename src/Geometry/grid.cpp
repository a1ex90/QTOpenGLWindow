/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %## #    CC        V    V  MM M  M MM RR    RR
 *   ,%      %    CC        VV  VV  MM  MM  MM RRRRRR
 *   (%      %,   CC    CC   VVVV   MM      MM RR   RR
 *     #%    %*    CCCCCC     VV    MM      MM RR    RR
 *    .%    %/
 *       (%.      Computer Vision & Mixed Reality Group
 *
 *****************************************************/
/** @copyright:   Hochschule RheinMain,
 *                University of Applied Sciences
 *     @author:   Alex Sommer
 *    @version:   1.0
 *       @date:   11.03.20
 *****************************************************/

#include "grid.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

/******************************************************
 * Constructors
 *****************************************************/

Grid::Grid()
    : Geometry(6, GeometryType::GRID)
    , m_positionsBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_texCoordBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_indicesBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
{}

/******************************************************
 * Public Functions
 *****************************************************/

void Grid::render(QMatrix4x4 modelMatrix, QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;
    const QMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

    m_shader->bind();
    m_shader->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformValue("mvp", modelViewProjectionMatrix);

    m_vao->bind();
    functions->glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_SHORT, Q_NULLPTR);
    m_vao->release();
}

void Grid::invalidate() {
    m_positionsBuffer->destroy();
    m_texCoordBuffer->destroy();
    m_indicesBuffer->destroy();
    m_shader.reset();
    m_vao->destroy();
}

void Grid::initGrid(QVector3D offset) {
    const float c0 = -0.5f;
    const float c1 = 0.5f;

    const float vertexPositions[] =
            {
                    offset.x() + c0, offset.y(), offset.z() + c0,
                    offset.x() + c1, offset.y(), offset.z() + c0,
                    offset.x() + c1, offset.y(), offset.z() + c1,
                    offset.x() + c0, offset.y(), offset.z() + c1
            };

    const float texW = 30.0f;
    const float texH = 30.0f;

    const float texCoords[] =
            {
                    0.0f, 0.0f,
                    texW, 0.0f,
                    texW, texH,
                    0.0f, texH
            };

    const ushort indices[] = { 0, 1, 2, 0, 2, 3 };

    m_vao->bind();

    m_positionsBuffer->bind();
    m_positionsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionsBuffer->allocate(vertexPositions, 18 * sizeof(float));

    m_texCoordBuffer->bind();
    m_texCoordBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_texCoordBuffer->allocate(texCoords, 12 * sizeof(float));

    m_indicesBuffer->bind();
    m_indicesBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indicesBuffer->allocate(indices, 6 * sizeof(ushort));

    m_shader->bind();

    m_positionsBuffer->bind();
    m_shader->enableAttributeArray("vertexPosition");
    m_shader->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_texCoordBuffer->bind();
    m_shader->enableAttributeArray("aTexcoord");
    m_shader->setAttributeBuffer("aTexcoord", GL_FLOAT, 0, 2);

    m_vao->release();
}

/******************************************************
 * Private Functions
 *****************************************************/

void Grid::initializeBuffers() {
    if (!m_positionsBuffer->create())
        qFatal("Unable to create position buffer");
    if (!m_texCoordBuffer->create())
        qFatal("Unable to create vertex buffer");
    if (!m_indicesBuffer->create())
        qFatal("Unable to create index buffer");
}
