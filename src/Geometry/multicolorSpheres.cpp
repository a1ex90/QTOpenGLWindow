/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %#  #    CC        V    V  MM M  M MM RR    RR
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
 *       @date:   13.10.20
 *****************************************************/

#include "multicolorSpheres.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

/******************************************************
 * Constructors
 *****************************************************/

MCSphereCloud::MCSphereCloud() :
    m_colorBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_recolor(true)
    , m_colors(nullptr) {
    m_type = GeometryType::BULKCLOUD;
    // Default color
    m_possibleColors.push_back(QVector3D(1,0,0));
}

/******************************************************
 * Public Functions
 *****************************************************/
void MCSphereCloud::render(const QVector3D &eye, const QMatrix4x4 &modelMatrix, const QMatrix4x4 &viewMatrix, const QMatrix4x4 &projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;
    const QMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

    GLint viewportSize[4];
    functions->glGetIntegerv(GL_VIEWPORT, viewportSize);

    m_shader->bind();

    m_shader->setUniformValue("eye", modelViewMatrix * eye);

    m_shader->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformValue("mvp", modelViewProjectionMatrix);
    m_shader->setUniformValue("R", m_pointSize);
    m_shader->setUniformValue("viewport", QVector4D(viewportSize[0], viewportSize[1], viewportSize[2], viewportSize[3]));

    m_shader->setUniformValue("light.position", QVector4D(1.0, 1.0, 1.0, 0.0));
    m_shader->setUniformValue("light.intensity", QVector3D(1.0, 1.0, 1.0));

    m_vao->bind();
    functions->glEnable(GL_PROGRAM_POINT_SIZE);
    functions->glEnable(GL_POINT_SPRITE);
    functions->glDrawArrays(GL_POINTS, 0, m_drawCount);
    m_vao->release();
}

void MCSphereCloud::invalidate() {
    m_positionsBuffer->destroy();
    m_colorBuffer->destroy();
    m_shader.reset();
    m_vao->destroy();
}

void MCSphereCloud::changePoints(float *dataHead, int length) {
    m_dataHead = dataHead;
    if(m_drawCount != length) {
        m_drawCount = length;
        m_recolor = true;
    }
    m_pointsChanged = true;
}

void MCSphereCloud::setColors(const QList<QVector3D> &colors) {
    m_possibleColors = colors;
}

/******************************************************
 * Private Functions
 *****************************************************/

void MCSphereCloud::initializeBuffers() {
    if (!m_positionsBuffer->create())
        qFatal("Unable to create position buffer");
    if (!m_colorBuffer->create())
        qFatal("Unable to create color buffer");
}

void MCSphereCloud::additionalChanges() {
    if (m_pointsChanged) {
        updatePoints();
        if (m_recolor) {
            generateColorBuffer();
            updateColors();
        }
    }
}

void MCSphereCloud::updateColors() {
    m_vao->bind();

    m_colorBuffer->bind();
    m_colorBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorBuffer->allocate(m_colors, 3 * m_drawCount * sizeof(float));

    m_shader->bind();

    m_colorBuffer->bind();
    m_shader->enableAttributeArray("vertexColor");
    m_shader->setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);

    m_vao->release();
    m_recolor = false;
}

void MCSphereCloud::generateColorBuffer() {
    m_colors = new float[3 * m_drawCount];
    for(int i = 0; i < m_drawCount; i++) {
        m_colors[3*i] = m_possibleColors[i % m_possibleColors.count()].x();
        m_colors[3*i + 1] = m_possibleColors[i % m_possibleColors.count()].y();
        m_colors[3*i + 2] = m_possibleColors[i % m_possibleColors.count()].z();
    }
}
