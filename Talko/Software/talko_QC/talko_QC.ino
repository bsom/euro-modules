/*
  http://www.microsmart.co.za/technical/2014/03/01/advanced-arduino-adc/
 */

#include "talkie2.h"

// Define various ADC prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

// Pin matching from 4511 to Aduino
const int LedA = 9;
const int LedB = 10;
const int LedC = 11;
const int LedD = 12;

int count = 0;



Talkie voice;

// the setup routine runs once when you press reset:

const uint8_t spZERO[]     PROGMEM = {0x69, 0xFB, 0x59, 0xDD, 0x51, 0xD5, 0xD7, 0xB5, 0x6F, 0x0A, 0x78, 0xC0, 0x52, 0x01, 0x0F, 0x50, 0xAC, 0xF6, 0xA8, 0x16, 0x15, 0xF2, 0x7B, 0xEA, 0x19, 0x47, 0xD0, 0x64, 0xEB, 0xAD, 0x76, 0xB5, 0xEB, 0xD1, 0x96, 0x24, 0x6E, 0x62, 0x6D, 0x5B, 0x1F, 0x0A, 0xA7, 0xB9, 0xC5, 0xAB, 0xFD, 0x1A, 0x62, 0xF0, 0xF0, 0xE2, 0x6C, 0x73, 0x1C, 0x73, 0x52, 0x1D, 0x19, 0x94, 0x6F, 0xCE, 0x7D, 0xED, 0x6B, 0xD9, 0x82, 0xDC, 0x48, 0xC7, 0x2E, 0x71, 0x8B, 0xBB, 0xDF, 0xFF, 0x1F};
const uint8_t spONE[]      PROGMEM = {0x66, 0x4E, 0xA8, 0x7A, 0x8D, 0xED, 0xC4, 0xB5, 0xCD, 0x89, 0xD4, 0xBC, 0xA2, 0xDB, 0xD1, 0x27, 0xBE, 0x33, 0x4C, 0xD9, 0x4F, 0x9B, 0x4D, 0x57, 0x8A, 0x76, 0xBE, 0xF5, 0xA9, 0xAA, 0x2E, 0x4F, 0xD5, 0xCD, 0xB7, 0xD9, 0x43, 0x5B, 0x87, 0x13, 0x4C, 0x0D, 0xA7, 0x75, 0xAB, 0x7B, 0x3E, 0xE3, 0x19, 0x6F, 0x7F, 0xA7, 0xA7, 0xF9, 0xD0, 0x30, 0x5B, 0x1D, 0x9E, 0x9A, 0x34, 0x44, 0xBC, 0xB6, 0x7D, 0xFE, 0x1F};
const uint8_t spTWO[]      PROGMEM = {0x06, 0xB8, 0x59, 0x34, 0x00, 0x27, 0xD6, 0x38, 0x60, 0x58, 0xD3, 0x91, 0x55, 0x2D, 0xAA, 0x65, 0x9D, 0x4F, 0xD1, 0xB8, 0x39, 0x17, 0x67, 0xBF, 0xC5, 0xAE, 0x5A, 0x1D, 0xB5, 0x7A, 0x06, 0xF6, 0xA9, 0x7D, 0x9D, 0xD2, 0x6C, 0x55, 0xA5, 0x26, 0x75, 0xC9, 0x9B, 0xDF, 0xFC, 0x6E, 0x0E, 0x63, 0x3A, 0x34, 0x70, 0xAF, 0x3E, 0xFF, 0x1F};
const uint8_t spTHREE[]    PROGMEM = {0x0C, 0xE8, 0x2E, 0x94, 0x01, 0x4D, 0xBA, 0x4A, 0x40, 0x03, 0x16, 0x68, 0x69, 0x36, 0x1C, 0xE9, 0xBA, 0xB8, 0xE5, 0x39, 0x70, 0x72, 0x84, 0xDB, 0x51, 0xA4, 0xA8, 0x4E, 0xA3, 0xC9, 0x77, 0xB1, 0xCA, 0xD6, 0x52, 0xA8, 0x71, 0xED, 0x2A, 0x7B, 0x4B, 0xA6, 0xE0, 0x37, 0xB7, 0x5A, 0xDD, 0x48, 0x8E, 0x94, 0xF1, 0x64, 0xCE, 0x6D, 0x19, 0x55, 0x91, 0xBC, 0x6E, 0xD7, 0xAD, 0x1E, 0xF5, 0xAA, 0x77, 0x7A, 0xC6, 0x70, 0x22, 0xCD, 0xC7, 0xF9, 0x89, 0xCF, 0xFF, 0x03};
const uint8_t spFOUR[]     PROGMEM = {0x08, 0x68, 0x21, 0x0D, 0x03, 0x04, 0x28, 0xCE, 0x92, 0x03, 0x23, 0x4A, 0xCA, 0xA6, 0x1C, 0xDA, 0xAD, 0xB4, 0x70, 0xED, 0x19, 0x64, 0xB7, 0xD3, 0x91, 0x45, 0x51, 0x35, 0x89, 0xEA, 0x66, 0xDE, 0xEA, 0xE0, 0xAB, 0xD3, 0x29, 0x4F, 0x1F, 0xFA, 0x52, 0xF6, 0x90, 0x52, 0x3B, 0x25, 0x7F, 0xDD, 0xCB, 0x9D, 0x72, 0x72, 0x8C, 0x79, 0xCB, 0x6F, 0xFA, 0xD2, 0x10, 0x9E, 0xB4, 0x2C, 0xE1, 0x4F, 0x25, 0x70, 0x3A, 0xDC, 0xBA, 0x2F, 0x6F, 0xC1, 0x75, 0xCB, 0xF2, 0xFF};
const uint8_t spFIVE[]     PROGMEM = {0x08, 0x68, 0x4E, 0x9D, 0x02, 0x1C, 0x60, 0xC0, 0x8C, 0x69, 0x12, 0xB0, 0xC0, 0x28, 0xAB, 0x8C, 0x9C, 0xC0, 0x2D, 0xBB, 0x38, 0x79, 0x31, 0x15, 0xA3, 0xB6, 0xE4, 0x16, 0xB7, 0xDC, 0xF5, 0x6E, 0x57, 0xDF, 0x54, 0x5B, 0x85, 0xBE, 0xD9, 0xE3, 0x5C, 0xC6, 0xD6, 0x6D, 0xB1, 0xA5, 0xBF, 0x99, 0x5B, 0x3B, 0x5A, 0x30, 0x09, 0xAF, 0x2F, 0xED, 0xEC, 0x31, 0xC4, 0x5C, 0xBE, 0xD6, 0x33, 0xDD, 0xAD, 0x88, 0x87, 0xE2, 0xD2, 0xF2, 0xF4, 0xE0, 0x16, 0x2A, 0xB2, 0xE3, 0x63, 0x1F, 0xF9, 0xF0, 0xE7, 0xFF, 0x01};
const uint8_t spSIX[]      PROGMEM = {0x04, 0xF8, 0xAD, 0x4C, 0x02, 0x16, 0xB0, 0x80, 0x06, 0x56, 0x35, 0x5D, 0xA8, 0x2A, 0x6D, 0xB9, 0xCD, 0x69, 0xBB, 0x2B, 0x55, 0xB5, 0x2D, 0xB7, 0xDB, 0xFD, 0x9C, 0x0D, 0xD8, 0x32, 0x8A, 0x7B, 0xBC, 0x02, 0x00, 0x03, 0x0C, 0xB1, 0x2E, 0x80, 0xDF, 0xD2, 0x35, 0x20, 0x01, 0x0E, 0x60, 0xE0, 0xFF, 0x01};
const uint8_t spSEVEN[]    PROGMEM = {0x0C, 0xF8, 0x5E, 0x4C, 0x01, 0xBF, 0x95, 0x7B, 0xC0, 0x02, 0x16, 0xB0, 0xC0, 0xC8, 0xBA, 0x36, 0x4D, 0xB7, 0x27, 0x37, 0xBB, 0xC5, 0x29, 0xBA, 0x71, 0x6D, 0xB7, 0xB5, 0xAB, 0xA8, 0xCE, 0xBD, 0xD4, 0xDE, 0xA6, 0xB2, 0x5A, 0xB1, 0x34, 0x6A, 0x1D, 0xA7, 0x35, 0x37, 0xE5, 0x5A, 0xAE, 0x6B, 0xEE, 0xD2, 0xB6, 0x26, 0x4C, 0x37, 0xF5, 0x4D, 0xB9, 0x9A, 0x34, 0x39, 0xB7, 0xC6, 0xE1, 0x1E, 0x81, 0xD8, 0xA2, 0xEC, 0xE6, 0xC7, 0x7F, 0xFE, 0xFB, 0x7F};
const uint8_t spEIGHT[]    PROGMEM = {0x65, 0x69, 0x89, 0xC5, 0x73, 0x66, 0xDF, 0xE9, 0x8C, 0x33, 0x0E, 0x41, 0xC6, 0xEA, 0x5B, 0xEF, 0x7A, 0xF5, 0x33, 0x25, 0x50, 0xE5, 0xEA, 0x39, 0xD7, 0xC5, 0x6E, 0x08, 0x14, 0xC1, 0xDD, 0x45, 0x64, 0x03, 0x00, 0x80, 0x00, 0xAE, 0x70, 0x33, 0xC0, 0x73, 0x33, 0x1A, 0x10, 0x40, 0x8F, 0x2B, 0x14, 0xF8, 0x7F};
const uint8_t spNINE[]     PROGMEM = {0xE6, 0xA8, 0x1A, 0x35, 0x5D, 0xD6, 0x9A, 0x35, 0x4B, 0x8C, 0x4E, 0x6B, 0x1A, 0xD6, 0xA6, 0x51, 0xB2, 0xB5, 0xEE, 0x58, 0x9A, 0x13, 0x4F, 0xB5, 0x35, 0x67, 0x68, 0x26, 0x3D, 0x4D, 0x97, 0x9C, 0xBE, 0xC9, 0x75, 0x2F, 0x6D, 0x7B, 0xBB, 0x5B, 0xDF, 0xFA, 0x36, 0xA7, 0xEF, 0xBA, 0x25, 0xDA, 0x16, 0xDF, 0x69, 0xAC, 0x23, 0x05, 0x45, 0xF9, 0xAC, 0xB9, 0x8F, 0xA3, 0x97, 0x20, 0x73, 0x9F, 0x54, 0xCE, 0x1E, 0x45, 0xC2, 0xA2, 0x4E, 0x3E, 0xD3, 0xD5, 0x3D, 0xB1, 0x79, 0x24, 0x0D, 0xD7, 0x48, 0x4C, 0x6E, 0xE1, 0x2C, 0xDE, 0xFF, 0x0F};
const uint8_t spTEN[]      PROGMEM = {0x0E, 0x38, 0x3C, 0x2D, 0x00, 0x5F, 0xB6, 0x19, 0x60, 0xA8, 0x90, 0x93, 0x36, 0x2B, 0xE2, 0x99, 0xB3, 0x4E, 0xD9, 0x7D, 0x89, 0x85, 0x2F, 0xBE, 0xD5, 0xAD, 0x4F, 0x3F, 0x64, 0xAB, 0xA4, 0x3E, 0xBA, 0xD3, 0x59, 0x9A, 0x2E, 0x75, 0xD5, 0x39, 0x6D, 0x6B, 0x0A, 0x2D, 0x3C, 0xEC, 0xE5, 0xDD, 0x1F, 0xFE, 0xB0, 0xE7, 0xFF, 0x03};
const uint8_t spELEVEN[]   PROGMEM = {0xA5, 0xEF, 0xD6, 0x50, 0x3B, 0x67, 0x8F, 0xB9, 0x3B, 0x23, 0x49, 0x7F, 0x33, 0x87, 0x31, 0x0C, 0xE9, 0x22, 0x49, 0x7D, 0x56, 0xDF, 0x69, 0xAA, 0x39, 0x6D, 0x59, 0xDD, 0x82, 0x56, 0x92, 0xDA, 0xE5, 0x74, 0x9D, 0xA7, 0xA6, 0xD3, 0x9A, 0x53, 0x37, 0x99, 0x56, 0xA6, 0x6F, 0x4F, 0x59, 0x9D, 0x7B, 0x89, 0x2F, 0xDD, 0xC5, 0x28, 0xAA, 0x15, 0x4B, 0xA3, 0xD6, 0xAE, 0x8C, 0x8A, 0xAD, 0x54, 0x3B, 0xA7, 0xA9, 0x3B, 0xB3, 0x54, 0x5D, 0x33, 0xE6, 0xA6, 0x5C, 0xCB, 0x75, 0xCD, 0x5E, 0xC6, 0xDA, 0xA4, 0xCA, 0xB9, 0x35, 0xAE, 0x67, 0xB8, 0x46, 0x40, 0xB6, 0x28, 0xBB, 0xF1, 0xF6, 0xB7, 0xB9, 0x47, 0x20, 0xB6, 0x28, 0xBB, 0xFF, 0x0F};
const uint8_t spTWELVE[]   PROGMEM = {0x09, 0x98, 0xDA, 0x22, 0x01, 0x37, 0x78, 0x1A, 0x20, 0x85, 0xD1, 0x50, 0x3A, 0x33, 0x11, 0x81, 0x5D, 0x5B, 0x95, 0xD4, 0x44, 0x04, 0x76, 0x9D, 0xD5, 0xA9, 0x3A, 0xAB, 0xF0, 0xA1, 0x3E, 0xB7, 0xBA, 0xD5, 0xA9, 0x2B, 0xEB, 0xCC, 0xA0, 0x3E, 0xB7, 0xBD, 0xC3, 0x5A, 0x3B, 0xC8, 0x69, 0x67, 0xBD, 0xFB, 0xE8, 0x67, 0xBF, 0xCA, 0x9D, 0xE9, 0x74, 0x08, 0xE7, 0xCE, 0x77, 0x78, 0x06, 0x89, 0x32, 0x57, 0xD6, 0xF1, 0xF1, 0x8F, 0x7D, 0xFE, 0x1F};
const uint8_t spTHIR_[]    PROGMEM = {0x04, 0xA8, 0xBE, 0x5C, 0x00, 0xDD, 0xA5, 0x11, 0xA0, 0xFA, 0x72, 0x02, 0x74, 0x97, 0xC6, 0x01, 0x09, 0x9C, 0xA6, 0xAB, 0x30, 0x0D, 0xCE, 0x7A, 0xEA, 0x6A, 0x4A, 0x39, 0x35, 0xFB, 0xAA, 0x8B, 0x1B, 0xC6, 0x76, 0xF7, 0xAB, 0x2E, 0x79, 0x19, 0xCA, 0xD5, 0xEF, 0xCA, 0x57, 0x08, 0x14, 0xA1, 0xDC, 0x45, 0x64, 0x03, 0x00, 0xC0, 0xFF, 0x03};
const uint8_t spFIF_[]     PROGMEM = {0x08, 0x98, 0x31, 0x93, 0x02, 0x1C, 0xE0, 0x80, 0x07, 0x5A, 0xD6, 0x1C, 0x6B, 0x78, 0x2E, 0xBD, 0xE5, 0x2D, 0x4F, 0xDD, 0xAD, 0xAB, 0xAA, 0x6D, 0xC9, 0x23, 0x02, 0x56, 0x4C, 0x93, 0x00, 0x05, 0x10, 0x90, 0x89, 0x31, 0xFC, 0x3F};
const uint8_t sp_TEEN[]    PROGMEM = {0x09, 0x58, 0x2A, 0x25, 0x00, 0xCB, 0x9F, 0x95, 0x6C, 0x14, 0x21, 0x89, 0xA9, 0x78, 0xB3, 0x5B, 0xEC, 0xBA, 0xB5, 0x23, 0x13, 0x46, 0x97, 0x99, 0x3E, 0xD6, 0xB9, 0x2E, 0x79, 0xC9, 0x5B, 0xD8, 0x47, 0x41, 0x53, 0x1F, 0xC7, 0xE1, 0x9C, 0x85, 0x54, 0x22, 0xEC, 0xFA, 0xDB, 0xDD, 0x23, 0x93, 0x49, 0xB8, 0xE6, 0x78, 0xFF, 0x3F};
const uint8_t spTWENTY[]   PROGMEM = {0x0A, 0xE8, 0x4A, 0xCD, 0x01, 0xDB, 0xB9, 0x33, 0xC0, 0xA6, 0x54, 0x0C, 0xA4, 0x34, 0xD9, 0xF2, 0x0A, 0x6C, 0xBB, 0xB3, 0x53, 0x0E, 0x5D, 0xA6, 0x25, 0x9B, 0x6F, 0x75, 0xCA, 0x61, 0x52, 0xDC, 0x74, 0x49, 0xA9, 0x8A, 0xC4, 0x76, 0x4D, 0xD7, 0xB1, 0x76, 0xC0, 0x55, 0xA6, 0x65, 0xD8, 0x26, 0x99, 0x5C, 0x56, 0xAD, 0xB9, 0x25, 0x23, 0xD5, 0x7C, 0x32, 0x96, 0xE9, 0x9B, 0x20, 0x7D, 0xCB, 0x3C, 0xFA, 0x55, 0xAE, 0x99, 0x1A, 0x30, 0xFC, 0x4B, 0x3C, 0xFF, 0x1F};
const uint8_t spT[]        PROGMEM = {0x01, 0xD8, 0xB6, 0xDD, 0x01, 0x2F, 0xF4, 0x38, 0x60, 0xD5, 0xD1, 0x91, 0x4D, 0x97, 0x84, 0xE6, 0x4B, 0x4E, 0x36, 0xB2, 0x10, 0x67, 0xCD, 0x19, 0xD9, 0x2C, 0x01, 0x94, 0xF1, 0x78, 0x66, 0x33, 0xEB, 0x79, 0xAF, 0x7B, 0x57, 0x87, 0x36, 0xAF, 0x52, 0x08, 0x9E, 0x6B, 0xEA, 0x5A, 0xB7, 0x7A, 0x94, 0x73, 0x45, 0x47, 0xAC, 0x5A, 0x9C, 0xAF, 0xFF, 0x07};
const uint8_t spHUNDRED[]  PROGMEM = {0x04, 0xC8, 0x7E, 0x5C, 0x02, 0x0A, 0xA8, 0x62, 0x43, 0x03, 0xA7, 0xA8, 0x62, 0x43, 0x4B, 0x97, 0xDC, 0xF2, 0x14, 0xC5, 0xA7, 0x9B, 0x7A, 0xD3, 0x95, 0x37, 0xC3, 0x1E, 0x16, 0x4A, 0x66, 0x36, 0xF3, 0x5A, 0x89, 0x6E, 0xD4, 0x30, 0x55, 0xB5, 0x32, 0xB7, 0x31, 0xB5, 0xC1, 0x69, 0x2C, 0xE9, 0xF7, 0xBC, 0x96, 0x12, 0x39, 0xD4, 0xB5, 0xFD, 0xDA, 0x9B, 0x0F, 0xD1, 0x90, 0xEE, 0xF5, 0xE4, 0x17, 0x02, 0x45, 0x28, 0x77, 0x11, 0xD9, 0x40, 0x9E, 0x45, 0xDD, 0x2B, 0x33, 0x71, 0x7A, 0xBA, 0x0B, 0x13, 0x95, 0x2D, 0xF9, 0xF9, 0x7F};
const uint8_t spTHOUSAND[] PROGMEM = {0x0C, 0xE8, 0x2E, 0xD4, 0x02, 0x06, 0x98, 0xD2, 0x55, 0x03, 0x16, 0x68, 0x7D, 0x17, 0xE9, 0x6E, 0xBC, 0x65, 0x8C, 0x45, 0x6D, 0xA6, 0xE9, 0x96, 0xDD, 0xDE, 0xF6, 0xB6, 0xB7, 0x5E, 0x75, 0xD4, 0x93, 0xA5, 0x9C, 0x7B, 0x57, 0xB3, 0x6E, 0x7D, 0x12, 0x19, 0xAD, 0xDC, 0x29, 0x8D, 0x4F, 0x93, 0xB4, 0x87, 0xD2, 0xB6, 0xFC, 0xDD, 0xAC, 0x22, 0x56, 0x02, 0x70, 0x18, 0xCA, 0x18, 0x26, 0xB5, 0x90, 0xD4, 0xDE, 0x6B, 0x29, 0xDA, 0x2D, 0x25, 0x17, 0x8D, 0x79, 0x88, 0xD4, 0x48, 0x79, 0x5D, 0xF7, 0x74, 0x75, 0xA1, 0x94, 0xA9, 0xD1, 0xF2, 0xED, 0x9E, 0xAA, 0x51, 0xA6, 0xD4, 0x9E, 0x7F, 0xED, 0x6F, 0xFE, 0x2B, 0xD1, 0xC7, 0x3D, 0x89, 0xFA, 0xB7, 0x0D, 0x57, 0xD3, 0xB4, 0xF5, 0x37, 0x55, 0x37, 0x2E, 0xE6, 0xB2, 0xD7, 0x57, 0xFF, 0x0F};
const uint8_t spAND[]      PROGMEM = {0xA9, 0x6B, 0x21, 0xB9, 0x22, 0x66, 0x9F, 0xAE, 0xC7, 0xE1, 0x70, 0x7B, 0x72, 0xBB, 0x5B, 0xDF, 0xEA, 0x56, 0xBB, 0x5C, 0x65, 0xCB, 0x66, 0xC5, 0x3D, 0x67, 0xD7, 0xAB, 0x6D, 0x2E, 0x64, 0x30, 0x93, 0xEE, 0xB1, 0xCD, 0x3D, 0x92, 0xB9, 0x9A, 0xDA, 0xB2, 0x8E, 0x40, 0x12, 0x9A, 0x6A, 0xEB, 0x96, 0x8F, 0x78, 0x98, 0xB3, 0x2A, 0xB4, 0xD3, 0x48, 0xAA, 0x2F, 0x7D, 0xA7, 0x7B, 0xFB, 0x0C, 0x73, 0x71, 0x5C, 0xCE, 0x6E, 0x5C, 0x52, 0x6C, 0x73, 0x79, 0x9A, 0x13, 0x4B, 0x89, 0x45, 0xE9, 0x6E, 0x49, 0x42, 0xA9, 0x57, 0xFF, 0x3F};
const uint8_t spMINUS[]    PROGMEM = {0xE6, 0x28, 0xC4, 0xF8, 0x44, 0x9A, 0xFB, 0xCD, 0xAD, 0x8D, 0x2A, 0x4E, 0x4A, 0xBC, 0xB8, 0x8C, 0xB9, 0x8A, 0xA9, 0x48, 0xED, 0x72, 0x87, 0xD3, 0x74, 0x3B, 0x1A, 0xA9, 0x9D, 0x6F, 0xB3, 0xCA, 0x5E, 0x8C, 0xC3, 0x7B, 0xF2, 0xCE, 0x5A, 0x5E, 0x35, 0x66, 0x5A, 0x3A, 0xAE, 0x55, 0xEB, 0x9A, 0x57, 0x75, 0xA9, 0x29, 0x6B, 0xEE, 0xB6, 0xD5, 0x4D, 0x37, 0xEF, 0xB5, 0x5D, 0xC5, 0x95, 0x84, 0xE5, 0xA6, 0xFC, 0x30, 0xE0, 0x97, 0x0C, 0x0D, 0x58, 0x40, 0x03, 0x1C, 0xA0, 0xC0, 0xFF, 0x03};
const uint8_t spMILLI[]    PROGMEM = {0x6E, 0xF0, 0x8A, 0xB3, 0x4B, 0xEB, 0xC6, 0xAE, 0x36, 0xA7, 0x1A, 0x3A, 0x54, 0x53, 0xD6, 0xDC, 0xEC, 0x66, 0x23, 0xDF, 0x58, 0x26, 0x43, 0xB4, 0xCD, 0xEA, 0x74, 0x5D, 0x94, 0x46, 0xF0, 0x96, 0x3B, 0x9D, 0x79, 0x98, 0x26, 0x75, 0xDB, 0xB3, 0xD7, 0xB6, 0xF5, 0x90, 0xA8, 0x91, 0x9F, 0xEA, 0x9E, 0xEE, 0xE9, 0x9B, 0x20, 0x7D, 0xCB, 0xFF, 0x03};
const uint8_t spVOLTS[]    PROGMEM = {0xA0, 0xDA, 0xA2, 0xB2, 0x3A, 0x44, 0x55, 0x9C, 0xFA, 0xB0, 0xBA, 0x46, 0x72, 0xDA, 0xD1, 0xDB, 0xAE, 0x47, 0x59, 0x61, 0xED, 0x28, 0x79, 0xED, 0x45, 0xAF, 0x5A, 0xDF, 0x60, 0xF4, 0x39, 0x69, 0xAB, 0x63, 0xD9, 0x3B, 0xD2, 0xBC, 0x24, 0xA5, 0xF5, 0xB6, 0x0F, 0x80, 0x01, 0x3E, 0x63, 0x65, 0xC0, 0x5F, 0x63, 0x12, 0x90, 0x80, 0x06, 0x24, 0x20, 0x01, 0x0E, 0xFC, 0x3F};


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);  
  pinMode(5, INPUT_PULLUP);  
  pinMode(2, INPUT_PULLUP); 

 pinMode(LedA, OUTPUT);
  pinMode(LedB, OUTPUT);
  pinMode(LedC, OUTPUT);
  pinMode(LedD, OUTPUT);
  pinMode(13, OUTPUT);




   // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library

  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_128;    // set our own prescaler to 64 

  
}

void Display(int n)
{
digitalWrite(LedD, ((n >> 3) & 1) ? HIGH : LOW);
digitalWrite(LedC, ((n >> 2) & 1) ? HIGH : LOW);
digitalWrite(LedB, ((n >> 1) & 1) ? HIGH : LOW);
digitalWrite(LedA, (n & 1) ? HIGH : LOW);
}

/* Say any number between -999,999 and 999,999 */
void sayNumber(long n) {
  if (n<0) {
    voice.say(spMINUS);
    sayNumber(-n);
  } else if (n==0) {
    voice.say(spZERO);
  } else {
    if (n>=1000) {
      int thousands = n / 1000;
      sayNumber(thousands);
      voice.say(spTHOUSAND);
      n %= 1000;
      if ((n > 0) && (n<100)) voice.say(spAND);
    }
    if (n>=100) {
      int hundreds = n / 100;
      sayNumber(hundreds);
      voice.say(spHUNDRED);
      n %= 100;
      if (n > 0) voice.say(spAND);
    }
    if (n>19) {
      int tens = n / 10;
      switch (tens) {
        case 2: voice.say(spTWENTY); break;
        case 3: voice.say(spTHIR_); voice.say(spT); break;
        case 4: voice.say(spFOUR); voice.say(spT);  break;
        case 5: voice.say(spFIF_);  voice.say(spT); break;
        case 6: voice.say(spSIX);  voice.say(spT); break;
        case 7: voice.say(spSEVEN);  voice.say(spT); break;
        case 8: voice.say(spEIGHT);  voice.say(spT); break;
        case 9: voice.say(spNINE);  voice.say(spT); break;
      }
      n %= 10;
    }
    switch(n) {
      case 1: voice.say(spONE); break;
      case 2: voice.say(spTWO); break;
      case 3: voice.say(spTHREE); break;
      case 4: voice.say(spFOUR); break;
      case 5: voice.say(spFIVE); break;
      case 6: voice.say(spSIX); break;
      case 7: voice.say(spSEVEN); break;
      case 8: voice.say(spEIGHT); break;
      case 9: voice.say(spNINE); break;
      case 10: voice.say(spTEN); break;
      case 11: voice.say(spELEVEN); break;
      case 12: voice.say(spTWELVE); break;
      case 13: voice.say(spTHIR_); voice.say(sp_TEEN); break;
      case 14: voice.say(spFOUR); voice.say(sp_TEEN);break;
      case 15: voice.say(spFIF_); voice.say(sp_TEEN); break;
      case 16: voice.say(spSIX); voice.say(sp_TEEN); break;
      case 17: voice.say(spSEVEN); voice.say(sp_TEEN); break;
      case 18: voice.say(spEIGHT); voice.say(sp_TEEN); break;
      case 19: voice.say(spNINE); voice.say(sp_TEEN); break;
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  
  // print out the value you read:
  Serial.print(analogRead(A0));
  Serial.print("  ");
   Serial.print(analogRead(A1));
  Serial.print("  ");
   Serial.print(analogRead(A2));
  Serial.print("  ");
   Serial.print(analogRead(A3));
  Serial.print("  ");
  Serial.print(analogRead(A4));
  Serial.print("  ");

  Serial.print(digitalRead(2));
  Serial.print("  ");
  
  Serial.print(digitalRead(4));
  Serial.print("  ");

  Serial.print(digitalRead(5));
  Serial.println("  ");

  digitalWrite(13,digitalRead(2));
   count = map(analogRead(0),-100,1000,0,9);
   
  Display(count);  // Displays the current count value
  delay(200);        // delay in between reads for stability

   int voltage = analogRead(1) * 5.000 / 1.023;
 
 //sayNumber(voltage);
 // voice.say(spMILLI);
 // voice.say(spVOLTS);
  
} 
