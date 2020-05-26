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
        , m_mouseOld(0,0)
        , m_screenDim(0,0)
{
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer *FrameBufferObject::createRenderer() const
{
    return new FrameBufferObjectRenderer;
}

void FrameBufferObject::mouseMove(QVector2D move, int mode) {
    m_mouseMode = mode;
    m_mouseMove = move;
}

void FrameBufferObject::mouseRotate(QVector2D move, QVector2D old, QVector2D screen) {
    m_mouseMove = move;
    m_mouseOld = old;
    m_screenDim = screen;
    m_mouseMode = 1;
}

int FrameBufferObject::readMouseMove(QVector2D &move) {
    move = m_mouseMove;
    int mode = m_mouseMode;
    m_mouseMove = QVector2D(0,0);
    m_mouseMode = 0;
    update();
    return mode;
}

void FrameBufferObject::readMouseRotate(QVector2D &old, QVector2D &screen) {
    old = m_mouseOld;
    screen = m_screenDim;
    m_mouseOld = QVector2D(0,0);
}