#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    unsigned char r, g, b;
} pixel;

typedef struct {
    int width, height;
    pixel *data;
} image;

image *readPPM(const char *filename)
{
    FILE *fp = fopen(filename, "rb");

    if (!fp)
    {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    int width, height, max;
    char buf[16];

    fgets(buf, sizeof(buf), fp);
    if (buf[0] != 'P' || buf[1] != '6')
    {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }

    fscanf(fp, "%d %d %d", &width, &height, &max);

    if (max != 255)
    {
        fprintf(stderr, "Invalid image max value (must be 255)\n");
        exit(1);
    }

    if (fgetc(fp) != '\n')
    {
        fprintf(stderr, "Expected newline\n");
        exit(1);
    }

    image *img = malloc(sizeof(image));
    assert(img);
    img->width = width;
    img->height = height;
    img->data = malloc(width * height * sizeof(pixel));

    fread(img->data, 3, width * height, fp);
    fclose(fp);
    return img;
}

void writePPM(const char *filename, const image *img)
{
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "%d\n", 255);
    fwrite(img->data, 3, img->width * img->height, fp);
    fclose(fp);
}

image *createImage(int width, int height)
{
    image *temp = malloc(sizeof(image));
    temp->width = width;
    temp->height = height;
    temp->data = malloc(width * height * sizeof(pixel));
    memset(temp->data, 0, width * height * sizeof(pixel));
    return temp;
}

void putRpixel(image *img, int x, int y, unsigned char r)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    img->data[x + y * img->width].r = r;
}

void putGpixel(image *img, int x, int y, unsigned char g)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    img->data[x + y * img->width].g = g;
}

void putBpixel(image *img, int x, int y, unsigned char b)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    img->data[x + y * img->width].b = b;
}

unsigned char getRpixel(image *img, int x, int y)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    return img->data[x + y * img->width].r;
}

unsigned char getGpixel(image *img, int x, int y)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    return img->data[x + y * img->width].g;
}

unsigned char getBpixel(image *img, int x, int y)
{
    assert(x >= 0 && x < img->width);
    assert(y >= 0 && y < img->height);
    return img->data[x + y * img->width].b;
}

int main() {
    char fname[100];
    printf("Enter the name of the file to be read\n");
    scanf("%s", fname);
    image *img = readPPM(fname);


    image *img1 = createImage(img->width, img->height);
    image *img2 = createImage(img->width, img->height);
    int w = img->width;
    int h = img->height;

    int i, j;

    float avg = 0;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            avg += getRpixel(img, i, j);
            avg += getGpixel(img, i, j);
            avg += getBpixel(img, i, j);
        }
    }

    avg = avg / (3 * w * h);

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {

            if(getRpixel(img, i, j) < avg)
                putRpixel(img1, i, j, 0);
            else
                putRpixel(img1, i, j, 255);

            if(getGpixel(img, i, j) < avg)
                putGpixel(img1, i, j, 0);
            else
                putGpixel(img1, i, j, 255);

            if(getBpixel(img, i, j) < avg)
                putBpixel(img1, i, j, 0);
            else
                putBpixel(img1, i, j, 255);
        }
    }

    float avg_in_block = 0;
    for (i = 0; i < w; i += 50) {
        for (j = 0; j < h; j += 50) {
            int a, b;
            for (a = i; a < i + 50; a++) {
                for (b = j; b < j + 50; b++) {
                    avg_in_block += getRpixel(img, a, b);
                    avg_in_block += getGpixel(img, a, b);
                    avg_in_block += getBpixel(img, a, b);
                }
            }

            avg_in_block = avg_in_block / (3 * 50 * 50);

            for (a = i; a < i + 50; a++) {
                for (b = j; b < j + 50; b++) {
                    if(getRpixel(img, a, b) < avg_in_block)
                        putRpixel(img2, a, b, 0);
                    else
                        putRpixel(img2, a, b, 255);

                    if(getGpixel(img, a, b) < avg_in_block)
                        putGpixel(img2, a, b, 0);
                    else
                        putGpixel(img2, a, b, 255);

                    if(getBpixel(img, a, b) < avg_in_block)
                        putBpixel(img2, a, b, 0);
                    else
                        putBpixel(img2, a, b, 255);
                }
            }
        }
    }

    char fname1[100], fname2[100];
    printf("\nEnter the name of the file to which single threshold results will be written\n");
    scanf("%s", fname1);
    printf("\nEnter the name of the file to which adaptive threshold results will be written\n");
    scanf("%s", fname2);

    writePPM(fname1, img1);
    writePPM(fname2, img2);

    return 0;

}
