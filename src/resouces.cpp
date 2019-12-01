#define EDITING_VERTEX 0
#define EDITING_TEXTURE 1
#define EDITING_NORMAL 2

#include <string>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "structs.h"
#include "text.h"
#include <Windows.h>

void hideConsole(){
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
	//For MinGW this function can be supressed by the -mwindows linker option.
}

std::string getFileName(){
	char fileName[MAX_PATH];
	fileName[259] = NULL;
	OPENFILENAME winFile;
	ZeroMemory(&fileName, sizeof(fileName));
	ZeroMemory(&winFile, sizeof(winFile));
	winFile.lStructSize = sizeof(winFile);
	winFile.hwndOwner = NULL;
	winFile.lpstrFilter = "OBJ Files\0*.obj\0Any File\0*.*\0";
	winFile.lpstrFile = fileName;
	winFile.nMaxFile = MAX_PATH;
	winFile.lpstrTitle = "Select an obj file";
	winFile.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	GetOpenFileNameA(&winFile);
	return std::string(winFile.lpstrFile);
}

void countLines(std::string filename, Obj &obj){
	obj.numFaces = 0; obj.numVertex = 0; obj.numNormals = 0; obj.numTextures = 0;
	std::ifstream file(filename);
	if(!file.is_open()){return;}
	std::string id;
	while(file >> id){
		if(id == "v"){
			obj.numVertex += 1;
		}else if(id == "vn"){
			obj.numNormals += 1;
		}else if(id == "f"){
			obj.numFaces += 1;
		}else if(id == "vt"){
			obj.numTextures += 1;
		}
	}
	file.close();
}

int countElements(std::string filename, std::string identifier){
	std::ifstream file(filename);
	std::string id = "", line;
	int counter = 0;
	while(id != identifier){
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

void getVertexPerFace(std::string filename, Obj &obj){
	std::ifstream file(filename);
	std::string id = "";
	std::string line;
	int currentFace = 0;
	while(file >> id){
		std::getline(file, line);
		if(id == "f"){
			int counter = 0;
			for(int i = 0; line[i + 1] != 0; i++){
				if(line[i] == ' ' && line[i + 1] != ' '){
					counter++;
				}
			}
			obj.face[currentFace].vertexPerFace = counter;
			obj.face[currentFace].vertex = new unsigned short int[counter];
			obj.face[currentFace].texture = new unsigned short int[counter];
			obj.face[currentFace].normal = new unsigned short int[counter];
			currentFace++;
		}
	}
	file.close();
}

void getVertexElements(std::string filename, Obj &obj, std::string identifier){
	if (obj.numNormals == 0 && identifier == "vn") return;
	int numElements = countElements(filename, identifier);
	double maxX = -10000, minX = 10000;
	double maxY = -10000, minY = 10000;
	double maxZ = -10000, minZ = 10000;
	std::string id, x, y, z, w;
	int current = 0;
	std::ifstream file(filename);
	while(file >> id){
		if(id == identifier){
			if(numElements == 2){
				file >> x >> y;
			} else if(numElements == 3){
				file >> x >> y >> z;
			} else if(numElements == 4){
				file >> x >> y >> z >> w;
			}
			if(identifier == "v"){
				//---x---//
				obj.vertex[current].x = stod(x);
				if(stod(x) > maxX){maxX = stod(x);}
				if(stod(x) < minX){minX = stod(x);}
				//---y---//
				obj.vertex[current].y = stod(y);
				if(stod(y) > maxY){maxY = stod(y);}
				if(stod(y) < minY){minY = stod(y);}
				//---z---//
				obj.vertex[current].z = stod(z);
				if(stod(z) > maxZ){maxZ = stod(z);}
				if(stod(z) < minZ){minZ = stod(z);}
			} else if(identifier == "vn"){
				obj.normal[current].x = stod(x);
				obj.normal[current].y = stod(y);
				obj.normal[current].z = stod(z);
			} else if(identifier == "vt"){
				obj.texture[current].x = stod(x);
				obj.texture[current].y = stod(y);
				//std::cout << current << std::endl;
				//std::cout << "X: " << x << std::endl;
				//std::cout << "Y: " << y << std::endl;
			}
			current++;
		}
	}
	if(identifier == "v"){
		obj.offset.x = minX + ((maxX - minX) / 2);
		obj.offset.y = minY + ((maxY - minY) / 2);
		obj.offset.z = minZ + ((maxZ - minZ) / 2);
		obj.size.x = maxX - minX;
		obj.size.y = maxY - minY;
		obj.size.z = maxZ - minZ;
	}
	file.close();
}

void getFaceElements(std::string filename, Obj &obj){
	std::ifstream file(filename);
	std::string line, id = "", temp;
	int currentVertex = -1, currentFace = 0, numVertexPassed = 0, numNormalsPassed = 0;
	while(file >> id){
		std::getline(file, line);
		int editing = EDITING_NORMAL;
		if(id == "v"){numVertexPassed++;}
		if(id == "vn"){numNormalsPassed++;}
		//face identifier
		if(id == "f"){
			for(int i = 1; line[i] != 0; i++){
			//currentFace incrementer and currentVertex resetter
				if(currentVertex == obj.face[currentFace].vertexPerFace){
					currentFace++;
					currentVertex = 0;
				}
				//element identifier
				if(line[i - 1] == ' ' && line[i] != ' '){
					editing = EDITING_VERTEX;
					temp = "";
					currentVertex++;
				} else if(editing == EDITING_VERTEX && line[i - 1] == '/'){
					editing = EDITING_TEXTURE;
					temp = "";
				} else if(editing == EDITING_TEXTURE && line[i - 1] == '/'){
					editing = EDITING_NORMAL;
					temp = "";
				}
				//element "builder" (if isn't '/' or ' ')
				if(!(line[i] == '/' || line[i] == ' ')){
					temp += line[i];
				//element applier (if is '/' or ' ' and has something in temp)
				} else if(temp != ""){
					if(editing == EDITING_VERTEX){
						obj.face[currentFace].vertex[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : numVertexPassed - abs(stoi(temp));
					} else if(editing == EDITING_TEXTURE){
						obj.face[currentFace].texture[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : obj.numVertex - abs(stoi(temp));
						//std::cout << obj.face[currentFace].texture[currentVertex] << std::endl;
					} else if(editing == EDITING_NORMAL){
						obj.face[currentFace].normal[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : numNormalsPassed - abs(stoi(temp));
					}
				}
			}
			//---last normal from current line---//
			obj.face[currentFace].normal[currentVertex] = (stoi(temp) > 0) ? abs(stoi(temp)) - 1 : numNormalsPassed - abs(stoi(temp));
		}
	}
}

int countMtlTextures(std::string filename){
	std::ifstream file(filename);
	std::string id = "", line;
	int count = 0;
	while(file >> id){
		if(id == "newmtl"){
			count++;
		}
	}
	return count;
}

void getTgaNames(std::string filename, Obj& obj){
	filename[filename.size() -3] = 'm';
	filename[filename.size() -2] = 't';
	filename[filename.size() -1] = 'l';
	obj.mtl = new Mtl[countMtlTextures(filename)];
	std::ifstream file(filename);
	std::string id = "", line;
	int mtlAtual = 0;
	while(file >> id){
		std::getline(file, line);
		if(id != ""){
			if(id == "newmtl"){
				obj.mtl[mtlAtual].name = line;
			} else{
				obj.mtl[mtlAtual].fileName = line;
				mtlAtual++;
			}
		}
	}
}


void loadObj(Obj& obj, std::string filename, SDL_Renderer* renderer, SDL_Texture* font){
	getTgaNames(filename, obj);
	countLines(filename, obj);
	if(!obj.numVertex){return;}
	obj.vertex = new Point3D[obj.numVertex];
	obj.normal = new Point3D[obj.numNormals];
	obj.face = new Face[obj.numFaces];
	obj.texture = new Point2D[obj.numTextures];
	std::string vertexText = "Loaded " + std::to_string(obj.numVertex) + " vertex!";
	std::string normalText = "Loaded " + std::to_string(obj.numNormals) + " normals!";
	std::string facesText = "Loaded " + std::to_string(obj.numFaces) + " faces!";
	std::string textureText = "Loaded " + std::to_string(obj.numTextures) + " textures!";
	writeLoadingText(renderer, "Loading vertexes...", font, 5, 10, 11, 17);
	getVertexElements(filename, obj, "v");
	writeLoadingText(renderer, vertexText, font, 5, 30, 11, 17);
	writeLoadingText(renderer, "Loading normals...", font, 5, 50, 11, 17);
	getVertexElements(filename, obj, "vn");
	writeLoadingText(renderer, normalText, font, 5, 70, 11, 17);
	writeLoadingText(renderer, "Loading faces...", font, 5, 90, 11, 17);
	getVertexPerFace(filename, obj);
	getFaceElements(filename, obj);
	writeLoadingText(renderer, facesText, font, 5, 110, 11, 17);
	writeLoadingText(renderer, "Loading textures...", font, 5, 130, 11, 17);
	getVertexElements(filename, obj, "vt");
	writeLoadingText(renderer, textureText, font, 5, 150, 11, 17);
	//SDL_Delay(3000); //This is annoying for debug
}