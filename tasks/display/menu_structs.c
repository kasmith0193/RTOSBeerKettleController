/*
 * menu_structs.c
 *
 * Created: 2/26/2025 8:05:27 PM
 *  Author: kasmi
 */ 

#include "options.h"
#include "menu_structs.h"

#include <stdlib.h>

void setFunction(menuItem_t* item, void(*function)(void*args)){
	item->menuFunction = function;
}

void setNextPrevPointers(menuItem_t *first, menuItem_t *secound){
	first->next = secound;
	secound->prev = first;
}

void setLoopPrev(menuItem_t * item){
	item->prev = item;
}

void setLoopNext(menuItem_t * item){
	item->next = item;
}

bool gotoNext(menuItem_t *active_pointer){
	if(active_pointer->next == NULL){
		return false;
	}
	active_pointer = active_pointer->next;
	if(active_pointer == NULL){
		return false;
	}
	return true;
}

bool gotoPrev(menuItem_t *active_pointer){
	if(active_pointer->prev == NULL){
		return false;
	}
	active_pointer = active_pointer->prev;
	if(active_pointer == NULL){
		return false;
	}
	return true;
}

bool triggerFunction(menuItem_t * item){
	if(item->menuFunction == NULL){
		return false;
	}
	item->menuFunction(item->args);
	return true;
}
