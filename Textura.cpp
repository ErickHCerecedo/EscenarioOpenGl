#include "Textura.h"

Textura::Textura()
{
  
}

Textura::~Textura()
{
  //dtor
}

bool Textura::readImage()
{
  	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0), *dib_copy(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	int i=0;
	while(i < NTextures){
        //check the file signature and deduce its format
        fif = FreeImage_GetFileType(texturefiles[i], 0);
        //if still unknown, try to guess the file format from the file extension
        if(fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(texturefiles[i]);
        //if still unkown, return failure
        if(fif == FIF_UNKNOWN){
                printf("exit 0\n");
            return false;
        }
        //check that the plugin has reading capabilities and load the file
        if(FreeImage_FIFSupportsReading(fif)){
                printf("reading image...\n");
            dib = FreeImage_Load(fif, texturefiles[i], BMP_DEFAULT);
        }
        //if the image failed to load, return failure
        if(!dib){
                printf("exit 1\n");
            return false;
        }
        //conversion to 24 bit deep color
        dib_copy = FreeImage_ConvertTo32Bits(dib);
        FreeImage_Unload(dib);
        dib = dib_copy;

        //TEXTURE GENERATION

        //retrieve the image data
        bits = FreeImage_GetBits(dib);
        //get the image width and height
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);
        //if this somehow one of these failed (they shouldn't), return failure
        if((bits == 0) || (width == 0) || (height == 0))
            return false;

        //generate an OpenGL texture ID for this texture
        glGenTextures(1, &texture[i]);
        //bind to the new texture ID
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        //store the texture data for OpenGL use
        // ** AGREGADO ** (filtros para la textura y condicional de mipmap) //
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
                     GL_BGRA, GL_UNSIGNED_BYTE, bits);

        //Free FreeImage's copy of the data
        FreeImage_Unload(dib);
        i++;
	}

	//return success
	return true;
}
