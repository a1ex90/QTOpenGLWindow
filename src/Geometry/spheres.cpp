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
 *       @date:   10.07.20
 *****************************************************/

#include "spheres.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

/******************************************************
 * Constructors
 *****************************************************/

SphereCloud::SphereCloud() : PointCloud() {
    m_type = GeometryType::SPHERECLOUD;
}

/******************************************************
 * Public Functions
 *****************************************************/

void SphereCloud::render(QMatrix4x4 modelMatrix, QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;
    const QMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

    GLint viewportSize[4];
    functions->glGetIntegerv(GL_VIEWPORT, viewportSize);

    m_shader->bind();
    m_shader->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformValue("mvp", modelViewProjectionMatrix);
    m_shader->setUniformValue("invmvp", modelViewProjectionMatrix.inverted());
    m_shader->setUniformValue("invProjectionMatrix", projectionMatrix.inverted());
    m_shader->setUniformValue("R", m_pointSize);
    m_shader->setUniformValue("viewport", QVector4D(viewportSize[0], viewportSize[1], viewportSize[2], viewportSize[3]));
    m_shader->setUniformValue("color", QVector4D(m_color, 1.0));

    m_shader->setUniformValue("light.position", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_shader->setUniformValue("light.intensity", QVector3D(1.0, 1.0, 1.0));

    m_vao->bind();
    functions->glEnable(GL_PROGRAM_POINT_SIZE);
    functions->glEnable(GL_LIGHTING);
    functions->glEnable(GL_COLOR_MATERIAL);
    functions->glDrawArrays(GL_POINTS, 0, m_drawCount);
    m_vao->release();
}
