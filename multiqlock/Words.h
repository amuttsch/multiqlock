/**
 * Words.h
 * Hier sind alle Wörter definiert
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    12.4.2011
 */
#ifndef WORDS_H
#define WORDS_H

/**
 * Definition der Woerter
 */
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

