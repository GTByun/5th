#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

typedef struct tagBITMAPHEADER {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
}BITMAPHEADER;

class Image
{
public:
    BYTE* image;
    LONG width, height;
	Image (const char* filename)
    {
        BITMAPHEADER header;
        FILE* fp;
        if (fopen_s(&fp, filename, "rb") != 0)
            exit(EXIT_FAILURE);
        fread_s(&header.bf, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, fp);
        fread_s(&header.bi, sizeof(BITMAPINFOHEADER), sizeof(BITMAPINFOHEADER), 1, fp);
        
        width = header.bi.biWidth;
        height = header.bi.biHeight;
        int imageSize = width * height;
        image = (BYTE*)malloc(sizeof(BYTE) * imageSize * 4);
        if (image == 0)
            exit(EXIT_FAILURE);
        fread_s(image, sizeof(BYTE) * imageSize * 4, sizeof(BYTE), imageSize * 4, fp);
        fclose(fp);
        if (image == NULL)
            exit(EXIT_FAILURE);
        BYTE temp = 0;
        
        for (size_t i = 0; i < imageSize; i++)
        {
            temp = image[i * 3];
            image[i * 3] = image[i * 3 + 2];
            image[i * 3 + 2] = temp;
        }
    }
	~Image()
    {
        free(image);
    }
};

