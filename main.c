#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{

    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReser1;
    uint16_t bfReser2;
    uint32_t bfOffSetBits;

} infoHead;


typedef struct
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biplanes;
    uint16_t biBitCount;
    uint32_t biCompress;
    uint32_t biSizeImag;
    uint32_t biXPPMeter;
    uint32_t biYPPMeter;
    uint32_t biClrUsed;
    uint32_t biClrImpor;
} infoImage;


typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reservado;
} infoColor;

#pragma pack(pop)


int main()
{
    infoHead Head;
    infoImage Image;
    infoColor Color;

    int Width;
    int Height;

    int Blue;
    int Red;
    int Green;
    int gray;
    int Limiar=0;
    int cor_Preto=0,cor_Branco=255;

    int aux;
    int i,j;
    char nome3[100];
    char nome2[100];
    char nome[100];
    int EixoX=0,EixoY=0;
    int BordaC,BordaA;

    //unsigned char const imagem[504];
    int ValorPixel;
    int coluna[84][48];

    FILE *file;
    FILE *fileGray;
    FILE *arquivoString;


    printf("Digite o nome do arquivo:");
    gets(nome);
    strcat(nome,".bmp");
    printf("Digite o nome do novo arquivo bmp:");
    gets(nome2);
    strcpy(nome3,nome2);
    strcat(nome2,"_gs.bmp");

    strcat(nome3,"_h.txt");




    //printf("%s",nome);
    printf("Nome do novo arquivo:\n%s",nome2);

    file = fopen(nome,"rb");

    if(file != NULL)
    {
        printf("\nO arquivo abriu com sucesso");
    }

    if(file == NULL)
    {
        printf("\nO arquivo nao abriu com sucesso");
    }

    fread(&Head,sizeof(infoHead),1,file);
    fread(&Image,sizeof(infoImage),1,file);


    Height = Image.biHeight;
    Width = Image.biWidth;

    unsigned char grayscaleImage[Width][Height];

    printf("\n\t=*=TAMANHO DA IMAGEM=*=");
    printf("\nAltura:%i",Height);
    printf("\nLargura:%i",Width);
    printf("\n\nDigite as cordenadas da imagem que deseja recortar:");
    printf("\nEixo X:");
    scanf("%i",&EixoX);
    printf("\nEixo Y:");
    scanf("%i",&EixoY);
    printf("\n\nQual O valor do Limiar para transformar em monocromatica ?");
    scanf("%i",&Limiar);

    BordaA = EixoY + 48;
    BordaC = EixoX + 84;
    printf("\n%i , %i",BordaA,BordaC);


    fileGray = fopen(nome2,"wb");

    if(fileGray != NULL)
    {
        printf("\nO novo arquivo foi criado com sucesso.");
    }

    fwrite(&Head,sizeof(infoHead),1, fileGray);
    fseek(fileGray,0, SEEK_CUR);
    fwrite(&Image,sizeof(infoImage),1, fileGray);


    arquivoString = fopen(nome3,"wb");

    if (arquivoString != NULL) {
    printf("\nO novo arquivo foi criado com sucesso.");
    }

    for (i = 0; i < Width; i++) {
    for (j = 0; j < Height; j++) {
        fread(&Color, sizeof(infoColor), 1, file);

        gray = (uint8_t)((0.2989 * Color.red) + (0.5870 * Color.green) + (0.1140 * Color.blue));
        Color.red = Color.green = Color.blue = gray;

        fwrite(&Color, sizeof(infoColor), 1, fileGray);

        if (EixoX <= i && i < BordaC && EixoY <= j && j < BordaA) {
            if (gray < Limiar) {
                ValorPixel = 0x01;
            } else {
                ValorPixel = 0x00;
            }
            grayscaleImage[i][j] = ValorPixel;



            /*
            // Escreva o valor do pixel no arquivo de texto na posição correta
            fprintf(arquivoString, " 0x%02X,", ValorPixel);

            // Preencha a matriz da imagem em escala de cinza
*/
            printf("|%i|",grayscaleImage[i][j]);

        }

    }
    if(i<89){
    printf("\n");
    }
    fprintf(arquivoString, "\n");
}

    fclose(arquivoString);
    fclose(fileGray);
    fclose(file);


int x=0,y=0;
i=0,j=0;

for(i=0;i++;i<=84){
    for(x=0;x++;x<=6){
                //j=y=coluna
                //i=x=linha
            coluna[x][y] = grayscaleImage[i][j];

            j++;
            if(x==6){
                i++;
            }
    }

            x++;
}
x=0,y=0;
int aux=0;
for(x=0;x++;x<=84){
    for(x=0;x++;x<=6){

      aux=+coluna[x][y];

    }
    fprintf(arquivoString, "0x%02X,",aux);
    printf("\n");
}





    return 0;
}
