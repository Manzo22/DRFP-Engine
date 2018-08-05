
#include "Arithmetic_Unit.h"

int32_t convertir_a_negativo(uint32_t w1, uint32_t w2, uint32_t w3){
    int32_t ret=0;
    if((w1&10000000)==0){
        return w3|(w2<<8)|(w1<<16);
    }
    ret = w3|(w2<<8)|(w1<<16);
    ret = ret - 16777216;
    return ret;
}

float arctan_2(int32_t wx, int32_t wy){
    float ret;
    ret = (float)atan2(wx, wy);
    ret = (float)ret*180/PI;
    return ret;
}

float arctan_3(int32_t wx, int32_t wy, int32_t wz){
    float ret;
    double temp;
    long long int long_temp;


    //printf("wx: %d  xy: %d\n", wx, wy);
    long_temp = (long long int)wx*(long long int)wx+(long long int)wy*(long long int)wy;
    //printf("long temp: %lli\n", long_temp);

    if (long_temp<2000000000){
        temp = (double) long_temp;
        ret = atan2(wz, sqrt(temp));
        ret = ((float)ret/PI)*180;
        return ret;
    }

    temp = ((float)wx/1000)*((float)wx/1000) + ((float)wy/1000)*((float)wy/1000);
    //printf("temp2: %lf\n", temp);
    ret = (float)atan2(wz, 1000*sqrt(temp));
    //printf("ret: %f\n", ret);
    ret = (float)ret*180/PI;
    //printf("ret: %f\n", ret);
    return ret;
}

float raiz_3(float wx, float wy, float wz){
    float ret;
    double temp;
    temp = wx*wx + wy*wy + wz*wz;
    if(temp>0){
        ret = sqrt(temp);
        return ret;
    }
    temp = (wx*wx)/100 + (wy*wy)/100 + (wz*wz)/100;
    ret = 10*sqrt(temp);
    return ret;
}

int truncar(float valor){
    float temp;
    int ret;

    ret = (int)valor;
    temp = (float)ret - valor;
    if(temp>0)
        ret = ret-1;
    return ret;
}

int convertir_a_par(int valor){
    if((valor%2)==0)
        return valor;
    else
        return valor -1;
}

float raiz_2(float wx, float wy){
    float ret;
    double temp;
    temp = wx*wx + wy*wy;
    if(temp>0){
        ret = sqrt(temp);
        return ret;
    }
    temp = (wx*wx)/100 + (wy*wy)/100;
    ret = 10*sqrt(temp);
    return ret;
}
