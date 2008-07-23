#include "Zorkmid.h"

/* constructors */
Zorkmid::Zorkmid(Saiph *saiph) : Analyzer("Zorkmid"), saiph(saiph) {
	action = "";
	priority = ILLEGAL_PRIORITY;
}

/* methods */
void Zorkmid::command(string *command) {
	*command = action;
}

void Zorkmid::finish() {
	if (saiph->itemtracker->on_ground != NULL) {
		/* there are items here, we should look for zorkmids */
		req.request = REQUEST_LOOT_STASH;
		req.priority = ZORKMID_LOOT_PRIORITY;
		req.coordinate = saiph->position;
		for (list<Item>::iterator i = saiph->itemtracker->on_ground->items.begin(); i != saiph->itemtracker->on_ground->items.end(); ++i) {
			if (i->name.find(ZORKMID_GOLD_PIECE, 0) != string::npos) {
				/* request that someone loot this stash */
				saiph->request(req);
				return;
			}
		}
	}
}

void Zorkmid::parseMessages(const string &messages) {
	if (saiph->world->menu && messages.find(MESSAGE_PICK_UP_WHAT, 0) != string::npos) {
		/* check if there's gold here to pick up */
		for (map<unsigned char, Item>::iterator p = saiph->itemtracker->pickup.begin(); p != saiph->itemtracker->pickup.end(); ++p) {
			if (p->second.name.find(ZORKMID_GOLD_PIECE, 0) != string::npos) {
				/* pick it up :) */
				action = p->first;
				priority = PRIORITY_PICKUP_ITEM;
				continue;
			}
		}
	}
}
