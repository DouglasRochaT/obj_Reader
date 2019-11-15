#define EDITING_VERTEX 0
#define EDITING_TEXTURE 1
#define EDITING_NORMAL 2

#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>


struct Screen {
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
	unsigned short int numVertex;
	unsigned short int vertex[4];
	unsigned short int texture;
	unsigned short int normal;
};

struct Obj {
	int numVertex;
	int numNormals;
	int numFaces;
	unsigned short int vertexPerFace;
	Point3D* vertex;
	Point3D* normal;
	Face* face;
};

double zoom = 1;
void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset) {
	zoom -= yOffset / 10;
	if(zoom < 1) {
		zoom = 1;
	}
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
}

Point2D getRotationFromCursor(GLFWwindow* window, Point2D currentPos, Point2D oldPos, Point2D currentRot) {
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
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

int countElements(std::string filename, std::string identifier){
	std::ifstream file(filename);
	std::string id = "";
	std::string line;
	int counter = 0;
	while(id != identifier){ //its not gonna work if its out of order
		file >> id;
		std::getline(file, line);
	}
	for(int i = 0; line[i + 1] != 0; i++){
		if(line[i] == ' ' && line[i + 1] != ' '){
			counter++;
		}
	}
	file.close();
	return counter;
}

void drawObj(Obj obj, Point2D rot) {
	glPushMatrix();
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(rot.y, 0.0, 1.0, 0.0);
	glColor3d(1, 1, 1);
	glEnable(GL_LIGHT0);

	if(obj.vertexPerFace == 3){
		glBegin(GL_TRIANGLES);
	} else if (obj.vertexPerFace == 4){
		glBegin(GL_QUADS);
	} else {
		glBegin(GL_POLYGON);
	}
	for(int i = 0; i < obj.numFaces; i++) {
		if(obj.numNormals > 0){
			glNormal3d(obj.normal[obj.face[i].normal].x, obj.normal[obj.face[i].normal].y, obj.normal[obj.face[i].normal].z);
		}
		glVertex3d(obj.vertex[obj.face[i].vertex[0]].x / zoom, obj.vertex[obj.face[i].vertex[0]].y / zoom, obj.vertex[obj.face[i].vertex[0]].z / zoom);
		glVertex3d(obj.vertex[obj.face[i].vertex[1]].x / zoom, obj.vertex[obj.face[i].vertex[1]].y / zoom, obj.vertex[obj.face[i].vertex[1]].z / zoom);
		glVertex3d(obj.vertex[obj.face[i].vertex[2]].x / zoom, obj.vertex[obj.face[i].vertex[2]].y / zoom, obj.vertex[obj.face[i].vertex[2]].z / zoom);
		if(obj.vertexPerFace == 4){
			glVertex3d(obj.vertex[obj.face[i].vertex[3]].x / zoom, obj.vertex[obj.face[i].vertex[3]].y / zoom, obj.vertex[obj.face[i].vertex[3]].z / zoom);
		}
	}
	glEnd();
	glPopMatrix();
}

int countLines(std::string filename, std::string identifier){
	std::ifstream file(filename);
	std::string id;
	int counter = 0;
	while(file >> id){
		if(id == identifier){
			counter++;
		}
	}
	file.close();
	return counter;
}

void getVertexElements(std::string filename, Point3D* array, std::string identifier){
	int numElements = countElements(filename, identifier);
	std::string id, x, y, z, w;
	int current = 0;
	std::ifstream file(filename);
	while(file >> id){
		if(id == identifier){
			if(numElements == 3){
				file >> x >> y >> z;
			} else if(numElements == 4){
				file >> x >> y >> z >> w;
			}
			array[current].x = stod(x);
			array[current].y = stod(y);
			array[current].z = stod(z);
			current++;
		}
	}
	file.close();
}

void getFaceElements(std::string filename, Obj &obj){
	obj.vertexPerFace = countElements(filename, "f");
	std::ifstream file(filename);
	std::string line;
	std::string id = "";
	int currentVertex = -1;
	int currentFace = 0;
	std::string temp;
	while(file >> id){
		std::getline(file, line);
		int editing = EDITING_NORMAL;
		//face identifier
		if(id == "f"){
			for(int i = 1; line[i] != 0; i++){
			//currentFace incrementer and currentVertex resetter
			if(currentVertex == obj.vertexPerFace){
				currentFace++;
				currentVertex = 0;
			}
				//element identifier
				if(editing == EDITING_NORMAL && line[i - 1] == ' ' && line[i] != ' '){
					editing = EDITING_VERTEX;
					currentVertex++;
				} else if(editing == EDITING_VERTEX && line[i - 1] == '/'){
					editing = EDITING_TEXTURE;
				} else if(editing == EDITING_TEXTURE && line[i - 1] == '/'){
					editing = EDITING_NORMAL;
				}
				//element "builder" (if isn't '/' or ' ')
				if(!(line[i] == '/' || line[i] == ' ')){
					temp += line[i];
				//element applier (if is '/' or ' ' and has something in temp)
				} else if(temp != ""){
					if(editing == EDITING_VERTEX){
						obj.face[currentFace].vertex[currentVertex] = stod(temp) - 1;
					} else if(editing == EDITING_TEXTURE){
						obj.face[currentFace].texture = stod(temp) - 1;
					} else if(editing == EDITING_NORMAL){
						obj.face[currentFace].normal = stod(temp) - 1;
					}
					temp = "";
				}
			}
		}
	}
}

int main() {

	std::string filename = "resources/hexa.obj";

	Obj object;

	object.numVertex = countLines(filename, "v");
	object.numNormals = countLines(filename, "vn");
	object.numFaces = countLines(filename, "f");

	object.vertex = new Point3D[object.numVertex];
	if(object.numNormals > 0){
		object.normal = new Point3D[object.numNormals];
	}
	object.face = new Face[object.numFaces];

	std::cout << "Loading vertexes...\n";
	getVertexElements(filename, object.vertex, "v");
	std::cout << "Loading normals...\n";
	getVertexElements(filename, object.normal, "vn");
	std::cout << "Loading faces...\n";
	getFaceElements(filename, object);
	Point2D mouse = { 0, 0 }, oldMouse = { 0, 0 }, rotation = { 180, 180 };

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
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(window, &mouse.x, &mouse.y);
		rotation = getRotationFromCursor(window, mouse, oldMouse, rotation);
		drawObj(object, rotation);
		drawCompass(rotation);
		glfwGetCursorPos(window, &oldMouse.x, &oldMouse.y);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}