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

#ifndef QTSIMVIEW_OBJLOADER_H
#define QTSIMVIEW_OBJLOADER_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include <limits>

class QString;
class QIODevice;

struct FaceIndices;

class ObjLoader
{
public:
    ObjLoader();

    void setLoadTextureCoordinatesEnabled( bool b ) { m_loadTextureCoords = b; }
    bool isLoadTextureCoordinatesEnabled() const { return m_loadTextureCoords; }

    void setMeshCenteringEnabled( bool b ) { m_centerMesh = b; }
    bool isMeshCenteringEnabled() const { return m_centerMesh; }

    bool hasNormals() const { return !m_normals.isEmpty(); }
    bool hasTextureCoordinates() const { return !m_texCoords.isEmpty(); }

    bool load( const QString& fileName );
    bool load( QIODevice* ioDev );

    QVector<QVector3D> vertices() const { return m_points; }
    QVector<QVector3D> normals() const { return m_normals; }
    QVector<QVector2D> textureCoordinates() const { return m_texCoords; }
    QVector<unsigned int> indices() const { return m_indices; }

private:
    void updateIndices(const QVector<QVector3D> &positions,
                       const QVector<QVector3D> &normals,
                       const QVector<QVector2D> &texCoords,
                       const QHash<FaceIndices, unsigned int> &faceIndexMap,
                       const QVector<FaceIndices> &faceIndexVector);
    void generateAveragedNormals( const QVector<QVector3D>& points,
                                  QVector<QVector3D>& normals,
                                  const QVector<unsigned int>& faces ) const;
    void center( QVector<QVector3D>& points );

    bool m_loadTextureCoords;
    bool m_generateTangents;
    bool m_centerMesh;

    QVector<QVector3D> m_points;
    QVector<QVector3D> m_normals;
    QVector<QVector2D> m_texCoords;
    QVector<unsigned int> m_indices;
};


#endif //QTSIMVIEW_OBJLOADER_H
