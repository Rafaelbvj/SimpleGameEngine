#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#define  TEXTURE  1
#define  NORMAL	  2
#define  MATERIAL 4


using namespace std;
typedef struct infobmp {
	char id[2];
	char blockIn32[4];
	char Reserved[4];
	char offsetToData[4];
	char HeadSize[4];
	char widthBMP[4];
	char heightBMP[4];
	char numberPlanes[2];
	char numberBitsPerPixel[2];
	char compression[4];
	char sizeImage[4];
	char xPixel[4];
	char yPixel[4];
	char ColorsUsed[4];
	char ColorsImportant[4];
}InfoBitmap;
typedef struct material{
	float Ka[3]; //Ambient
	float Kd[3]; //Diffuse
	float Ks[3]; //Specular
	int until;
	char  name[25];
}Material;
typedef struct texture {
	int width;
	int height;
	void *data;
	int sizeData;
	GLuint gen;
}Texture;
typedef struct object {
	vector <float> vertices,texcoord,normals;
	vector <int>  indices;
	Texture *texture;
	vector<Material> mat;
} Object;
class Graphic {
private:
	FILE *file;
	float x, y, z;
	InfoBitmap bmp;
	Material mtl;
public:
	int ReadShapeObject(Object* , const char[]);   //Only OBJ files
	int ReadMaterialObject(Object*, const char[]); //Only MTL files
	int ReadTextureFile(Texture *, const char[]);  //Only BITMAP FILES
	int SetTextureObject(Object*, Texture*);	   //Attach a texture to an object
	int ReleaseTexture(Texture*);				   //Release memory from a loaded texture
	int DrawObject(Object*, int );					
};

