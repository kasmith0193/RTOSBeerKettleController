/*
 * menu_structs.h
 *
 * Created: 2/26/2025 7:52:12 PM
 *  Author: kasmi
 */ 


#ifndef MENU_STRUCTS_H_
#define MENU_STRUCTS_H_

#include <stdbool.h>

/* ----------Menu item data structure elements---------- */
// Could be turned into a menu obj
typedef enum menuItemType{
	LIST_ITEM,
	LIST_ITEM_ENTRY,
	UPDATING_VALUE,
	UPDATING_VALUE_ROTATING,
} menuItemType_t;

typedef struct menuItem menuItem_t;
typedef struct menuItem{
	menuItem_t * prev;
	//if lines replaced with pointer this could work as portable
	char line1[20];
	char line2[20];
	char line3[20];
	char line4[20];
	void (*menuFunction)(void * args);
	void * args;
	menuItemType_t menu_type;
	menuItem_t * next;
} menuItem_t;

/* Init Functions */
void setFunction(menuItem_t* item, void (*function)(void*args));
void setNextPrevPointers(menuItem_t *first, menuItem_t *secound);
void setLoopPrev(menuItem_t * item);
void setLoopNext(menuItem_t * item);
//void setStruct(void * structure);

bool gotoNext(menuItem_t* active_pointer);
bool gotoPrev(menuItem_t* active_pointer);

bool triggerFunction(menuItem_t * item);

#endif /* MENU_STRUCTS_H_ */