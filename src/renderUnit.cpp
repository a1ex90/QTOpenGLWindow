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
 *       @date:   12.02.2020
 *****************************************************/

#include "renderUnit.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QMatrix4x4>

#include <QDebug>

#include <cmath>
#include <QtMath>

RenderUnit::RenderUnit(QObject *parent)
        : QObject(parent)
        , m_coordinateMirroring(DoNotMirrorCoordinates)
        , m_azimuth(0.0)
        , m_elevation(15.0)
        , m_distance(15.0)
        , m_center(0.0, 0.0, 0.0)
{
}

RenderUnit::~RenderUnit()
{
    invalidate();
}

void RenderUnit::render()
{
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    modelMatrix.rotate(-90, 0, 1, 0);

    modelMatrix.translate(-m_center);

    const float azimuthInRadians = qDegreesToRadians(m_azimuth);
    const float elevationInRadians = qDegreesToRadians(m_elevation);

    const QVector3D eyePosition(std::cos(elevationInRadians) * std::cos(azimuthInRadians),
                                std::sin(elevationInRadians),
                                -std::cos(elevationInRadians) * std::sin(azimuthInRadians));

    QVector3D upVector = qFuzzyCompare(m_elevation, 90.0f)
                         ? QVector3D(-std::cos(azimuthInRadians), 0, std::sin(azimuthInRadians))
                         : QVector3D(0, 1, 0);

    viewMatrix.lookAt(eyePosition * m_distance,
                      QVector3D(0,0,0),
                      upVector);


    GLint viewportSize[4];
    functions->glGetIntegerv(GL_VIEWPORT, viewportSize);

    projectionMatrix.perspective(30, float(viewportSize[2]) / viewportSize[3], 0.01, 1000);

    switch (m_coordinateMirroring) {
        case RenderUnit::DoNotMirrorCoordinates:
            break;
        case RenderUnit::MirrorYCoordinate:
            projectionMatrix.scale(1, -1, 1);
            break;
    }

    functions->glClearColor(0.7, 0.92, 1.0, 1.0);
    functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    functions->glEnable(GL_DEPTH_TEST);
    functions->glEnable(GL_BLEND);

    for(std::shared_ptr<Geometry> geo: m_geometries) {
        geo->render(modelMatrix, viewMatrix, projectionMatrix);
    }
}

void RenderUnit::invalidate()
{
    for(std::shared_ptr<Geometry> geo: m_geometries) {
        geo->invalidate();
    }
}

void RenderUnit::setAzimuth(float azimuth)
{
    m_azimuth = azimuth;
}

void RenderUnit::setElevation(float elevation)
{
    m_elevation = elevation;
}

void RenderUnit::setDistance(float distance)
{
    m_distance = distance;
}

void RenderUnit::setCenter(QVector3D center) {
    m_center = center;
}

void RenderUnit::addGeometry(const std::shared_ptr<Geometry> &geometry) {
    m_geometries.push_back(geometry);
}

std::shared_ptr<Geometry> & RenderUnit::getGeometry(const unsigned int &id) {
    return m_geometries.at(id);
}