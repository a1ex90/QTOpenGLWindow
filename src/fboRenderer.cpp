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

#include "fboRenderer.h"
#include <QQuickWindow>
#include <QOpenGLFramebufferObject>

FrameBufferObjectRenderer::FrameBufferObjectRenderer() {}

void FrameBufferObjectRenderer::synchronize(QQuickFramebufferObject *item)
{
    m_window = item->window();

    FrameBufferObject *i = static_cast<FrameBufferObject *>(item);
    m_render.setAzimuth(i->azimuth());
    m_render.setElevation(i->elevation());
    m_render.setDistance(i->distance());

    addSync(item);
}

void FrameBufferObjectRenderer::render() {
        m_render.render();
        m_window->resetOpenGLState();
}

QOpenGLFramebufferObject * FrameBufferObjectRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}