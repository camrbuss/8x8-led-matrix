#ifndef Board_H
#define Board_H

#include <Wire.h>
#include <Arduino.h>

extern "C" {
  #include "user_interface.h" //For os_timer_t etc
}

class Board
{
public:
	Board(uint8_t latchpin, uint8_t clockpin, uint8_t datapin);
	~Board();

  uint16_t frameRateTimerMS = 1000;
  bool animation = false;
 
  void allOn();
  void allOff();
  void setHeart();
  void setX();
  void setSnake();
  void multiplexRow();
  void setSingleFrame(uint8_t frame[8]);
  void setFrameRate(uint8_t frameRate);
  void incrementFrame();
	
private:
  uint8_t _frameCurrent[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t _frameHeart[8] = {0b01101100, 0b10010010, 0b10000010, 0b10000010, 0b01000100, 0b00101000, 0b00010000, 0x00};
  uint8_t _frameX[8] = {0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00011000, 0b00100100, 0b01000010, 0b10000001};
  uint8_t _frameOff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t _frameOn[8] = {255, 255, 255, 255, 255, 255, 255, 255};

  uint8_t _animCurrent[100][8];
  uint8_t _animSnake[3][8] = {{255, 0, 0, 0, 0, 0, 0, 0},
                              {0, 255, 0, 0, 0, 0, 0, 0},
                              {0, 0, 255, 0, 0, 0, 0, 0}};
  uint8_t i = 0;
  uint8_t _j = 0;
  uint16_t dataToSend = 0;
  uint8_t _ltc;
  uint8_t _clc;
  uint8_t _dat;
  
  uint8_t _numFrames = 0;

};

#endif
