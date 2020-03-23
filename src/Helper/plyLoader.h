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

#ifndef QTSIMVIEW_PLYLOADER_H
#define QTSIMVIEW_PLYLOADER_H

#include <QVector>
#include <QVector3D>

class QIODevice;


class PlyLoader {
public:
    PlyLoader();

    bool load( const QString& fileName );
    bool load( QIODevice* ioDev );

    QVector<QVector3D> positions() const { return m_points; }
    QVector3D centroid() const { return m_centroid; }

    static QVector3D centroid(QVector<QVector3D>);

private:
    QVector<QVector3D> m_points;
    QVector3D m_centroid;
};


#endif //QTSIMVIEW_PLYLOADER_H
