// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdint.h>

void printPacket(uint8_t* packet, short length){
    printf("[");
    for(int i = 0; i < length; i ++){
        printf("0x%02X,", packet[i]);
    }
    printf("]\n");
}

class CAN{
private:
    uint8_t stored[8] = {0,0,0,0,0,0,0,0};
    short id;
public: 
    CAN(){}
    
    void sendPacket(short id, uint8_t* packet, short length){
        printf("You sent this packet: [id: 0x%04X]",id);
        printPacket(packet, length);
        if(!(id ^ 0x23E1 ^ 0x221E)){ //convoluted for no reason lol
            printf("Motor successfully recieved angle: %d | velocity: %d | torque: %d | temperature: %d\n", packet[0] << 8 | packet[1], (int16_t)(packet[2] << 8 | packet[3]), (int16_t)(packet[4] << 8 | packet[5]), packet[6]);
            this->id = id;
            int a = rand() % 8192;
            int v = (rand() % 16000) - 8000;
            int c = (rand() % 300) - 150;
            int t = (rand() % 30) + 60;
            stored[0] = (uint8_t)(a >> 8);
            stored[1] = (uint8_t)(a);
            stored[2] = (uint8_t)(v >> 8);
            stored[3] = (uint8_t)(v);
            stored[4] = (uint8_t)(c >> 8);
            stored[5] = (uint8_t)(c);
            stored[6] = (uint8_t)(t);
            stored[7] = 0x00;
            //printPacket(stored, 8);
        }
    }
    
    void readPacket(short* id, uint8_t* packet, short* length){
        *length = 8;
        *id = this->id;
        std::copy(stored, stored + 8, packet);
        printf("You recieved this packet: [id: 0x%04X]",this->id);
        
        printPacket(packet, 8);
    }
};

//TOUCH NOTHING ABOVE THIS

int main() {
    srand(0); //MODIFY THIS TO CHANGE THE READ PACKET TEST CASE
    CAN canbus; //usually this has parameters, but since this isn't real and we're running this on a standard compiler, it doesn't
    
    int16_t angle = 8000;
    int16_t velocity = 400;
    int16_t torque = -10000;
    int8_t temperature = 200; 
    //test cases: angle, velocity, torque, temperature
    //test case 1: 1300, 2140, 382, 10
    //test case 2: 8000, -5000, -800, 90
    //test case 3: 8000, 400, -10000, 200
    
    
    //TODO: ENCODE THE DATA TO SEND TO THE MOTOR
    uint8_t data_send[8] = {0,0,0,0,0,0,0,0};
    short len_send = 8;
    short id_send = 0x1FF;
    
    //encrypting angle
    uint8_t angle_byte1 = (uint8_t)(angle >> 8); //isolating first angle byte
    uint8_t angle_byte2 = (uint8_t)angle; //isolating second angle byte
    data_send[0] = angle_byte1; //passing into datasend
    data_send[1] = angle_byte2; 
    
    //encrytping velocity
    uint8_t velocity_byte1 = (uint8_t)(velocity >> 8); //isolating first velocity byte
    uint8_t velocity_byte2 = (uint8_t)velocity; //isolating second velocity byte
    data_send[2] = velocity_byte1; //pasing into datasend
    data_send[3] = velocity_byte2;
    
    //encrypting torque
    uint8_t torque_byte1 = (uint8_t)(torque >> 8); //isolating first torque byte
    uint8_t torque_byte2 = (uint8_t)torque; //isolating second torque byte
    data_send[4] = torque_byte1; // passing into datasend
    data_send[5] = torque_byte2;
    
    data_send[6] = temperature; //no need to encrypt
    
    uint8_t data_recv[8] = {0,0,0,0,0,0,0,0};
    short len_recv;
    short id_recv;
    //in practice, we can often reuse the sending and receiving data, but for now we'll keep them separate. In real scenarios, we often don't need to keep hold of the packet we just sent, and if we do, we possess the data that we used to construct it.
    
    //We pass in the packet via its adress (its an array), and then it is sent through the can bus
    canbus.sendPacket(id_send, data_send, len_send);
    
    //We pass in an array (data_recv) and it is filled in the can read function, as well as the id we recieve from and the length of the packet.
    canbus.readPacket(&id_recv, data_recv, &len_recv);

    uint16_t decrypted_angle = data_recv[0] << 8; //first angle byte
    decrypted_angle += data_recv[1]; //second angle byte
    
    int16_t decrypted_velocity = data_recv[2] << 8; //first velocity byte
    decrypted_velocity += data_recv[3]; //second velocity byte
    
    uint16_t decrypted_torque = data_recv[4] << 8; //first torque byte
    decrypted_torque += data_recv[5]; //second torque byte
    
    uint8_t decrypted_temperature = data_recv[6]; //only temperature byte
    
    printf("Decoded - angle: %d | velocity: %d | torque: %d | temperature: %d \n", decrypted_angle, decrypted_velocity, decrypted_torque, decrypted_temperature); //printing values
    
    //TODO: DECODE THE DATA RECIEVED BY THE MOTOR, YOU SHOULD GET DIFFERENT DATA DEPENDING ON SRAND
    // srand(0): 1383, -5114, 27, 85
    // srand(2): 6138, 6719, 38, 65
    // srand(4): 7645, 4083, 124, 86
}
