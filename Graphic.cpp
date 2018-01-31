 #include "Graphic.h"
int Graphic::ReleaseTexture(Texture* tex) {
	if (tex == NULL) {
		return -1;
	}
	free(tex->data);
	return NOERROR;
}
int Graphic::SetTextureObject(Object* obj, Texture* tex) {
	if (tex == NULL||obj == NULL) {
		return -1;
	}
	obj->texture = tex;
	return 0;
}
int Graphic::ReadShapeObject(Object *obj,const char path[]) {
	  ZeroMemory(obj, sizeof(Object));
	  fopen_s(&file,path, "rb");
	  if (file == NULL) {
		  return ERROR_FILE_NOT_FOUND;
	  }
	  for (int letter=0, i = 0,v =0;letter!= EOF;) {
		  letter = fgetc(file);
		  if (letter == '#') { for (; fgetc(file) != '\n';) {} }
		  if (letter == 'u') {
			  
			  if (i > 0) { obj->mat.push_back(mtl); }
			  ZeroMemory(&mtl, sizeof(Material));
			  fscanf_s(file, "semtl %s\n", mtl.name, 25);
			  i++;
		  }

		  if (letter == 'v') {
			  if ((letter = fgetc(file)) == EOF) { break; }
			  if (letter == ' ') {
				  //VERTICES
				  if (fscanf_s(file, "%f %f %f", &x, &y, &z) < 3) { return -1; }
				  obj->vertices.push_back(x);
				  obj->vertices.push_back(y);
				  obj->vertices.push_back(z);
				 
				  mtl.until++;
			  }
			  if (letter == 't') {
				  //TEX COORD
				  if (fscanf_s(file, " %f %f", &x, &y) < 2) { return -1; }
				  obj->texcoord.push_back(x);
				  obj->texcoord.push_back(y);
				   
			  }
			  if (letter == 'n') {
				  //NORMAL VERTICES
				  if (fscanf_s(file, " %f %f %f", &x, &y, &z) < 3) { return -1; }
				  obj->normals.push_back(x);
				  obj->normals.push_back(y);
				  obj->normals.push_back(z);
				  v += 3;
				 
					
			  }
			  continue;
		  }
		  if (letter == 'f') {
				  //INDICES
				  for (;fgetc(file)==' ';) {
					  if (fscanf_s(file, "%f//%*d", &x) < 1) { return -1; }
					  x -= 1.0f;			
					  obj->indices.push_back((int)x);					  
		 
				  }
				  
			  
		  }
	  }
	  if (mtl.until == obj->vertices.size()/ 3) {
		  obj->mat.push_back(mtl);
	  }
	  
	  fclose(file);
	  return NO_ERROR;

}
int Graphic::ReadMaterialObject(Object* obj,const char path[]) {
	if (obj == NULL) { return -1; }
	fopen_s(&file, path,"rb");
	if (file == NULL) { return ERROR_FILE_NOT_FOUND; }
	for (char letter =0;letter != EOF;) {
		letter = fgetc(file);
		if (letter == '#') {
			for (;fgetc(file)!='\n';){}
			continue;
		}
		if (letter == 'n') { 
			fscanf_s(file, "ewmtl %s\nK", mtl.name,25);
			for (unsigned int i=0;i<obj->mat.size(); i++) {
				if (strcmp(obj->mat.at(i).name, mtl.name) == 0) {
					letter = fgetc(file);
					switch (letter) {
					case 'a':
						fscanf_s(file, " %f %f %f", &obj->mat.at(i).Ka[0], &obj->mat.at(i).Ka[1], &obj->mat.at(i).Ka[2]);
						break;
					case 's':
						fscanf_s(file, " %f %f %f", &obj->mat.at(i).Ks[0], &obj->mat.at(i).Ks[1], &obj->mat.at(i).Ks[2]);
						break;
					case 'd':
						fscanf_s(file, " %f %f %f", &obj->mat.at(i).Kd[0], &obj->mat.at(i).Kd[1], &obj->mat.at(i).Kd[2]);
						break;

					}
				}
			}
		}

	}

	fclose(file);
	return NO_ERROR;
}
int Graphic::ReadTextureFile(Texture *tex, const char path[]){
	if (tex == NULL) {
		return -1;
	}
	fopen_s(&file, path, "rb");
	if (file == NULL) {
		return ERROR_FILE_NOT_FOUND;
	}
	ZeroMemory(&bmp, sizeof(InfoBitmap));
	fseek(file, 0, SEEK_END);
	tex->sizeData = ftell(file) - sizeof(InfoBitmap);
	rewind(file);
	fread(&bmp, sizeof(InfoBitmap), 1, file);
	tex->data = (char*)malloc(sizeof(char)*tex->sizeData);
	fread(tex->data, sizeof(char), tex->sizeData, file);
	memcpy(&tex->width,  bmp.widthBMP , strlen(bmp.widthBMP));
	memcpy(&tex->height, bmp.heightBMP, strlen(bmp.heightBMP));
	fclose(file);
 
	return NO_ERROR;
}
int Graphic::DrawObject(Object *obj, int opt) {
	
	if (obj == NULL) { return -1; }
	glBegin(GL_TRIANGLES);
 
	 
	glEnd();
	 
	return 0;

}