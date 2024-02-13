#include<Wire.h>
const int MPU=0x68; //MPU6050 indirizzo I2C 
int16_t AcX,AcY,AcZ,Tmp;
//**********************
// low pass Xth order
//**********************
float LPF_X(float * out, float in, float coeff,uint8_t order){//86us per ordine
  out[0] = in;
  for (uint8_t i=1; i<=order; i++) out[i]+=(out[i-1]-out[i]*coeff;
  return out[order]
}

void setup(){
  Wire.begin(2,0);            //inizializza la comunicazione
  Wire.setClock(400000);      //configura la frequenza del clock
  Wire.beginTransmission(MPU);//inizia la comunicazione con mpu
  Wire.write(0x6B);           //dialoga con il registro 6B  indirizzo di PWR_MGMT_1 
  Wire.write(0x00);           //scrivi 0 nel registro per resettare il device
  Wire.endTransmission(true); //fine della trasmissione
  
  // configurazioni accellerometro 
  Wire.beginTransmission(MPU);
  Wire.write(0x1A);           //1A indirizzo di CONFIG EXT_SYNC_SET /DLPF 
  Wire.write(0x06);           //ACCELLEROMETER Bandwidth 5HZ 
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);           //1C indirizzo di ACCEL_CONFIG 
  Wire.write(0x00);           //+-2g 0x00 +-4g 0x08 +-8g 0x10 +-16g 0x18
  Wire.endTransmission(true);
  Serial.begin(9600);       
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  Serial.println(" ");
  delay(333);
}

//implementare un filtro passa basso

//implementare un calibratore per misurare i limiti e pertanto la scala 

//fare le operazioni di trigonometria per tirare fuori gli angoli forse lo facciamo sul server.
