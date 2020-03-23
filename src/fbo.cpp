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
 *       @date:   20.03.2020
 *****************************************************/

#include "fbo.h"

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include "fboRenderer.h"

// MyFrameBufferObject implementation

FrameBufferObject::FrameBufferObject(QQuickItem *parent)
        : QQuickFramebufferObject(parent)
        , m_azimuth(0.0)
        , m_elevation(15.0)
        , m_distance(5.0)
{
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer *FrameBufferObject::createRenderer() const
{
    return new FrameBufferObjectRenderer;
}

float FrameBufferObject::azimuth() const
{
    return m_azimuth;
}

float FrameBufferObject::distance() const
{
    return m_distance;
}

float FrameBufferObject::elevation() const
{
    return m_elevation;
}

void FrameBufferObject::setAzimuth(float azimuth)
{
    if (m_azimuth == azimuth)
        return;

    m_azimuth = azimuth;
    emit azimuthChanged(azimuth);
    update();
}

void FrameBufferObject::setDistance(float distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(distance);
    update();
}

void FrameBufferObject::setElevation(float elevation)
{
    if (m_elevation == elevation)
        return;

    m_elevation = elevation;
    emit elevationChanged(elevation);
    update();
}