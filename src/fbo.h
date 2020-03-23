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

    Q_PROPERTY(float azimuth READ azimuth WRITE setAzimuth NOTIFY azimuthChanged)
    Q_PROPERTY(float elevation READ elevation WRITE setElevation NOTIFY elevationChanged)
    Q_PROPERTY(float distance READ distance WRITE setDistance NOTIFY distanceChanged)

public:
    explicit FrameBufferObject(QQuickItem *parent = 0);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    float azimuth() const;
    float distance() const;
    float elevation() const;

    signals:
    void azimuthChanged(float azimuth);
    void distanceChanged(float distance);
    void elevationChanged(float elevation);

public slots:
    void setAzimuth(float azimuth);
    void setDistance(float distance);
    void setElevation(float elevation);

private:
    float m_azimuth;
    float m_elevation;
    float m_distance;
};

#endif //QTSIMVIEW_FBO_H
