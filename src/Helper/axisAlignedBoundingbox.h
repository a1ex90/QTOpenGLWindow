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
 *       @date:   12.02.2020
 *****************************************************/

#ifndef QTSIMVIEW_AXISALIGNEDBOUNDINGBOX_H
#define QTSIMVIEW_AXISALIGNEDBOUNDINGBOX_H

#include <QVector>
#include <QVector3D>

class QDebug;

class AxisAlignedBoundingBox
{
public:
    AxisAlignedBoundingBox();

    AxisAlignedBoundingBox(const QVector<QVector3D>& points);

    void update( const QVector<QVector3D>& points );

    QVector3D center() const { return m_center; }
    QVector3D radii() const { return m_radii; }

    QVector3D minPoint() const { return m_center - m_radii; }
    QVector3D maxPoint() const { return m_center + m_radii; }

    float xExtent() const { return 2.0f * m_radii.x(); }
    float yExtent() const { return 2.0f * m_radii.y(); }
    float zExtent() const { return 2.0f * m_radii.z(); }

    float maxExtent() const { return qMax( xExtent(), qMax( yExtent(), zExtent() ) ); }
    float minExtent() const { return qMin( xExtent(), qMin( yExtent(), zExtent() ) ); }

private:
    QVector3D m_center;
    QVector3D m_radii;
};

QDebug & operator<<(QDebug & stream, const AxisAlignedBoundingBox & bbox);


#endif //QTSIMVIEW_AXISALIGNEDBOUNDINGBOX_H
