/*
 * app.h
 *
 * Created: 2/20/2025 9:39:55 PM
 *  Author: kasmi
 */ 

#include <stdint.h>


#ifndef APP_H_
#define APP_H_


typedef struct appTaskArgs{
	uint8_t num;
}appTaskArgs_t;

appTaskArgsInit(appTaskArgs_t*);

appTask(appTaskArgs_t*);

#endif /* APP_H_ */