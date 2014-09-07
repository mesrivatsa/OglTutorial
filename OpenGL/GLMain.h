#ifndef GLINITIALIZE_H
#define GLINITIALIZE_H

class GLApplication
{
public:
	GLApplication();
	virtual void RenderScene() = 0;
	virtual void HandleInput(unsigned char key, int x, int y) = 0;
	virtual bool Running() const = 0;
};

class GLMain
{
protected:
	static GLApplication * current_context;
	static bool initialized_glut;

	static void CheckDeviceCaps();
	static void RenderCallback();
	static void InputCallback(unsigned char key, int x, int y);

public:
	static void Run(GLApplication &p);
	static void InitializeGLUT();
	static bool Initialized();
};

#endif