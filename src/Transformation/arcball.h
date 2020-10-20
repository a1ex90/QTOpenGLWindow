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

#include "qDualQuaternion.h"

/**
 * \class Arcball
 *
 * \brief Arcball class for manipulating the szene view. Has methods for panning,
 * zooming and rotation. Actually moves and scales all objects by a model
 * transformation in front of a fixed camera position.
 */
class Arcball {
public:
    /**
     * Constructor
     */
    Arcball();

    /**
     * Resets the view to initial condition
     */
    void reset();

    /**
     * Performs an arcball rotation
     * @param current current mouse position
     * @param start initial mouse position
     * @param screen window size
     */
    void rotate(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    /**
     * Performs a pan perpendicular to the current viewing direction
     * @param current current mouse position
     * @param start initial mouse position
     * @param screen window size
     */
    void translate(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    /**
     * Performs a zoom in the current viewing direction
     * @param current current mouse position
     * @param start initial mouse position
     * @param screen window size
     */
    void zoom(const QVector2D &current, const QVector2D &start, const QVector2D &screen);

    /**
     * Transforms the dual quaternion representation to a 4x4 model matrix
     * @return 4x4 model view matrix
     */
    QMatrix4x4 getModel();

    /**
     * Passes the current Arcball parameter
     * @param position[out] current position
     * @param rotation[out] current rotation
     * @param zoom[out] current zoom
     */
    void getParameter(QVector3D &position, QQuaternion &rotation, float &zoom);

    /**
     * Sets the initial Arcball parameter
     * @param position initial position
     * @param rotation initial rotation
     * @param zoom initial zoom
     */
    void setParameter(const QVector3D &position, const QQuaternion &rotation, const float &zoom);
private:
    void updateTransformation();
    static QQuaternion projectOnSphere(QVector2D point, const QVector2D &screen);
protected:
    // Positions initial, current, target
    QVector3D m_pos0, m_posCur, m_posTar;
    // Rotation initial, current, target
    QQuaternion m_rot0, m_rotCur, m_rotTar;
    // Zoom initial, current, target
    float m_zoom0, m_zoomCur, m_zoomTar;
    // Current view representation
    QDualQuaternion m_view;
};


#endif //QTOPENGLWINDOW_ARCBALL_H
