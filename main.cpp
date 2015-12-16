nclude "mbed.h"
#define UPPTHRESHOLD 0.6
#define DOWNTHRESHOLD 0.4
#define INTERVAL 500
#define WAIT 0.0001
Serial PC(USBTX, USBRX);
DigitalOut enable(p23);
DigitalOut RST(p22);
DigitalOut SLP(p17);
DigitalOut myled(LED1);
DigitalOut dir(p13);
DigitalOut step(p16);
DigitalOut ms1(p18);
DigitalOut ms2(p19);
DigitalOut ms3(p20);
AnalogIn eyeball(p15);

float last;
int direct;
Timer t;

void fullStep(){
    PC.printf("getting into full step...\r\n");
    ms1.write(0);
    ms2.write(0);
    ms3.write(0);
}
void halfStep(){
    PC.printf("half step...\r\n");
    ms1.write(1);
    ms2.write(0);
    ms3.write(0);
}
void quarterStep(){
    PC.printf("quarter step...\r\n");
    ms1.write(0);
    ms2.write(1);
    ms3.write(0);
}
void eighthStep(){
    PC.printf("eighth step...\r\n");
    ms1.write(1);
    ms2.write(1);
    ms3.write(0);
}
void sixteenthStep(){
    PC.printf("sixteenth step...\r\n");
    ms1.write(1);
    ms2.write(1);
    ms3.write(1);
}
void stepForwardFull(int ms){
     fullStep();
     dir.write(0);
     t.start();
     while(t.read_ms()<ms){
         step.write(1);
         wait(WAIT);
         step.write(0);
         wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepForwardHalf(int ms){
     halfStep();
     dir.write(0);
     t.start();
     while(t.read_ms()<ms){
         step.write(1);
         wait(WAIT);
         step.write(0);
         wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepForwardQuarter(int ms){
     quarterStep();
     dir.write(0);
     t.start();
     while(t.read_ms()<ms){
         step.write(1);
         wait(WAIT);
         step.write(0);
         wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepForwardEighth(int ms){
     eighthStep();
     dir.write(0);
     t.start();
     while(t.read_ms()<ms){
         step.write(1);
         wait(WAIT);
         step.write(0);
         wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepForwardSixteenth(int ms){
     sixteenthStep();
     dir.write(0);
     t.start();
     while(t.read_ms()<ms){
         step.write(1);
         wait(WAIT);
         step.write(0);
         wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepReverseFull(int ms){
    fullStep();
    dir.write(1);
    t.start();
    while(t.read_ms()<ms){
        step.write(1);
        //PC.printf("step:%d",step.read());
        wait(WAIT);
        step.write(0);
        //PC.printf("step:%d \r\n",step.read());
        wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepReverseHalf(int ms){
    halfStep();
    dir.write(1);
    t.start();
    while(t.read_ms()<ms){
        step.write(1);
        //PC.printf("step:%d",step.read());
        wait(WAIT);
        step.write(0);
        //PC.printf("step:%d \r\n",step.read());
        wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepReverseQuarter(int ms){
    quarterStep();
    dir.write(1);
    t.start();
    while(t.read_ms()<ms){
        step.write(1);
        //PC.printf("step:%d",step.read());
        wait(WAIT);
        step.write(0);
        //PC.printf("step:%d \r\n",step.read());
        wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepReverseEighth(int ms){
    eighthStep();
    dir.write(1);
    t.start();
    while(t.read_ms()<ms){
        step.write(1);
        //PC.printf("step:%d",step.read());
        wait(WAIT);
        step.write(0);
        //PC.printf("step:%d \r\n",step.read());
        wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stepReverseSixteenth(int ms){
    sixteenthStep();
    dir.write(1);
    t.start();
    while(t.read_ms()<ms){
        step.write(1);
        //PC.printf("step:%d",step.read());
        wait(WAIT);
        step.write(0);
        //PC.printf("step:%d \r\n",step.read());
        wait(WAIT);
    }
    t.stop();
    t.reset();
}
void stop(int ms){
    t.start();
    while(t.read_ms()<ms){}
    t.stop();
    t.reset();
}
int main() {
    PC.printf("start main...\r\n");
    //RST.write(1);
    //SLP.write(1);
    enable.write(0);
    step.write(0);
    /*
    stepReverseFull(INTERVAL);
    stop(INTERVAL);
    stepForwardFull(INTERVAL);
    stop(INTERVAL);
    */
    
    while(1) {
        float current = eyeball.read();
        //float delta = current-last;
        //last = current;
        PC.printf("current eyeball voltage is %f\r\n", current);
        if(current>UPPTHRESHOLD){
            PC.printf("turn right\r\n");
            stepForwardHalf(INTERVAL);
        }
        else if(current<DOWNTHRESHOLD){
            PC.printf("turn left\r\n");
            stepReverseHalf(INTERVAL);
        }
        else{
            PC.printf("stay\r\n");
            stop(INTERVAL);
        }
        step.write(0);
    }
    
}
