
#include "filtro.h"
float filter_iirr(int analogVal, int banderaFS ){  
float entrada;
float salida;
float estadoTemp ;

//
int NL[MWSPT_NSEC] = { 1,3,1,3,1,2,1 }; 
const float NUM[MWSPT_NSEC][3] = {
  {
     0.1703699231,              0,              0 
  },
  {
                1,   0.4610463381,              1 
  },
  {
     0.2077388465,              0,              0 
  },
  {
                1,     1.15225184,              1 
  },
  {
     0.5875786543,              0,              0 
  },
  {
                1,              1,              0 
  },
  {
                1,              0,              0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1,2,1 };
const float DEN[MWSPT_NSEC][3] = {
  {
                1,              0,              0 
  },
  {
                1,  -0.5839410424,   0.8720063567 
  },
  {
                1,              0,              0 
  },
  {
                1,  -0.9251801968,   0.5800253749 
  },
  {
                1,              0,              0 
  },
  {
                1,  -0.6174653172,              0 
  },
  {
                1,              0,              0 
  }
};
float estados[MWSPT_NSEC] [2] = {{0,0}, {0,0}, {0,0}};
 entrada = analogVal;
 // for (int k1 = 0; k1 < 2; k1++){
 for (int k1 = 0; k1 < MWSPT_NSEC; k1++){
  switch (NL[k1]){
    
    case 1:{
      //salida = (entrada*NUM[k1][0])/DEN [k1][0];/
      salida = entrada*NUM[k1][0];
      //salida = entrada;
      break;
      }
    case 2:{
        estadoTemp = entrada-(estados[k1][0]*DEN[k1][1]);
        salida = estadoTemp + (estados[k1][0]*NUM[k1][1]);
        estados[k1][0] = estadoTemp;

 break;
    }
     
      
    case 3:{
      if (banderaFS){
        estadoTemp = entrada-(estados[k1][0]*DEN[k1][1]+estados[k1][1]*DEN[k1][2]);
        salida = estadoTemp + (estados[k1][0]*NUM[k1][1]+estados[k1][1]);
        estados[k1][1] = estadoTemp;
   
      }
      else{
        estadoTemp = entrada-(estados[k1][1]*DEN[k1][1]+estados[k1][0]*DEN[k1][2]);
        salida = estadoTemp + (estados[k1][1]*NUM[k1][1]+estados[k1][0]);
        estados[k1][0] = estadoTemp;
       
      }
      break;
   }
  }
   // Actualizar entrada y salida
 entrada = salida;
 return  salida;
 salida = 0;
 }
 if(banderaFS){
 banderaFS=0;
 }else{
 banderaFS=1;
 }
}
