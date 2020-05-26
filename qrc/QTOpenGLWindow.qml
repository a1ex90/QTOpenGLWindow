import QtQuick 2.7
import QtQuick.Controls 1.0

import opengl.qt.viewer 1.0

Item {
    id: parWindow
    width: parent.width
    height: parent.height

    property RenderUnit renderer: RenderUnit{parent: parWindow; width: parWindow.width; height: parWindow.height; objectName: "renderunit_id"}

    MouseArea {
        property bool panning: false
        property bool rotating: false
        property bool zooming: false
        property vector2d startP: Qt.vector2d(0,0);
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        onPressed: {
            startP = Qt.vector2d(mouseX, mouseY);
            if(mouse.button == Qt.LeftButton) {
                rotating = true;
            } else if(mouse.button == Qt.MiddleButton) {
                panning = true;
            } else if(mouse.button == Qt.RightButton) {
                zooming = true;
            }
        }
        onReleased: {
            if(mouse.button == Qt.LeftButton) {
                rotating = false;
            } else if(mouse.button == Qt.MiddleButton) {
                panning = false;
            } else if(mouse.button == Qt.RightButton) {
                zooming = false;
            }
        }
        onPositionChanged: {
            if(rotating) {
                var moveP = Qt.vector2d(mouseX, mouseY);
                renderer.mouseRotate(moveP, startP, Qt.vector2d(parent.width, parent.height));
                startP = moveP;
            } else if(panning) {
                var moveP = Qt.vector2d(mouseX, mouseY);
                var translation = Qt.vector2d(2.0 * (startP.x - moveP.x) / parent.width, 2.0 * (startP.y - moveP.y) / parent.height);
                renderer.mouseMove(translation, 2);
                startP = moveP;
            } else if(zooming) {
                var moveP = Qt.vector2d(mouseX, mouseY);
                var zoom = Qt.vector2d(0.0, 1.0 + (moveP.y - startP.y) / parent.height);
                renderer.mouseMove(zoom, 3);
                startP = moveP;
            }
        }
    }
}
