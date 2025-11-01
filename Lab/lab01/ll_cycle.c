#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
		if(head == NULL) return 0;
		node *tortise = head;
		node *hare = head;
		
		while(1){
			hare = hare->next;
			if(hare == NULL) return 0;
			hare = hare->next;
			if(hare == NULL) return 0;
			tortise = tortise->next;
			if(tortise == hare) return 1;
		}

    return 0;
}
