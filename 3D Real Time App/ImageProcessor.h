#include <iostream>
#include "freeglut.h"

#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              
	GLbyte	colorMapType;           
	GLbyte	imageType;              
	unsigned short	colorMapStart;  
	unsigned short	colorMapLength; 
	unsigned char 	colorMapBits;   
	unsigned short	xstart;         
	unsigned short	ystart;         
	unsigned short	width;          
	unsigned short	height;         
	GLbyte	bits;                   
	GLbyte	descriptor;             
} TGAHEADER;
#pragma pack(8)


GLbyte *gltLoadTGA(const char *szFileName, GLint *pointerW, GLint *pointerH, GLint *pointerComponent, GLenum *pointerFormat)
{
	FILE *pFile;			
	TGAHEADER tgaHeader;	
	unsigned long lImageSize;
	short sDepth;			
	GLbyte	*pBits = NULL;  

							
	*pointerW = 0;
	*pointerH = 0;
	*pointerFormat = GL_BGR_EXT;
	*pointerComponent = GL_RGB8;

	fopen_s(&pFile, szFileName, "rb");

	if (pFile == NULL)
		return NULL;

	fread(&tgaHeader, 18, 1, pFile);

#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif

	*pointerW = tgaHeader.width;
	*pointerH = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	switch (sDepth)
	{
	case 3:     
		*pointerFormat = GL_BGR_EXT;
		*pointerComponent = GL_RGB8;
		break;
	case 4:
		*pointerFormat = GL_BGRA_EXT;
		*pointerComponent = GL_RGBA8;
		break;
	case 1:
		*pointerFormat = GL_LUMINANCE;
		*pointerComponent = GL_LUMINANCE8;
		break;
	};


	fclose(pFile);
	return pBits;
}