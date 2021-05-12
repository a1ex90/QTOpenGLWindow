# QTOpenGLWindow
This is an OpenGL Viewer Item for Qt5, which can be added as a submodule and embedded in Qt Quick 2 applications. Hold right-mouse-button for zooming, middle-mouse-button for panning and left-mouse-button for arcball rotation.

## Requirements
- Qt 5.9.5
- Qt Quick 2.7
- OpenGL 4.*
- CMake
- C++ 14

## Testing
CMake can be advised to build a test application by passing a variable `BUILD_TESTS` to Cmake. (CMake option `-DBUILD_TESTS=1`)

![test app picture](https://raw.githubusercontent.com/a1ex90/QTOpenGLWindow/master/test/assets/app_prev.png)

## Setup 
The following steps need to be done to add this module to an existing project:
1. clone this module to a folder inside the project (e.g. `ext/QTOpenGLWindow`) or directly add this module as a submodule to the project git
```
git submodule add 'link_to_this_repo' ext/QTOpenGLWindow
```
2. add this module to the project CMake file
```
add_subdirectory(ext/QTOpenGLWindow)
...
target_link_libraries(...
        QTOpenGLWindow
        ...)
```
3. add this module to the project qrc file
```
<qresource>
    <file>../ext/QTOpenGLWindow/qrc/</file>
</qresource>
```

## Usage
For rendering some geometry the `FrameBufferObject` and `FrameBufferObjectRender` need to be extended. An easy example can be found in the `openGLWindow` class inside the `test` folder. The `FrameBufferObject` can also be extended to have new signals and slots to interact with the Qt Quick application. The `addSync` function of the `FrameBufferObjectRender` class can be overwritten, to manipulate geometry objects safely during runtime. Further renderable geometry can be created by extending the geometry class.

The extended `FrameBufferObject` needs to be registered as a qml module inside the main.cpp, like e.g.:
```
qmlRegisterType<FBO>("opengl.qt.viewer", 1, 0, "RenderUnit");
```

This so generated module plus the qml from the submodule need to be imported in the project's qml file, like e.g.:
```
import "ext/QTOpenGLWindow/qrc"
import opengl.qt.viewer 1.0
```

Finally, the `QTOpenGLWindow` can be defined with an id inside the qml `QTOpenGLWindow { id:openGLWindow }`. Its attributes (e.g. `azimuth`) can be read/set by accessing them like `openGLWindow.renderer.azimuth`. 


