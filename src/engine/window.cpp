#include "window.hpp"

#include "debug.hpp"

Window::Window(unsigned int width, unsigned int height, const std::string & title, bool fullscreen)
  : m_width(width),
	m_height(height),
    m_title(title),
    m_fullscreen(fullscreen),
    m_init(false)
{
}

Window::~Window() {
    
}

void Window::start() {

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		Debug::log("Could not create Window!");
		exit(0);
	}

	glfwMakeContextCurrent(m_window);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		Debug::log("Cound not initialize GLEW!");
		Debug::log(glewGetErrorString(err));
	}

	// if (glewIsSupported("GL_ARB_debug_output")) {
	// 	// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	// 	// glDebugMessageCallback(&Window::debugCallback, stderr);
	// // 	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	// }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow * window, int width, int height){
        
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        width = (width > mode->width) ? mode->width : width;
        height = (height > mode->height) ? mode->height : height;

        Window * win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        win->setWidth(width);
        win->setHeight(height);

        Loop & loop = win->getLoop();
        loop.resizeRenderings(width, height);
    
    });

    m_init = true;

	m_loop.start(m_window);
    glfwDestroyWindow(m_window);

}

void Window::debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                     GLsizei length, const GLchar *message, GLvoid *userParam) {
    
    (void)length;
    FILE *outFile = (FILE*)userParam;
    char finalMessage[256];
    formatDebugOutput(finalMessage, 256, source, type, id, severity, message);
    fprintf(outFile, "%s\n", finalMessage);

}

void Window::formatDebugOutput(char outStr[], size_t outStrSize, GLenum source, GLenum type,
    GLuint id, GLenum severity, const char *msg)
{
    char sourceStr[32];
    const char *sourceFmt = "UNDEFINED(0x%04X)";
    switch(source)

    {
    case GL_DEBUG_SOURCE_API_ARB:             sourceFmt = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:   sourceFmt = "WINDOW_SYSTEM"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: sourceFmt = "SHADER_COMPILER"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:     sourceFmt = "THIRD_PARTY"; break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB:     sourceFmt = "APPLICATION"; break;
    case GL_DEBUG_SOURCE_OTHER_ARB:           sourceFmt = "OTHER"; break;
    }

    snprintf(sourceStr, 32, sourceFmt, source);
 
    char typeStr[32];
    const char *typeFmt = "UNDEFINED(0x%04X)";
    switch(type)
    {

    case GL_DEBUG_TYPE_ERROR_ARB:               typeFmt = "ERROR"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: typeFmt = "DEPRECATED_BEHAVIOR"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:  typeFmt = "UNDEFINED_BEHAVIOR"; break;
    case GL_DEBUG_TYPE_PORTABILITY_ARB:         typeFmt = "PORTABILITY"; break;
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:         typeFmt = "PERFORMANCE"; break;
    case GL_DEBUG_TYPE_OTHER_ARB:               typeFmt = "OTHER"; break;
    }
    snprintf(typeStr, 32, typeFmt, type);

 
    char severityStr[32];
    const char *severityFmt = "UNDEFINED";
    switch(severity)
    {
    case GL_DEBUG_SEVERITY_HIGH_ARB:   severityFmt = "HIGH";   break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB: severityFmt = "MEDIUM"; break;
    case GL_DEBUG_SEVERITY_LOW_ARB:    severityFmt = "LOW"; break;
    }

    snprintf(severityStr, 32, severityFmt, severity);
 
    snprintf(outStr, outStrSize, "OpenGL: %s [source=%s type=%s severity=%s id=%d]",
        msg, sourceStr, typeStr, severityStr, id);
}
