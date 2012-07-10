#include<stdlib.h>
#include "ami.h"
#include "ami_bmp.h"
#include<math.h>



float masc_posi(float *canal,float mascara[3][3],int width,int height,int y,int x){
  float resultado=0,producto;
  int i,j,fila,columna;
  fila = y-2;
  for(i=0;i<3;i++){
    fila=fila+1;
    columna=x-1;
    for(j=0;j<3;j++){
      if(fila<0){
        if(columna<0){
          producto = (mascara[i][j])*((canal)[((fila+1)*width)+(columna+1)]);

        }
        else{
          if((columna>=0)&&(columna<=width)){
            producto = (mascara[i][j])*((canal)[((fila+1)*width)+(columna)]);
          }
          else {
            producto = (mascara[i][j])*((canal)[((fila+1)*width)+(columna-1)]);
          };
        };
      }
      else{
        if((fila>=0)&&(fila<height)){
          if(columna<0){
            producto = (mascara[i][j])*((canal)[((fila)*width)+(columna+1)]);

          }
          else{
            if((columna>=0)&&(columna<width)){
              producto = (mascara[i][j])*((canal)[((fila)*width)+(columna)]);
            }
            else {
              producto = (mascara[i][j])*((canal)[((fila)*width)+(columna-1)]);
            };
          };

        }
        else{
          if(columna<0){
            producto = (mascara[i][j])*((canal)[((fila-1)*width)+(columna+1)]);

          }
          else{
            if((columna>=0)&&(columna<width)){
              producto = (mascara[i][j])*((canal)[((fila-1)*width)+(columna)]);
            }
            else {
              producto = (mascara[i][j])*((canal)[((fila-1)*width)+(columna-1)]);
            };
          };

        };
      };
      resultado = resultado+producto;
      columna=columna+1;
    };
  };
  return resultado;
};
//Funcion para calcular la aplicación de la máscara a un canal
void aan_mascara_canal(float *canal_input, float *canal_output, int width, int height,
    float m[3][3]){
  int i,j;

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      (canal_output)[(i*width)+j]= masc_posi(canal_input,m,width,height,i,j);
    };
  };
};
//función que calcula la máscara a aplicar
void mascara_perona(float m[3][3],float *K,int width,int height,int y,int x){
  m[0][0] = 0;
  m[0][2] = 0;
  m[2][0]= 0;
  m[2][2]= 0;
  if((y>0) && (y< (height-1))){
    if((x>0) && (x<width-1)){
      m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
      m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
      m[1][1]= (-1*(K[((y+1)*width)+x]))-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+(x-1)]);
      m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
      m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);
    }
    else{
      if(x==0){
        m[0][1]=(K[(y*width)+x])+(K[(y*width)+x]);
        m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
        m[1][1]=(-1*(K[((y+1)*width)+x]))-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+x]);
        m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
        m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);

      }
      else {
        if(x == (width -1)){
          m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
          m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
          m[1][1]=-(K[((y+1)*width)+x])-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x)])-(K[(y*width)+(x-1)]);
          m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
          m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x)]);
        }
      }
    }
  }
  else{
    if(y==0){
      if((x>0) && (x<width-1)){
        m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
        m[1][0]=(K[(y*width)+x])+(K[((y)*width)+x]);
        m[1][1]=-(K[((y+1)*width)+x])-(K[((y)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+(x-1)]);
        m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
        m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);
      }
      else{
        if(x==0){
          m[0][1]=(K[(y*width)+x])+(K[(y*width)+x]);
          m[1][0]=(K[(y*width)+x])+(K[((y)*width)+x]);
          m[1][1]=-(K[((y+1)*width)+x])-(K[((y)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+x]);
          m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
          m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);
        }
        else {
          if(x == (width -1)){
            m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
            m[1][0]=(K[(y*width)+x])+(K[((y)*width)+x]);
            m[1][1]=-(K[((y+1)*width)+x])-(K[((y)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x)])-(K[(y*width)+(x-1)]);								m[1][2]=(K[(y*width)+x])+(K[((y+1)*width)+x]);
            m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x)]);
          }
        }
      }
    }
    else {
      if(y == (height -1)){
        if((x>0) && (x<width-1)){
          m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
          m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
          m[1][1]=-(K[((y)*width)+x])-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+(x-1)]);
          m[1][2]=(K[(y*width)+x])+(K[((y)*width)+x]);
          m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);
        }
        else{
          if(x==0){
            m[0][1]=(K[(y*width)+x])+(K[(y*width)+x]);
            m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
            m[1][1]=-(K[((y)*width)+x])-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x+1)])-(K[(y*width)+x]);
            m[1][2]=(K[(y*width)+x])+(K[((y)*width)+x]);
            m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x+1)]);

          }
          else {
            if(x == (width -1)){
              m[0][1]=(K[(y*width)+x])+(K[(y*width)+(x-1)]);
              m[1][0]=(K[(y*width)+x])+(K[((y-1)*width)+x]);
              m[1][1]=-(K[((y)*width)+x])-(K[((y-1)*width)+x])-(4*(K[(y*width)+x]))-(K[(y*width)+(x)])-(K[(y*width)+(x-1)]);
              m[1][2]=(K[(y*width)+x])+(K[((y)*width)+x]);
              m[2][1]=(K[(y*width)+x])+(K[(y*width)+(x)]);
            }
          }
        }
      }
    }
  }
}



void calcular_gradiente(float *canal_input,float *canal_output,int width,int height){

  float masc_horizontal[3][3]= {{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.},{-2.*(sqrt(2.)-1.)/4,0.,2.*(sqrt(2.)-1.)/4.},{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.}};
  float masc_vertical[3][3]  = {{-(2.-sqrt(2.))/4.,-2.*(sqrt(2.)-1.)/4.,-(2.-sqrt(2.))/4.},{0.,0.,0.},{(2.-sqrt(2.))/4.,2.*(sqrt(2.)-1.)/4.,(2.-sqrt(2.))/4.}};
  float *h,*v;
  int i;

  h = (float*)malloc((width*height)*sizeof(float));
  v = (float*)malloc((width*height)*sizeof(float));

  aan_mascara_canal(canal_input,h,width,height,masc_horizontal);
  aan_mascara_canal(canal_input,v,width,height,masc_vertical);

  for(i=0;i<(height*width);i++){
    canal_output[i]= sqrt((h[i]*h[i])+(v[i]*v[i]));
  };

  free(h);
  free(v);
}

//funcion que aplica el metodo de perona malik a un canal determinado
void perona_canal(float* canal_input,int width,int height,float dt,float lambda){
  int i,j,posicion;
  float * gradiente,*K,*canal_aux;
  float mascara[3][3];
  float posi;
  // calculamos el módulo del gradiente
  gradiente =(float*)malloc((width*height)*sizeof(float));
  calcular_gradiente(canal_input,gradiente,width,height);

  // calculamos los valores de K
  K =(float*)malloc((width*height)*sizeof(float));
  for(i=0;i<(width*height);i++){
    K[i]=exp(-1*lambda*(gradiente[i]));
  }

  // guardamos los valores del canal original, para los cálculos de las sucesivas máscaras
  canal_aux =(float*)malloc((width*height)*sizeof(float));
  for(i=0;i<(width*height);i++){
    canal_aux[i]=canal_input[i];
  }



  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      posicion = (i*width)+j;
      // calculamos la máscara para la posición actual
      mascara_perona(mascara,K,width,height,i,j);
      posi = masc_posi(canal_aux,mascara,width,height,i,j);
      canal_input[posicion]=canal_input[posicion] + ((dt/2.0)*posi);
    }
  }
  free(gradiente);
  free(K);
  free(canal_aux);
}

// función que aplica el  método de perona malik a cada canal de una imagen dada
void perona_malik(float* red_input,float*green_input,float*blue_input,int width,int height,float dt, int niter,float lambda){
  int i,j;
  char name[200];
  unsigned char *ro,*go,*bo;

  ro=(unsigned char*)malloc((width*height)*sizeof(unsigned char));
  go=(unsigned char*)malloc((width*height)*sizeof(unsigned char));
  bo=(unsigned char*)malloc((width*height)*sizeof(unsigned char));

  for(i=0;i<(width*height);i++){
    ro[i]=red_input[i];
    go[i]=green_input[i];
    bo[i]=blue_input[i];
  }

  for(i=0;i<niter; i++){
    sprintf(name,"/home/groteck/Imágenes/practica9/resultado/imagen_%d.bmp",100000+i);
    ami_write_bmp(name,ro,go,bo,width,height);
    perona_canal(red_input,width,height,dt,lambda);
    perona_canal(green_input,width,height,dt,lambda);
    perona_canal(blue_input,width,height,dt,lambda);
    for(j=0;j<(width*height);j++){
      if(red_input[j]>255){
        ro[j]=255;
      }
      else{
        if(red_input[j]<0){
          ro[j]=0;
        }
        else ro[j]=(unsigned char)red_input[j];
      }
      if(green_input[j]>255){
        go[j]=255;
      }
      else{
        if(green_input[j]<0){
          go[j]=0;
        }
        else go[j]=(unsigned char)green_input[j];
      }
      if(blue_input[j]>255){
        bo[j]=255;
      }
      else{
        if(blue_input[j]<0){
          bo[j]=0;
        }
        else bo[j]=(unsigned char)blue_input[j];
      }
    }

  };
  free(ro);
  free(go);
  free(bo);
}

#include <stdio.h>
int main(){
  unsigned char *ro_ch,*ve_ch,*az_ch;
  float *red_input,*red_output,*blue_input,*blue_output,*green_input,*green_output,lambda;
  char fentrada[200];
  int i,niter,tam,h,w;
  float dt;
  printf("---------------MENU-----------------.\n");
  printf("Introduzca la direccion del archivo\n");
  scanf("%s",fentrada);
  printf("introduzca dt \n");
  scanf("%f",&dt);
  printf("Introduzca numero de iteraciones\n");
  scanf("%d",&niter);
  printf("Introduzca valor para el parámetro lambda\n");
  scanf("%f",&lambda);
  ami_read_bmp(fentrada,&ro_ch,&ve_ch,&az_ch, &w,&h);
  tam=w*h;
  red_input=(float*)malloc(tam*sizeof(float));
  blue_input=(float*)malloc(tam*sizeof(float));
  green_input=(float*)malloc(tam*sizeof(float));
  red_output=(float*)malloc(tam*sizeof(float));
  blue_output=(float*)malloc(tam*sizeof(float));
  green_output=(float*)malloc(tam*sizeof(float));
  for(i=0;i<tam;i++){
    red_input[i]=ro_ch[i];
    blue_input[i]=az_ch[i];
    green_input[i]=ve_ch[i];
  }
  perona_malik(red_input,green_input,blue_input,w,h,dt,niter,lambda);
  free(red_input);
  free(blue_input);
  free(green_input);
  free(red_output);
  free(blue_output);
  free(green_output);
  free(ro_ch);
  free(az_ch);
  free(ve_ch);
  printf("FINISH");
  return 0;
}
