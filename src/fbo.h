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

#ifndef QTSIMVIEW_FBO_H
#define QTSIMVIEW_FBO_H

#include <QQuickFramebufferObject>

class FrameBufferObject : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    explicit FrameBufferObject(QQuickItem *parent = 0);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    Q_INVOKABLE void mouseMove(QVector2D move, int mode);
    Q_INVOKABLE void mouseRotate(QVector2D move, QVector2D old, QVector2D screen);

    int readMouseMove(QVector2D &move);
    void readMouseRotate(QVector2D &old, QVector2D &screen);

private:
    QVector2D m_screenDim;
    QVector2D m_mouseOld;
    QVector2D m_mouseMove;
    // MouseMoveMode 0 = none, 1 = rotate, 2 = pan, 3 = zoom
    int m_mouseMode;
};

#endif //QTSIMVIEW_FBO_H
