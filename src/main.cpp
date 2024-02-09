#include "GLFramework.h"

const int width = 800;
const int height = 600;

int main()
{
	GLFramework::GLApp app;
	app.setWindowX(width);
	app.setWindowY(height);
	app.Run();
	
	return 0;
}
