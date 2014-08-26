//Includes all opengl headers too.
#include <GLFW/glfw3.h>

//Includes all cout functions, i.e. std::cout.
#include <iostream>

//Glfw error function, all errors will be notified by this function.
void error_callback(int error, const char* description) {
    std::cout << "Error code: " << error  << " - " << description << std::endl;
}

//Glfw keyboard function, all keyboard inputs will be notified by this function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << "key= " << key << " action= " << action << " mods= " << mods << std::endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

//Glfw frame buffer function, after resize a window the framework will notify by this function
void framebuffer_callback(GLFWwindow* window, int width, int height) {
	std::cout << "resize width= " << width << " height= " << height << std::endl;
	const float ratio = static_cast<float>(width) / static_cast<float>(height);
	glViewport(0, 0, width, height);

	//Resets the projection matrix
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Sets the projection matrix to be orthogonal
    glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

    //Back to model view matrix
    glMatrixMode(GL_MODELVIEW);
}

void render() {
	//Clear the screen buffers
	glClear(GL_COLOR_BUFFER_BIT);

	//Resets the model view matrix
	glLoadIdentity();

	//Draws the triangle
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void initializeOpengl() {
	//Says to opengl to interpolate the colors between vertices
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
	const int width = 800;
	const int height = 600;

	//Installs a callback function for glfw errors, if any error occurs the function will be called.
	glfwSetErrorCallback(error_callback);

	//Initializes the glfw framework, this function must be called.
	if (!glfwInit()) {
	    std::cout << "Error glfwInit" << std::endl;
		return 1;
	}

	//Creates a window with the opengl context
	GLFWwindow* window = glfwCreateWindow(width, height, "glfw tutorial 02", NULL, NULL);
	if (!window) {
	    std::cout << "Error glfwCreateWindow" << std::endl;
	    glfwTerminate();
	    return 1;
	}
	//Sets this window as the current render context, after call this function the opengl functions will be enabled.
	glfwMakeContextCurrent(window);

	//Sets the callback function for the keyboard
	glfwSetKeyCallback(window, key_callback);

	//Sets the callback function for the frame buffer resize
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	//Forces the initialization of the frame buffer
	framebuffer_callback(window, width, height);

	//Initializes all opengl stuff
	initializeOpengl();

	//Main loop, checks if the window still alive
	while (!glfwWindowShouldClose(window)) {
        //Process all the events, inputs, window resize, etc.
		glfwPollEvents();

		//Render the scene
		render();

		//Sends the back buffer to render.
        glfwSwapBuffers(window);
	}

	//Frees resources associates with the window.
	glfwDestroyWindow(window);

	//Frees all resources used by glfw framework.
	glfwTerminate();

	//Everything ended ok.
	return 0;
}
