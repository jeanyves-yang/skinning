#pragma once

#ifndef MY_WIDGET_GL_HPP
#define MY_WIDGET_GL_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>

#include "../../lib/interface/navigator_tool.hpp"
#include "../../lib/mesh/mesh.hpp"
#include "../../lib/opengl/mesh_opengl.hpp"
#include "../../lib/opengl/axes_helper.hpp"
#include "../../lib/interface/camera_matrices.hpp"
#include "../scene/scene.hpp"


/** Qt Widget to render OpenGL scene */
class myWidgetGL : public QGLWidget
{
    Q_OBJECT

public:

    myWidgetGL(const QGLFormat& format,QGLWidget *parent = 0);
    ~myWidgetGL();

    /** Set the drawing on/off */
    void change_draw_state();
    /** Set the wireframe on/off */
    void wireframe(bool est_actif);
    /** Get the current cameras values */
    cpe::camera_matrices const& camera() const;

    /** Load a texture given by its filename */
    GLuint load_texture_file(std::string const& filename);

protected:

    /** Setup the OpenGL rendering mode */
    void initializeGL();
    /** The actual rendering function */
    void paintGL();
    /** Function called when the window is resized */
    void resizeGL(int width, int height);

    /** Function called a button of the mouse is pressed */
    void mousePressEvent(QMouseEvent *event);
    /** Function called when the mouse is moved */
    void mouseMoveEvent(QMouseEvent *event);
    /** Function called in a timer loop */
    void timerEvent(QTimerEvent *event);
    /** Function called when keyboard is pressed */
    void keyPressEvent(QKeyEvent *event);

private:

    /** Compute the camera value for each drawing */
    void setup_camera();

    /** Init the OpenGL rendering mode once at the beginning */
    void setup_opengl();
    /** Init Glew once at the beginning */
    void setup_glew();
    /** Print on the command line the actual version of the OpenGL Context */
    void print_current_opengl_context() const;

    /** Function drawing the 3 axes on the corner of the screen */
    void draw_axes();


    /** The navigator storing the camera and window information */
    cpe::navigator_tool nav;

    /** All the content of the 3D scene */
    scene scene_3d;

    /** Enable/Disable the drawing of the 3D scene*/
    bool draw_state;

    /** Helper class for drawing the 3D axes */
    cpe::axes_helper axes;

    /** Storage class for the camera data */
    cpe::camera_matrices camera_data;

};

#endif
