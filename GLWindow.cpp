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

    demo_buffer_destroy (context()->extraFunctions(), buffer);
    demo_font_destroy (context()->extraFunctions(), font);

    FT_Done_Face (ft_face);
    FT_Done_FreeType (ft_library);

    demo_view_destroy (vu);
    demo_glstate_destroy (context()->extraFunctions(), st);
}

void GLWindow::initializeGL()
{
    qDebug() << "Vendor graphic card:" << (const char *) glGetString(GL_VENDOR);
    qDebug() << "Renderer:" << (const char *) glGetString(GL_RENDERER);
    qDebug() << "Version GL:" << (const char *) glGetString(GL_VERSION);
    qDebug() << "Version GLSL:" << (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()), Qt::DirectConnection);

//    gles1_wrapper = new GLES1_Wrapper(context());

    st = demo_glstate_create (context()->extraFunctions());
    vu = demo_view_create (st);
    demo_view_print_help (vu);

    FT_Init_FreeType (&ft_library);
    FT_New_Face(ft_library, "/System/Library/Fonts/Times.ttc", 0/*face_index*/, &ft_face);
    if (!ft_face) qFatal("failed to open font file");

    font = demo_font_create (ft_face, demo_glstate_get_atlas (st));
    buffer = demo_buffer_create (context()->extraFunctions());
    glyphy_point_t top_left = {0, 0};
    demo_buffer_move_to (buffer, &top_left);
    demo_buffer_add_text (context()->extraFunctions(), buffer, "1\n2", font, 200);

    demo_font_print_stats (font);

    demo_view_setup (context()->extraFunctions(), vu);
}

void GLWindow::resizeGL(int w, int h) {
    demo_view_reshape_func (context()->extraFunctions(), vu, w, h);
}

void GLWindow::paintGL()
{
    demo_view_display(context()->extraFunctions(), vu, buffer);
}

void GLWindow::keyPressEvent(QKeyEvent * keyEvent)
{
    demo_view_keyboard_func(context()->extraFunctions(), vu, keyEvent->key());
}

void GLWindow::keyReleaseEvent(QKeyEvent * keyEvent)
{
}

void GLWindow::mousePressEvent(QMouseEvent *)
{
}

void GLWindow::mouseReleaseEvent(QMouseEvent *)
{
}

void GLWindow::mouseMoveEvent(QMouseEvent *)
{
}
