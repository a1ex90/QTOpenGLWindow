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

// FBO implementation

FrameBufferObject::FrameBufferObject(QQuickItem *parent)
        : QQuickFramebufferObject(parent)
        , m_mouseMode(0)
        , m_mouseMove(0,0)
        , m_mouseStart(0, 0)
{
    setMirrorVertically(true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

QQuickFramebufferObject::Renderer *FrameBufferObject::createRenderer() const
{
    return new FrameBufferObjectRenderer;
}

int FrameBufferObject::readMouse(QVector2D &move, QVector2D &start, QVector2D &screen) {
    move = m_mouseMove;
    start = m_mouseStart;
    screen = {(float)this->width(), (float)this->height()};
    m_mouseStart = m_mouseMove;
    update();
    return m_mouseMode;
}

void FrameBufferObject::mousePressEvent(QMouseEvent *event) {
    m_mouseStart = QVector2D(event->x(), event->y());
    m_mouseMove = m_mouseStart;
    if(event->button() == Qt::LeftButton) {
        m_mouseMode = 1;
    } else if(event->button() == Qt::MiddleButton) {
        m_mouseMode = 2;
    } else if(event->button() == Qt::RightButton) {
        m_mouseMode = 3;
    }
}

void FrameBufferObject::mouseReleaseEvent(QMouseEvent *event) {
    m_mouseMode = 0;
}

void FrameBufferObject::mouseMoveEvent(QMouseEvent *event) {
    if(m_mouseMode != 0) {
        m_mouseStart = m_mouseMove;
        m_mouseMove = {(float)event->x(), (float)event->y()};
    }
}