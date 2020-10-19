/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %#  #    CC        V    V  MM M  M MM RR    RR
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
 *       @date:   19.10.20
 *****************************************************/

#ifndef QTOPENGLWINDOW_ARCBALL_H
#define QTOPENGLWINDOW_ARCBALL_H

#include "qDualeQuaternion.h"


class Arcball {
public:
    Arcball();

    void reset();

    void updateTransformation();

    void rotate(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    void translate(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    void zoom(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    QMatrix4x4 getModel() { return m_view.toMatrix(); }
private:
    QQuaternion projectOnSphere(QVector2D point, const QVector2D &screen);
protected:
    QVector3D m_pos0, m_posCur, m_posTar;
    QQuaternion m_rot0, m_rotCur, m_rotTar;
    float m_zoom0, m_zoomCur, m_zoomTar;
    QDualQuaternion m_view;
};


#endif //QTOPENGLWINDOW_ARCBALL_H
