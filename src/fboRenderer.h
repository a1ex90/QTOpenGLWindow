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
 *       @date:   20.03.20
 *****************************************************/

#ifndef QTSIMVIEW_FBORENDERER_H
#define QTSIMVIEW_FBORENDERER_H


#include <QQuickFramebufferObject>
#include "renderUnit.h"
#include "fbo.h"

/**
 * \class FrameBufferObjectRenderer
 *
 * \brief Class template for the FBO Renderer. Overrides QT's FBO Renderer.
 */
class FrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer {
public:
    /**
     * Constructor
     */
    FrameBufferObjectRenderer();

    /**
     * Process tasks during at times where it's safe to synchronizes. Pulls
     * mouse events and forwards addSync function.
     * @param item parental FBO
     */
    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE;

    /**
     * Override this with additional operations needed during synchronization phase
     * like loading in new meshes, etc.
     * @param item parental FBO
     */
    virtual void addSync(QQuickFramebufferObject *item){}

    /**
     * Actual FBO Renderer render function. Just calls render function from Renderunit.
     */
    void render() Q_DECL_OVERRIDE;

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

protected:
    // Renderunit
    RenderUnit m_render;

    // Parental window
    QQuickWindow *m_window;
};


#endif //QTSIMVIEW_FBORENDERER_H
