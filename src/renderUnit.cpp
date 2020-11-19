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
#include <cmath>
#include <QtMath>

RenderUnit::RenderUnit(QObject *parent)
        : QObject(parent)
        , m_coordinateMirroring(DoNotMirrorCoordinates)
        , m_center(0.0, 0.0, 0.0)
        , m_bg_color(QVector4D(0.7, 0.92, 1.0, 1.0))
{
    const float azimuth = 0.0f;
    const float elevation = 15.0f;

    const float distance = 2.0f;
    const float azimuthInRadians = qDegreesToRadians(azimuth);
    const float elevationInRadians = qDegreesToRadians(elevation);

    m_eye = distance * QVector3D(std::cos(elevationInRadians) * std::cos(azimuthInRadians),
                                std::sin(elevationInRadians),
                                -std::cos(elevationInRadians) * std::sin(azimuthInRadians));
}

RenderUnit::~RenderUnit()
{
    invalidate();
}

void RenderUnit::render()
{
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 modelMatrix = m_arcball.getModel();
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    modelMatrix.rotate(-90, 0, 1, 0);

    modelMatrix.translate(-m_center);

    viewMatrix.lookAt(m_eye,
                      QVector3D(0,0,0),
                      QVector3D(0,1,0));


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

    functions->glClearColor(m_bg_color.x(), m_bg_color.y(), m_bg_color.z(), m_bg_color.w());
    functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    functions->glEnable(GL_DEPTH_TEST);
    functions->glEnable(GL_BLEND);
    functions->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for(std::shared_ptr<Geometry> geo: m_geometries) {
        geo->render(m_eye, modelMatrix, viewMatrix, projectionMatrix);
    }
}

void RenderUnit::invalidate()
{
    for(std::shared_ptr<Geometry> geo: m_geometries) {
        geo->invalidate();
    }
}

void RenderUnit::rotate(const QVector2D &move, const QVector2D &start, const QVector2D &screen) {
    m_arcball.rotate(move, start, screen);
}


void RenderUnit::pan(const QVector2D &move, const QVector2D &start, const QVector2D &screen) {
    m_arcball.translate(move, start, screen);
}

void RenderUnit::zoom(const QVector2D &move, const QVector2D &start, const QVector2D &screen) {
    m_arcball.zoom(move, start, screen);
}

void RenderUnit::setCenter(const QVector3D &center) {
    m_center = center;
}

void RenderUnit::setBgColor(const QVector4D &color) {
    m_bg_color = color;
}

void RenderUnit::addGeometry(const std::shared_ptr<Geometry> &geometry) {
    m_geometries.push_back(geometry);
}

std::shared_ptr<Geometry> & RenderUnit::getGeometry(const unsigned int &id) {
    return m_geometries.at(id);
}

void RenderUnit::clearGeometries() {
    m_geometries.clear();
}

int RenderUnit::geometryCount() {
    return m_geometries.size();
}

Arcball & RenderUnit::getArcballReference() {
    return m_arcball;
}