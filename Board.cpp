#include "Board.h"

Board::Board(uint8_t latchpin, uint8_t clockpin, uint8_t datapin)
{
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  this->_ltc = latchpin;
  this->_clc = clockpin;
  this->_dat = datapin;
}

Board::~Board()
{
  // Nothing
}

void Board::allOn()
{
  this->animation = false;
  memcpy(this->_frameCurrent, this->_frameOn, 8);
}

void Board::allOff()
{
  this->animation = false;
  memcpy(this->_frameCurrent, this->_frameOff, 8);
}

void Board::setHeart()
{
  this->animation = false;
  memcpy(this->_frameCurrent, this->_frameHeart, 8);
}

void Board::setX()
{
  this->animation = false;
  memcpy(this->_frameCurrent, this->_frameX, 8);
}

void Board::setSnake()
{
  this->animation = true;
  this->_numFrames = sizeof(_animSnake) / sizeof(_animSnake[0]);
  memcpy(_animCurrent, _animSnake, sizeof(_animCurrent));
  this->_j = 0;
  this->setFrameRate(2);
}

void Board::setSingleFrame(uint8_t frame[8])
{
  this->animation = false;
  memcpy(this->_frameCurrent, frame, 8);
}

void Board::multiplexRow()
{
  dataToSend = (0x01 << i) + (~_frameCurrent[i] << 8);
  digitalWrite(this->_ltc, LOW);
  shiftOut(this->_dat, this->_clc, LSBFIRST, (dataToSend >> 8));
  shiftOut(this->_dat, this->_clc, MSBFIRST, dataToSend);
  digitalWrite(this->_ltc, HIGH);
  if (i == 7)
  {
    i = 0;
  }
  else
  {
    i++;
  }
}

// Private Methods

void Board::incrementFrame()
{
  if (_j < _numFrames - 1)
  {
    memcpy(_frameCurrent, _animCurrent[_j], sizeof(_frameCurrent));
    _j++;
  }
  else
  {
    memcpy(_frameCurrent, _animCurrent[_j], sizeof(_frameCurrent));
    _j = 0;
  }
}

void Board::setFrameRate(uint8_t frameRate)
{
  this->frameRateTimerMS = (uint16_t)(1000 / frameRate);
}
