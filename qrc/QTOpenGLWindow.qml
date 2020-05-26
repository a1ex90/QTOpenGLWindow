import QtQuick 2.7
import QtQuick.Controls 1.0

import opengl.qt.viewer 1.0

Item {
    id: parWindow
    width: parent.width
    height: parent.height

    property RenderUnit renderer: RenderUnit{parent: parWindow; width: parWindow.width; height: parWindow.height; objectName: "renderunit_id"}

    }
