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

#ifndef QTSIMVIEW_FBO_H
#define QTSIMVIEW_FBO_H

#include <QQuickFramebufferObject>

/**
 * \class FrameBufferObject
 *
 * \brief FBO. Reads and passes mouse events and creates the renderer.
 */
class FrameBufferObject : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    /**
     * Constructor
     */
    explicit FrameBufferObject(QQuickItem *parent = 0);

    /**
     * Creates the renderer
     * @return renderer
     */
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    int readMouse(QVector2D &move, QVector2D &start, QVector2D &screen);

    /**
     * Saves previous and current mouse position. Sets mouse mode:
     * left-click rotate, middle-button-click panning and right-click
     * zooming
     * @param event mouse press event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Unsets mouse mode when button is released
     * @param event mouse release event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * Updates rotation, panning or zooming during mouse move,
     * when button is pressed
     * @param event mouse move event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    // previous mouse position
    QVector2D m_mouseStart;
    // current(latest) mouse position
    QVector2D m_mouseMove;
    // MouseMoveMode 0 = none, 1 = rotate, 2 = pan, 3 = zoom
    int m_mouseMode;
};

#endif //QTSIMVIEW_FBO_H
