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

#include "arcball.h"
#include <cmath>
#include <QVector2D>

/******************************************************
 * Constructors
 *****************************************************/

Arcball::Arcball() {
    m_pos0 = m_posCur = m_posTar = {0,0,0};
    m_rot0 = m_rotCur = m_rotTar = {1.0f,0,0,0};
    m_zoom0 = m_zoomCur = m_zoomTar = 1.0f;
    m_view = {m_rot0, m_pos0};
}

/******************************************************
 * Public Functions
 *****************************************************/

void Arcball::reset() {
    m_posTar = m_pos0;
    m_rotTar = m_rot0;
    m_zoomTar = m_zoom0;
}

void Arcball::rotate(const QVector2D &current, const QVector2D &start, const QVector2D &screen) {
    const QQuaternion prevRot = projectOnSphere(start, screen);
    const QQuaternion curRot = projectOnSphere(current, screen);
    m_rotTar = (curRot * prevRot * m_rotTar).normalized();
}

void Arcball::translate(const QVector2D &current, const QVector2D &start, const QVector2D &screen) {
    QVector3D moveP = { 0, 2.0f * (start.y() - current.y()) / screen.y(), 2.0f * (start.x() - current.x()) / screen.x()};
    moveP = 0.5f * moveP;
    m_posTar += moveP;
}

void Arcball::zoom(const QVector2D &current, const QVector2D &start, const QVector2D &screen) {
    float zoom = (current.y() - start.y()) / screen.y();
    m_zoomTar += zoom;
    if(m_zoomTar < 0) {
        m_zoomTar = 0;
    }
}

QMatrix4x4 Arcball::getModel() {
    updateTransformation();
    QMatrix4x4 tmp = m_view.toMatrix();
    tmp.scale(m_zoomCur);
    return tmp;
}

void Arcball::getParameter(QVector3D &position, QQuaternion &rotation, float &zoom) {
    position = m_posCur;
    rotation = m_rotCur;
    zoom = m_zoomCur;
}

void Arcball::setParameter(const QVector3D &position, const QQuaternion &rotation, const float &zoom) {
    m_pos0 = m_posTar = position;
    m_rot0 = m_rotTar = rotation;
    m_zoom0 = m_zoomTar = zoom;
}

/******************************************************
 * Private Functions
 *****************************************************/

void Arcball::updateTransformation() {
    const QVector3D diffPos = m_posTar - m_posCur;
    const float dPos = QVector3D::dotProduct(diffPos, diffPos);
    const float diffZoom = m_zoomTar - m_zoomCur;
    const float dZoom = diffZoom * diffZoom;
    const QQuaternion diffRot = m_rotTar - m_rotCur;
    const float dRot = QQuaternion::dotProduct(diffRot, diffRot);
    if(dPos < 1.0e-10f && dZoom < 1.0e-10f && dRot < 1.0e-10f)
        return;
    m_posCur = m_posTar;
    m_zoomCur = m_zoomTar;
    m_rotCur = m_rotTar;

    m_view =  QDualQuaternion(m_rotCur) * QDualQuaternion::translation(m_posCur);
}

QQuaternion Arcball::projectOnSphere(QVector2D point, const QVector2D &screen) {
    point.setX(2.0f * point.x() / screen.x() - 1.0f);
    point.setY(1.0f - 2.0f * point.y() / screen.y());
    const float dist = QVector2D::dotProduct(point, point);
    float z;
    if(dist <= 1.0f) {
        z = sqrtf(1.0f - dist);
    } else {
        // point outside sphere => project
        point = point.normalized();
        z = 0.0f;
    }
    return {0, -z, -point.y(), point.x()};
}
