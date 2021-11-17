#include "gepch.h"
#include "Window.h"
#include "Camera.h"
#include "BaseApp.h"

namespace GE
{
	WindowProps::WindowProps(const std::string& title, uint32 width, uint32 height) :
		title(title), width(width), height(height)
	{
	}

	WindowProps::WindowProps(const WindowProps& other) :
		title(other.title), width(other.width), height(other.height)
	{
	}

	Window::Window(const WindowProps& props) :
		props(WindowProps(props))
	{
		initGLFW();
		setProps();
		initWindow(1);
		// creates hidden window
		initWindow(2);
		useWindow(window);
		initCallbacks();
		perspectiveCamera = std::shared_ptr<GE::Camera>(new PerspectiveCamera(*this));
		orthoCamera = std::shared_ptr<GE::Camera>(new Camera2D(*this));
		activeCamera = orthoCamera;
	}

	void Window::initGLFW()
	{
		// Welcome Message
		GE_INFO("Creating Window '{0}' width = {1} height = {2}", props.title, props.width, props.height);

		// initializes GLFW
		if (!GLFWInitialized)
		{
			int init = glfwInit();
			GE_ASSERT(init, "Failed to initialize GLFW");
			if (init)
			{
				GE_INFO("Initialized GLFW");
				GLFWInitialized = true;
			}
			else
				exit(1);
		}
	}

	void Window::setProps()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		props.width = mode->width;
		props.height = mode->height;
	}

	Window::~Window()
	{
		onShutdown();
	}

	void Window::useHandCursor()
	{
		glfwSetCursor(getGLFWWindow(), glfwCreateStandardCursor(GLFW_HAND_CURSOR));
	}

	void Window::useNormalCursor()
	{
		glfwSetCursor(getGLFWWindow(), glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
	}

	void Window::useWindow(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
	}

	void Window::useMainWindow()
	{
		useWindow(window);
	}

	void Window::useHiddenWindow()
	{
		useWindow(hiddenWindow);
	}

	void Window::onReset()
	{
		props = WindowProps();
		setProps();
		perspectiveCamera.reset();
		orthoCamera.reset();
		perspectiveCamera = std::shared_ptr<GE::Camera>(new PerspectiveCamera(*this));
		orthoCamera = std::shared_ptr<GE::Camera>(new Camera2D(*this));
		activeCamera = orthoCamera;
	}

	void Window::onUpdate()
	{
		useHiddenWindow();
		glfwSwapInterval(0);
		glFinish();
		glClearColor(
			WINDOW_COLOR.r / 255.f,
			WINDOW_COLOR.g / 255.f,
			WINDOW_COLOR.b / 255.f,
			1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		useMainWindow();
		glfwPollEvents();
		glfwSwapInterval(1);
		glfwSwapBuffers(window);
		glClearColor(
			WINDOW_COLOR.r / 255.f, 
			WINDOW_COLOR.g / 255.f, 
			WINDOW_COLOR.b / 255.f, 
			1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::setCamera(CamType type)
	{
		activeCamType = type;
		if (type == CamType::ORTHO)
		{
			activeCamera = orthoCamera;
			activeCamera->onWindowResize();
		}
		else
		{
			activeCamera = perspectiveCamera;
			activeCamera->onWindowResize();
		}
	}

	void Window::onShutdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool Window::isPointInWindow(int x, int y)
	{
		return x >= 0 && x < props.width&& y > 0 && y < props.height;
	}

	void Window::initWindow(int id)
	{
		// sets opengl context to window settings
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		// creates the window
		if (id == 1)
		{
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
			Window::window = glfwCreateWindow(int(props.width), int(props.height), props.title.c_str(), nullptr, nullptr);
			glfwMakeContextCurrent(Window::window);
			glfwSetWindowUserPointer(Window::window, &this->props);
		}
		else
		{
			// hidden window does not use vsync
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			Window::hiddenWindow = glfwCreateWindow(int(props.width), int(props.height), props.title.c_str(), nullptr, window);
			glfwMakeContextCurrent(Window::hiddenWindow);
			glfwSetWindowUserPointer(Window::hiddenWindow, &this->props);
		}

		glfwSetErrorCallback([](int error, const char* message)
			{
				GE_ERROR("GLFW experienced an error. Error code: {0}. Message: {1}", error, message);
			});
		initGlad();
	}

	void Window::initGlad()
	{
		//Iniializes glad
		// Load all OpenGL functions using the glfw loader function
		int gladLoaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_ASSERT(gladLoaded, "Failed to initialize OpenGL context");
		if (!gladLoaded)
		{
			GE_FATAL("Program executed due to glad initialization error");
			exit(1);
		}
		GE_INFO("Glad successfully loaded to context");
		GE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glViewport(0, 0, getWidth(), getHeight());
		glEnable(GL_MULTISAMPLE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// sets OpenGL error callback
#ifdef GE_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); //allows call stack to operate correctly on debug break
		glDebugMessageCallback(glErrorCallback, 0);
		glDebugMessageControl(GL_DEBUG_SOURCE_API,
			GL_DEBUG_TYPE_ERROR,
			GL_DEBUG_SEVERITY_MEDIUM,
			0, nullptr, GL_TRUE);
#endif
	}

	void GLAPIENTRY Window::glErrorCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		if (type != GL_DEBUG_TYPE_ERROR)
			return;
		const char* typeCstr = glGetErrorFlags(type);
		const char* severityCstr = glGetErrorFlags(severity);
		const char* sourceCstr = glGetErrorFlags(source);
		if (severity == GL_DEBUG_SEVERITY_HIGH)
		{
			GE_ERROR("GL CALLBACK: {}, source = {}\n severity = {}\n message = {}",
				typeCstr, sourceCstr, severityCstr, message);
			__debugbreak();
		}
		else
		{
			GE_WARN("GL CALLBACK: {}, source = {}\n severity = {}\n message = {}",
				typeCstr, sourceCstr, severityCstr, message);
		}
	}

	const char* Window::glGetErrorFlags(GLenum& arg)
	{
		char* output;
		switch (arg)
		{
		case GL_DEBUG_SOURCE_API:
			output = "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			output = "WINDOW SYSTEM";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			output = "SHADER COMPILER";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			output = "THIRD PARTY";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			output = "APPLICATION";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			output = "UNKNOWN";
			break;
		case GL_DEBUG_TYPE_ERROR:
			output = "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			output = "DEPRECATED BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			output = "UDEFINED BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			output = "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			output = "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_OTHER:
			output = "OTHER";
			break;
		case GL_DEBUG_TYPE_MARKER:
			output = "MARKER";
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			output = "HIGH";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			output = "MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			output = "LOW";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			output = "NOTIFICATION";
			break;
		default:
			output = "UNKNOWN";
			break;
		}
		return output;
	}

	void Window::initCallbacks()
	{
		 glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowClosedEvent* event = new WindowClosedEvent();
				Event* e = dynamic_cast<Event*>(event);
				EventTrasmitter::dispatch(*e);
				delete e;
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowResizedEvent* event = new WindowResizedEvent(width, height);
				// calls window user pointer which is a pointer to this windows windowprops
				// to reset height and width
				WindowProps& props = *reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
				props.width = width;
				props.height = height;
				Event* e = dynamic_cast<Event*>(event);
				EventTrasmitter::dispatch(*e);
				delete e;
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent* event = new KeyPressedEvent(key);
					Event* e = dynamic_cast<Event*>(event);
					EventTrasmitter::dispatch(*e);
					delete e;
					break;
				}
				case GLFW_REPEAT:
				{
					KeyHeldEvent* event = new KeyHeldEvent(key);
					Event* e = dynamic_cast<Event*>(event);
					EventTrasmitter::dispatch(*e);
					delete e;
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent* event = new KeyReleasedEvent(key);
					Event* e = dynamic_cast<Event*>(event);
					EventTrasmitter::dispatch(*e);
					delete e;
					break;
				}
				}
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				MouseMoveEvent* event = new MouseMoveEvent(xpos, ypos);
				Event* e = dynamic_cast<Event*>(event);
				EventTrasmitter::dispatch(*e);
				delete e;
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mod)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseClickedEvent* event = new MouseClickedEvent(button);
					Event* e = dynamic_cast<Event*>(event);
					EventTrasmitter::dispatch(*e);
					delete e;
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent* event = new MouseReleasedEvent(button);
					Event* e = dynamic_cast<Event*>(event);
					EventTrasmitter::dispatch(*e);
					delete e;
					break;
				}
				}

			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				MouseScrolledEvent* event = new MouseScrolledEvent(xoffset, yoffset);
				Event* e = dynamic_cast<Event*>(event);
				EventTrasmitter::dispatch(*e);
				delete e;
			});

		
		glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int notified)
			{
				if (notified)
				{
					BaseApp::getApp().getWindow().setActive(false);
				}
				else
					BaseApp::getApp().getWindow().setActive(true);
			});
	}

	bool Window::isActive()
	{
		return active;
	}

	void Window::setActive(bool is)
	{
		active = is;
	}

	uint32 Window::getWidth() const
	{
		return props.width;
	}

	uint32 Window::getHeight() const
	{
		return props.height;
	}

	void Window::onResize()
	{
		glfwGetWindowSize(window, &props.width, &props.height);
	}

	std::shared_ptr<GE::Camera> Window::getCamera()
	{
		return activeCamera;
	}
}
