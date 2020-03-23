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

#ifndef QTSIMVIEW_FBORENDERER_H
#define QTSIMVIEW_FBORENDERER_H


#include <QQuickFramebufferObject>
#include "renderUnit.h"
#include "fbo.h"

class FrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer {
public:
    FrameBufferObjectRenderer();

    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE;

    /**
     * Override this with additional operations needed during synchronization phase
     * like loading in new meshes, etc.
     * @param item
     */
    virtual void addSync(QQuickFramebufferObject *item){}

    void render() Q_DECL_OVERRIDE;

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

protected:
    RenderUnit m_render;
    QQuickWindow *m_window;
};


#endif //QTSIMVIEW_FBORENDERER_H
