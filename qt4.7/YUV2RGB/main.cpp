#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define _MAX_PATH 260
#define _CURRENT_PATH "./"

unsigned long wSize;
unsigned char *pYUV, *pRGB, *pRGB_line;
int hFile;
char rdata_fname[_MAX_PATH + 1];
char wdata_fname[_MAX_PATH + 1];
unsigned i, k;
int o_num;
int yuv_size = 0;
int yuv_hsize = 0;
int yuv_vsize = 0;
int rgb_size, rgb_1Lsize;

unsigned char BMP_H[] = { 0x42, 0x4D, 0x76, 0x70, 0x31, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
                          0x00, 0x00, 0x84, 0x03, 0x00, 0x00, 0xB0, 0x04,
                          0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x40, 0x70, 0x31, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    memset(rdata_fname, '\0', _MAX_PATH + 1);
    (void)strncpy(rdata_fname,_CURRENT_PATH,
                  sizeof(_CURRENT_PATH));

    k = strlen(rdata_fname);
    o_num = 0;

    for(i = k - 1; 0 < i; i--) {
        if(rdata_fname[i] == '\\') {
            o_num = i + 1;
            break;
        }
    }

    memset(&rdata_fname[o_num], 0x00,
           _MAX_PATH + 1 - o_num);
    (void)strncpy(wdata_fname, rdata_fname,
                  strlen(rdata_fname));
    (void)strcat(rdata_fname, "RECVDATA_02.DAT\0");
    (void)strcat(wdata_fname, "CONV.BMP\0");

    hFile = open(rdata_fname, O_RDONLY , 0666);
    // check if file exists
    if(hFile == -1) {
        perror("ERRORN");
        (void)close(hFile);
        return 0;
    }

    // file size
    (void)lseek(hFile, 0L, SEEK_END);
    yuv_size = lseek(hFile, 0L, SEEK_CUR);
    (void)lseek(hFile, 0L, SEEK_SET);
    fprintf(stdout, "yuv_size: %u\n", yuv_size);

    pYUV = new unsigned char[yuv_size];
    unsigned long rBytes = read(hFile, pYUV, yuv_size);
    fprintf(stdout, "rBytes: %u\n", rBytes);

    if(rBytes <= 12) {
        // error ...
        return 0;
    }

    (void)close(hFile);

    yuv_hsize = *((unsigned short *)(pYUV + 10));
    yuv_vsize = *((unsigned short *)(pYUV + 12));
    fprintf(stdout, "yuv_hsize: %d\n", yuv_hsize);
    fprintf(stdout, "yuv_vsize: %d\n", yuv_vsize);

    rgb_1Lsize = ((yuv_hsize * 3 + 3) / 4) * 4;
    rgb_size = rgb_1Lsize * yuv_vsize;
    fprintf(stdout, "rgb_size: %d\n", rgb_size);
    fprintf(stdout, "rgb_1Lsize: %d\n", rgb_1Lsize);

    pRGB = new unsigned char[rgb_size];
    fprintf(stdout, "rgb_1Lsize * (yuv_vsize - 1): %d\n", rgb_1Lsize * (yuv_vsize - 1));
    pRGB_line = pRGB + rgb_1Lsize * (yuv_vsize - 1);

    k = 0;

    unsigned long tmp = (*((unsigned long *)(pYUV + 6)) / 4);
    fprintf(stdout, "tmp: %u\n", tmp);

    for (i = 0; i < (*((unsigned int *)(pYUV + 6)) / 4); i++) {
        // U  : inDdata[4*i+0]-128
        // Y0 : inDdata[4*i+1]
        // V  : inDdata[4*i+2]-128
        // Y1 : inDdata[4*i+3]
        // B = 1.000Y + 1.772U
        // G = 1.000Y - 0.344U - 0.714V
        // R = 1.000Y		  + 1.402V

        double y0 = (double)(*(pYUV + 4 * i + 1 + 15));
        double y1 = (double)(*(pYUV + 4 * i + 3 + 15));
        double u  = (double)(*(pYUV + 4 * i + 0 + 15)) - 128.0;
        double v  = (double)(*(pYUV + 4 * i + 2 + 15)) - 128.0;

        //B = 1.000Y + 1.772U
        double RGB = (y0 + 1.722 * u);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        //fprintf(stdout, "k: %u\n", k);
        //fprintf(stdout, "RGB: %d\n", RGB);
        *(pRGB_line + 6 * k + 0) = (unsigned char)(RGB);  //B

        //G = 1.000Y - 0.344U - 0.714V
        RGB = (y0 - 0.344 * u - 0.714 * v);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        *(pRGB_line + 6 * k + 1) = (unsigned char)(RGB); //G


        //R = 1.000Y		  + 1.402V
        RGB = (y0 + 1.402 * v);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        *(pRGB_line + 6 * k + 2) = (unsigned char)(RGB); //R


        //B = 1.000Y + 1.772U
        RGB = (y1 + 1.722 * u);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        *(pRGB_line + 6 * k + 3) = (unsigned char)RGB;  //B


        //G = 1.000Y - 0.344U - 0.714V
        RGB = (y1 - 0.344 * u - 0.714 * v);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        *(pRGB_line + 6 * k + 4) = (unsigned char)(RGB); //G


        //R = 1.000Y		  + 1.402V
        RGB = (y1 + 1.402 * v);
        if (RGB < 0) {
            RGB = 0;
        }
        if (RGB > 255) {
            RGB = 255;
        }
        *(pRGB_line + 6 * k + 5) = (unsigned char)(RGB); //R


        k++;
        if ((i + 1) % (yuv_hsize / 2) == 0) {
            pRGB_line = pRGB_line - rgb_1Lsize;
            k = 0;
        }
    }

    // check and unlink the exist file
    hFile = open(wdata_fname, O_RDONLY, 0666);
    if(hFile != -1) {
        // file exist
        (void)unlink(wdata_fname);
        (void)close(hFile);
    }

    hFile = open(wdata_fname, O_APPEND | O_WRONLY | O_CREAT, 0666);
    if(-1 == hFile) {
        perror("ERRORN");
        (void)close(hFile);
        return 0;
    }

    *(unsigned short *)(&BMP_H[18]) = yuv_hsize;
    *(unsigned short *)(&BMP_H[22]) = yuv_vsize;
    (void)write(hFile, BMP_H, 54);

    // Debug
    //(void)lseek(hFile, 0L, SEEK_END);
    //int size = lseek(hFile, 0L, SEEK_CUR);
    //fprintf(stdout, "size: %d\n", size);

    fprintf(stdout, "rgb_size: %d\n", rgb_size);
    (void)write(hFile, pRGB, rgb_size);
    (void)close(hFile);

    delete[] pYUV;
    delete[] pRGB;

    return a.exec();
}
