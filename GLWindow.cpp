#include "GLWindow.h"

#include <QDebug>
//#include <GLES1_Wrapper/GLES1_Wrapper.h>

//GLES1_Wrapper * gles1_wrapper;

GLWindow::GLWindow(QOpenGLWindow::UpdateBehavior updateBehavior) :
    QOpenGLWindow(updateBehavior)
{
    QSurfaceFormat fmt;
    fmt.setSamples(4);
    fmt.setAlphaBufferSize(8);
    fmt.setRedBufferSize(8);
    fmt.setGreenBufferSize(8);
    fmt.setBlueBufferSize(8);
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);

    // Request OpenGL 4.3 core or OpenGL ES 3.2
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 4.3 core context");
        fmt.setVersion(4, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.2 context");
        fmt.setVersion(3, 2);
    }

    setFormat(fmt);
}

#include "glyphy/demo/demo-buffer.h"
#include "glyphy/demo/demo-font.h"
#include "glyphy/demo/demo-view.h"

FT_Library ft_library;
FT_Face ft_face = nullptr;
demo_font_t *font = nullptr;

static demo_glstate_t *st;
static demo_view_t *vu;
static demo_buffer_t *buffer;

GLWindow::~GLWindow()
{
    makeCurrent();
//    delete gles1_wrapper;

    demo_buffer_destroy (context()->functions(), buffer);
    demo_font_destroy (context()->functions(), font);

    FT_Done_Face (ft_face);
    FT_Done_FreeType (ft_library);

    demo_view_destroy (vu);
    demo_glstate_destroy (context()->functions(), st);
}

void GLWindow::initializeGL()
{
    qDebug() << "Vendor graphic card:" << (const char *) glGetString(GL_VENDOR);
    qDebug() << "Renderer:" << (const char *) glGetString(GL_RENDERER);
    qDebug() << "Version GL:" << (const char *) glGetString(GL_VERSION);
    qDebug() << "Version GLSL:" << (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()), Qt::DirectConnection);

//    gles1_wrapper = new GLES1_Wrapper(context());

    st = demo_glstate_create (context()->functions());
    vu = demo_view_create (st);
    demo_view_print_help (vu);

    FT_Init_FreeType (&ft_library);
    FT_New_Face(ft_library, "/System/Library/Fonts/Times.ttc", 0/*face_index*/, &ft_face);
    if (!ft_face) qFatal("failed to open font file");

    font = demo_font_create (ft_face, demo_glstate_get_atlas (st));

    buffer = demo_buffer_create (context()->functions());
    glyphy_point_t top_left = {0, 0};
    demo_buffer_move_to (buffer, &top_left);
    demo_buffer_add_text (context()->functions(), buffer, "k", font, 1);

    demo_font_print_stats (font);

    demo_view_setup (context()->functions(), vu);
}

void GLWindow::resizeGL(int w, int h) {
    demo_view_reshape_func (context()->functions(), vu, w, h);
}

void GLWindow::paintGL()
{
    demo_view_display(context()->functions(), vu, buffer);

//    glEnable(GL_DEPTH);
//    glClearColor(1, 1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




//    gles1_wrapper->glMatrixMode(GL_PROJECTION);
//    gles1_wrapper->glLoadIdentity();

//    static float angle = 0.0f;

//    gles1_wrapper->glMatrixMode(GL_MODELVIEW);
//    gles1_wrapper->glLoadIdentity();

//    gles1_wrapper->gluPerspective(45.0f, (float)width() / (float)height(), 0.1f, 100.0f);

//    gles1_wrapper->glTranslatef(0.0f, 0.0f, -6.0f);

    // Rotate around the y and z axis.
//    gles1_wrapper->glRotatef(angle, 0.0f, 0.0f, 1.0f);

//    gles1_wrapper->glBegin(GL_TRIANGLES);
//    gles1_wrapper->glColor3f(1.0, 0.0, 0.0); gles1_wrapper->glVertex3f(-1.0, -1.0, 0.0);
//    gles1_wrapper->glColor3f(0.0, 1.0, 0.0); gles1_wrapper->glVertex3f( 0.0,  1.0, 0.0);
//    gles1_wrapper->glColor3f(0.0, 0.0, 1.0); gles1_wrapper->glVertex3f( 1.0, -1.0, 0.0);
//    gles1_wrapper->glEnd();

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    gles1_wrapper->glBegin(GL_QUADS);
//        gles1_wrapper->glVertex3f(-0.5f,  0.0f, 0.0f); // The bottom left corner
//        gles1_wrapper->glVertex3f( 0.0f,  0.5f, 0.0f); // The top left corner
//        gles1_wrapper->glVertex3f( 0.5f,  0.0f, 0.0f); // The top right corner
//        gles1_wrapper->glVertex3f( 0.0f, -0.5f, 0.0f); // The bottom right corner
//    gles1_wrapper->glEnd();

//    gles1_wrapper->glBegin(GL_QUAD_STRIP); // draw in triangle strips
//           gles1_wrapper->glVertex2f(0.0f, 0.75f); // top of the roof
//           gles1_wrapper->glVertex2f(-0.5f, 0.25f); // left corner of the roof
//           gles1_wrapper->glVertex2f(0.5f, 0.25f); // right corner of the roof
//           gles1_wrapper->glVertex2f(-0.5f, -0.5f); // bottom left corner of the house
//           gles1_wrapper->glVertex2f(0.5f, -0.5f); //bottom right corner of the house
//   gles1_wrapper->glEnd();

//    gles1_wrapper->glBegin(GL_QUAD_STRIP); // draw in triangle strips
//           gles1_wrapper->glVertex2f(0.0f, 0.75f); // top of the roof
//           gles1_wrapper->glVertex2f(-0.5f, 0.25f); // left corner of the roof
//           gles1_wrapper->glColor3f(0.0, 0.0, 1.0);
//           gles1_wrapper->glVertex2f(0.5f, 0.25f); // right corner of the roof
//           gles1_wrapper->glColor3f(1.0, 1.0, 1.0);
//           gles1_wrapper->glVertex2f(-0.5f, -0.5f); // bottom left corner of the house
//           gles1_wrapper->glColor3f(0.0, 0.0, 1.0);
//           gles1_wrapper->glVertex2f(0.5f, -0.5f); //bottom right corner of the house
//   gles1_wrapper->glEnd();

   //    gles1_wrapper->glBegin(GL_QUADS);
//        gles1_wrapper->glColor3f(0.0, 0.0, 1.0);
//        gles1_wrapper->glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner
//        gles1_wrapper->glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner
//        gles1_wrapper->glColor3f(1.0, 1.0, 1.0);
//        gles1_wrapper->glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner
//        gles1_wrapper->glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner
//    gles1_wrapper->glEnd();

    //    angle++;
//    angle++;

//    if(angle >= 360.0f)
//    angle = 0.0f;
}
