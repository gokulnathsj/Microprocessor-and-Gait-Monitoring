#include "mbed.h"
#include "MMA8451Q.h"
#define MMA8451_I2C_ADDRESS (0x1d << 1)
#include <string>

// variable declaration
#define REG_WHO_AM_I      0x0D
#define REG_CTRL_REG_1    0x2A
#define REG_OUT_X_MSB     0x01
#define REG_OUT_Y_MSB     0x03
#define REG_OUT_Z_MSB     0x05

#define UINT14_MAX        16383

//function definitions
float accX();
float accY();
float accZ();
int16_t accAxis(uint8_t);
void readRegs(int, uint8_t *, int);
void writeRegs(uint8_t *, int); 
void uart_init();
void uart_print(string);

//I2C initialise

I2C i2c(PTE25, PTE24);
int m_addr = MMA8451_I2C_ADDRESS;
void acc_init(){
    uint8_t data[2] = {REG_CTRL_REG_1, 0x01};
    writeRegs(data, 2);
}
 
int main(void) {
    acc_init();
    uart_init();
    PwmOut rled(LED_RED);
    PwmOut gled(LED_GREEN);
    PwmOut bled(LED_BLUE);
    while (true) {       
        float x = accX();
        float y = accY();
        float z = accZ();
        
        float xcos = x / sqrt(x * x + y * y + z * z);
        float ycos = y / sqrt(x * x + y * y + z * z);
        float zcos = z / sqrt(x * x + y * y + z * z);
        
        float limit = 1 / 1.732;
        
        if((abs(ycos) <= 1 && abs(ycos) > 0.9) || (abs(zcos) < 1 && abs(zcos) > 0.9)){
            uart_print("The person has laid down\n");
            bled = 1.0 - abs(z);
            rled = 1.0;
            gled = 1.0;
            wait(0.5);
        }
        else if(abs(xcos) <= 1  && abs(xcos) >= 0.92){
            uart_print("The person is standing\n");  
            gled = 1.0 - abs(x);
            rled = 1.0;
            bled = 1.0;
            wait(0.5);
        }else if(abs(zcos) <= 0.92 && abs(zcos) > limit){
            uart_print("You are Unstable.. please remain in stable position\n");           
            rled = 1.0 - abs(z);    
            gled = 1.0;
            bled = 1.0;
            wait(0.2);
            rled = 1.0;    
            gled = 1.0;
            bled = 1.0;
            wait(0.2);
        }
        else if(abs(zcos) <= limit){
            uart_print("Alert!!!..Falling Chances detected\n");            
            rled = 1.0 - abs(z);    
            gled = 1.0;
            bled = 1.0;
            wait(0.5);
            rled = 1.0;    
            gled = 1.0;
            bled = 1.0;
            wait(0.5);
        }
        if(abs(x) > 1.1 || abs(y) > 1.1 || abs(z) > 1.1){
            uart_print("PERSON HAS FALLEN DOWN!!!!\n");
            rled = 1.0 - abs(y);   
            gled = 1.0;
            bled = 1.0;
            wait(4);
        }
    }
}
void uart_init(void) { 
    SIM->SCGC4 |= 0x0400;
    SIM->SOPT2 |= 0x04000000; 
    UART0->C2 |= 0; 
    UART0->BDH |= 0x00; 
    UART0->BDL |= 0x16; 
    UART0->C4 |= 0x0F; 
    UART0->C1 |= 0x00; 
    UART0->C2 |= 0x08;
    SIM->SCGC5 |= 0x0200; 
    PORTA->PCR[2] |= 0x0200;
}

void uart_print(string data){
    for(int i = 0; i < data.size(); i++){
        char a = data[i];
        while(!(UART0->S1 & 0x80)) { }
            UART0->D = a;
    }
}

float accX() {
    return (float(accAxis(REG_OUT_X_MSB))/4096.0);
}

float accY() {
    return (float(accAxis(REG_OUT_Y_MSB))/4096.0);
}

float accZ() {
    return (float(accAxis(REG_OUT_Z_MSB))/4096.0);
}

int16_t accAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    readRegs(addr, res, 2);

    acc = (res[0] << 6) | (res[1] >> 2);
    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;

    return acc;
}

void readRegs(int addr, uint8_t * data, int len) {
    char t[1] = {addr};
    i2c.write(m_addr, t, 1, true);
    i2c.read(m_addr, (char *)data, len);
}

void writeRegs(uint8_t * data, int len) {
    i2c.write(m_addr, (char *)data, len);
}