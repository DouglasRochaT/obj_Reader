#include <glfw3.h>
#include <fstream>
#include <string>


struct screen {
	int x;
	int y;
	int wScale;
	int hScale;
};

struct Point2D {
	double x;
	double y;
};

struct Point3D {
	double x;
	double y;
	double z;
};

struct Face {
	unsigned short int vertex[3];
	unsigned short int normal;
};

struct Obj {
	Point3D* vertex;
	Point3D* normal;
	Face* face;
};

double zoom = 1;

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset) {
	zoom -= yOffset / 10;
	if (zoom < 1) {
		zoom = 1;
	}
}

void mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods) {
}

Point2D getRotationFromCursor(GLFWwindow* window, Point2D currentPos, Point2D oldPos, Point2D currentRot) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		currentRot.x += (currentPos.y - oldPos.y) / 5;
		currentRot.y += (currentPos.x - oldPos.x) / 5;
	}
	return currentRot;
}

void drawCompass(Point2D rot){
	glPushMatrix();
	glTranslated(-0.90, -0.90, 0.0);
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(rot.y, 0.0, 1.0, 0.0);
	glTranslated(0.90, 0.90, 0.0);
	glDisable(GL_LIGHT0);
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-1.0, -0.90, 0.0);
	glColor3d(0, 255, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -1.0, 0.0);
	glColor3d(0, 0, 255);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -0.90, -0.10);
	glEnd();
	glPopMatrix();
}

void drawObj(Point3D* vertex, Point3D* normals, Face* faces, Point2D rot) {
	glPushMatrix();
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(rot.y, 0.0, 1.0, 0.0);
	glColor3d(1, 1, 1);
	glEnable(GL_LIGHT0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 12; i++) {
		glNormal3d(normals[faces[i].normal].x, normals[faces[i].normal].y, normals[faces[i].normal].z);
		glVertex3d(vertex[faces[i].vertex[0]].x / zoom, vertex[faces[i].vertex[0]].y / zoom, vertex[faces[i].vertex[0]].z / zoom);
		glVertex3d(vertex[faces[i].vertex[1]].x / zoom, vertex[faces[i].vertex[1]].y / zoom, vertex[faces[i].vertex[1]].z / zoom);
		glVertex3d(vertex[faces[i].vertex[2]].x / zoom, vertex[faces[i].vertex[2]].y / zoom, vertex[faces[i].vertex[2]].z / zoom);
	}
	glEnd();
	glPopMatrix();
}

/*int getLines(std::string file, std::string type) {
	std::ifstream arq(file);
	std::string line = "";
	int cont = 0;
	if (type != " ") {
		for (int lineCont = 0; getline(arq, line); lineCont++) {
			std::string temp;
			double x, y, z;
			arq >> temp >> x >> y >> z;
			if (temp == type) {
				cont++;
			}
		}
	}
	else {
		for (int lineCont = 0; getline(arq, line); lineCont++) {
			cont++;
		}
	}
	return cont;
}

void readFile(Obj &obj) {
	std::fstream arq;
	arq.open("resources/cube.obj");
	obj.vertex = new Point3D[getLines("resources/cube.obj", "v")];
	obj.normal = new Point3D[getLines("resources/cube.obj", "vn")];
	obj.face = new Face[getLines("resources/cube.obj", "f")];
	int cont[3] = {0, 0, 0};
	std::string temp;
	std::string x, y, z;

	for (int i = 0; i < getLines("resources/cube.obj", " "); i++) {
		arq >> temp >> x >> y >> z;
		if(temp == "v"){
			obj.vertex[cont[0]] = {std::stod(x), std::stod(y), std::stod(z)};
			cont[0]++;
		}else if(temp == "vn"){
			obj.normal[cont[1]] = {std::stod(x), std::stod(y), std::stod(z)};
			cont[1]++;
		}else if(temp == "f"){
			
		}
	}
}*/

int main() {

	Point3D vertex[8] = { { -0.5, -0.5, -0.5 },
	{ -0.5, -0.5,  0.5 },
	{ -0.5,  0.5, -0.5 },
	{ -0.5,  0.5,  0.5 },
	{ 0.5, -0.5, -0.5 },
	{ 0.5, -0.5,  0.5 },
	{ 0.5,  0.5, -0.5 },
	{ 0.5,  0.5,  0.5 } };

	Point3D normals[8] = { { 0.0,  0.0,  1.0 },
	{ 0.0,  0.0, -1.0 },
	{ 0.0,  1.0,  0.0 },
	{ 0.0, -1.0,  0.0 },
	{ 1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 } };

	Face faces[12] = { { { 0, 6, 4 }, 1 },
	{ { 0, 2, 6 }, 1 },
	{ { 0, 3, 2 }, 5 },
	{ { 0, 1, 3 }, 5 },
	{ { 2, 7, 6 }, 2 },
	{ { 2, 3, 7 }, 2 },
	{ { 4, 6, 7 }, 4 },
	{ { 4, 7, 5 }, 4 },
	{ { 0, 4, 5 }, 3 },
	{ { 0, 5, 1 }, 3 },
	{ { 1, 5, 7 }, 0 },
	{ { 1, 7, 3 }, 0 } };

	Point2D mouse = { 0, 0 }, oldMouse = { 0, 0 }, rotation = {180, 180};

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "WINDOLOS", NULL, NULL);
	glfwMakeContextCurrent(window);


	//light
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glColor3d(1, 1, 1);
	GLfloat light_position[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	//input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //CHANGE TO GLFW_CURSOR_DISABLED
	glfwSetScrollCallback(window, scrollCallBack);
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);
	glfwSetCursorPos(window, 180.0, -180.0);
	

	glLineWidth(2.0);
	glClearColor(0.08, 0.08, 0.08, 255);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(window, &mouse.x, &mouse.y);
		rotation = getRotationFromCursor(window, mouse, oldMouse, rotation);
		drawObj(vertex, normals, faces, rotation);
		drawCompass(rotation);
		glfwGetCursorPos(window, &oldMouse.x, &oldMouse.y);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}