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
 *       @date:   11.03.2020
 *****************************************************/

#include "points.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

/******************************************************
 * Constructors
 *****************************************************/

PointCloud::PointCloud()
        : Geometry(0, GeometryType::POINTCLOUD)
        , m_positionsBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
        , m_color(QVector3D(0,0,0))
        , m_pointSize(1.0f)
        , m_pointsChanged(false)
        , m_dataHead(nullptr)
{}

/******************************************************
 * Public Functions
 *****************************************************/

void PointCloud::render(const QVector3D &eye, const QMatrix4x4 &modelMatrix, const QMatrix4x4 &viewMatrix, const QMatrix4x4 &projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;
    const QMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

    m_shader->bind();
    m_shader->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformValue("mvp", modelViewProjectionMatrix);
    m_shader->setUniformValue("color", QVector4D(m_color, 1.0));
    m_shader->setUniformValue("ps", m_pointSize);

    m_vao->bind();
    functions->glEnable(GL_PROGRAM_POINT_SIZE);
    functions->glEnable(GL_POINT_SMOOTH);
    functions->glDrawArrays(GL_POINTS, 0, m_drawCount);
    m_vao->release();
}

void PointCloud::invalidate() {
    m_positionsBuffer->destroy();
    m_shader.reset();
    m_vao->destroy();
}

void PointCloud::changePoints(float *dataHead, int length) {
    m_dataHead = dataHead;
    m_drawCount = length;
    m_pointsChanged = true;
}

void PointCloud::setColor(QVector3D color) {
    m_color = color;
}

void PointCloud::setPointSize(const float &ps) {
    m_pointSize = ps;
}

void PointCloud::flush() {
    m_vao->bind();

    const QVector<QVector3D> positions;
    m_drawCount = positions.size();

    m_positionsBuffer->bind();
    m_positionsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionsBuffer->allocate(positions.constData(), positions.size() * sizeof(QVector3D));

    m_shader->bind();

    m_positionsBuffer->bind();
    m_shader->enableAttributeArray("vertexPosition");
    m_shader->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vao->release();
}

QVector3D PointCloud::centroid() {
    return m_centroid;
}


/******************************************************
 * Private Functions
 *****************************************************/

void PointCloud::initializeBuffers() {
    if (!m_positionsBuffer->create())
        qFatal("Unable to create position buffer");
}

void PointCloud::additionalChanges() {
    if (m_pointsChanged)
        updatePoints();
}

void PointCloud::updatePoints() {
    m_vao->bind();

    m_positionsBuffer->bind();
    m_positionsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionsBuffer->allocate(m_dataHead, 3 * m_drawCount * sizeof(float));

    m_shader->bind();

    m_positionsBuffer->bind();
    m_shader->enableAttributeArray("vertexPosition");
    m_shader->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vao->release();

    m_pointsChanged = false;
}