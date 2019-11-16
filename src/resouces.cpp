#define EDITING_VERTEX 0
#define EDITING_TEXTURE 1
#define EDITING_NORMAL 2

#include <string>
#include <fstream>
#include <iostream>
#include "structs.h"

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

int getVertexPerFace(std::string filename, int numFace){
	std::ifstream file(filename);
	std::string id = "";
	std::string line;
	int counter = 0;
	while(id != "f"){
		file >> id;
		std::getline(file, line);
	}
	for(int i = 0; i < numFace; i++){
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
	for(int i = 0; i < obj.numFaces; i++){
		obj.face[i].vertexPerFace = getVertexPerFace(filename, i);
	}
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
				if(currentVertex == obj.face[currentFace].vertexPerFace){
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