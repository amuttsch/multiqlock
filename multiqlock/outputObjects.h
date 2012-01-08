/**
 * outputObjects.h
 *
 * Definition of predefined output objects like numbers
 * @mc       Arduino/RBBB
 * @autor    Benedikt Gerlich
 * 			 Bernhard Göberndorfer (DE_AT)
 * @version  2.0
 * @datum    07.01.2012
 */
#ifndef OUTPUTOBJECTS_H
#define OUTPUTOBJECTS_H

/**
 * Definition der Woerter
 */



#ifdef DE_DE
	#define VOR          setMatrixOr(3, 0b1110000000000000)
	#define NACH         setMatrixOr(3, 0b0000000111100000)
	#define ESIST        setMatrixOr(0, 0b1101110000000000)
	#define UHR          setMatrixOr(9, 0b0000000011100000)
	
	#define FUENF        setMatrixOr(0, 0b0000000111100000)
	#define ZEHN         setMatrixOr(1, 0b1111000000000000)
	#define VIERTEL      setMatrixOr(2, 0b0000111111100000)
	#define ZWANZIG      setMatrixOr(1, 0b0000111111100000)
	#define HALB         setMatrixOr(4, 0b1111000000000000)
	#define DREIVIERTEL  setMatrixOr(2, 0b1111111111100000)
	
	#define H_EIN        setMatrixOr(5, 0b1110000000000000)
	#define H_EINS       setMatrixOr(5, 0b1111000000000000)
	#define H_ZWEI       setMatrixOr(5, 0b0000000111100000)
	#define H_DREI       setMatrixOr(6, 0b1111000000000000)
	#define H_VIER       setMatrixOr(6, 0b0000000111100000)
	#define H_FUENF      setMatrixOr(4, 0b0000000111100000)
	#define H_SECHS      setMatrixOr(7, 0b1111100000000000)
	#define H_SIEBEN     setMatrixOr(8, 0b1111110000000000)
	#define H_ACHT       setMatrixOr(7, 0b0000000111100000)
	#define H_NEUN       setMatrixOr(9, 0b0001111000000000)
	#define H_ZEHN       setMatrixOr(9, 0b1111000000000000)
	#define H_ELF        setMatrixOr(4, 0b0000011100000000)
	#define H_ZWOELF     setMatrixOr(8, 0b0000001111100000)
#endif

#ifdef DE_AT
  #define FUNK         setMatrixOr(2, 0b0001111000000000)
  #define ESIST        setMatrixOr(0, 0b1101110000000000)
  #define PUNKT        setMatrixOr(1, 0b0000001111100000)
  
  #define FUENF        setMatrixOr(0, 0b0000000111100000)
  #define ZEHN         setMatrixOr(1, 0b1111000000000000)
  
  #define VOR          setMatrixOr(2, 0b1110000000000000)
  #define NACH         setMatrixOr(2, 0b0000000111100000)
  
  #define VIERTEL      setMatrixOr(3, 0b0000111111100000)
  #define HALB         setMatrixOr(4, 0b1111000000000000)
  #define DREIVIERTEL  setMatrixOr(3, 0b1111111111100000)
  
  #define H_EIN        setMatrixOr(4, 0b0000000111000000)
  #define H_EINS       setMatrixOr(4, 0b0000000111100000)
  #define H_ZWEI       setMatrixOr(5, 0b1111000000000000)
  #define H_DREI       setMatrixOr(5, 0b0000000111100000)
  #define H_VIER       setMatrixOr(6, 0b1111000000000000)
  #define H_FUENF      setMatrixOr(6, 0b0000000111100000)
  #define H_SECHS      setMatrixOr(7, 0b1111100000000000)
  #define H_SIEBEN     setMatrixOr(7, 0b0000111111000000)
  #define H_ACHT       setMatrixOr(8, 0b1111000000000000)
  #define H_NEUN       setMatrixOr(8, 0b0000000111100000)
  #define H_ZEHN       setMatrixOr(9, 0b1111000000000000)
  #define H_ELF        setMatrixOr(6, 0b0000011100000000)
  #define H_ZWOELF     setMatrixOr(9, 0b0000001111100000)

#endif

#define CORNER_UPPER_LEFT   setMatrixOr(1, 0b0000000000010000)
#define CORNER_UPPER_RIGHT  setMatrixOr(0, 0b0000000000001000)
#define CORNER_LOWER_LEFT   setMatrixOr(2, 0b0000000000000010)
#define CORNER_LOWER_RIGHT  setMatrixOr(3, 0b0000000000000100)

const byte Seconds_ziffern[10][7] = {
  {
    0b00001110,
    0b00010001,
    0b00010011,
    0b00010101,
    0b00011001,
    0b00010001,
    0b00001110
  }
  , {
    0b00000010,
    0b00000110,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00000111
  }
  , {
    0b00001110,
    0b00010001,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00011111
  }
  , {
    0b00011111,
    0b00000010,
    0b00000100,
    0b00000010,
    0b00000001,
    0b00010001,
    0b00001110
  }
  , {
    0b00000010,
    0b00000110,
    0b00001010,
    0b00010010,
    0b00011111,
    0b00000010,
    0b00000010
  }
  , {
    0b00011111,
    0b00010000,
    0b00011110,
    0b00000001,
    0b00000001,
    0b00010001,
    0b00001110
  }
  , {
    0b00000110,
    0b00001000,
    0b00010000,
    0b00011110,
    0b00010001,
    0b00010001,
    0b00001110
  }
  , {
    0b00011111,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00001000,
    0b00001000
  }
  , {
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001110
  }
  , {
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001111,
    0b00000001,
    0b00000010,
    0b00001100
  }
};

/**
 * Definition von Hi/Lo
 */
const uint16_t hiLo[2][10] = 
{
  {
    0b1111111111100000,
    0b1000000000100000,
    0b1010101110100000,
    0b1010100100100000,
    0b1011100100100000,
    0b1010100100100000,
    0b1010101110100000,
    0b1000000000100000,
    0b1000000000100000,
    0b1111111111100000
  }, {
    0b1111111111100000,
    0b1000000000100000,
    0b1010000100100000,
    0b1010001010100000,
    0b1010001010100000,
    0b1010001010100000,
    0b1011100100100000,
    0b1000000000100000,
    0b1000000000100000,
    0b1111111111100000
  }
};

#endif
