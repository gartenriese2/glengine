glengine
========

OpenGL engine


See http://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project

USAGE:

	create Engine:

		Engine e;

	create one or more Windows:

		WindowID w = e.createWindow(width, height);

	create a Camera for each Window:

		CameraID cam = w.createCamera(position, direction, up);

	create one or more Renderings:

		RenderID basic = w.createBasicRendering(cam);
		RenderID normal = w.createNormalRendering(cam);


