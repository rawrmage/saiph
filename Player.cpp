#include "Player.h"

/* constructors */
Player::Player() {
	/* attributes */
	alignment = 0;
	charisma = 0;
	constitution = 0;
	dexterity = 0;
	intelligence = 0;
	strength = 0;
	wisdom = 0;
	/* status */
	armor_class = 0;
	encumbrance = 0;
	experience = 0;
	hunger = 0;
	hitpoints = 0;
	hitpoints_max = 0;
	power = 0;
	power_max = 0;
	turn = 0;
	/* effects */
	blind = false;
	confused = false;
	foodpoisoned = false;
	hallucinating = false;
	ill = false;
	slimed = false;
	stunned = false;
	/* position */
	dungeon = 0;
	col = 0;
	row = 0;
	/* zorkmids */
	zorkmids = 0;

	/* used for parsing rows */
	//effects = new char*[MAX_EFFECTS];
	//for (int e = 0; e < MAX_EFFECTS; ++e)
	//	effects[e] = new char[MAX_TEXT_LENGTH];
}

/* destructors */
Player::~Player() {
	for (int e = 0; e < MAX_EFFECTS; ++e)
		delete [] effects[e];
	delete [] effects;
}

/* methods */
bool Player::parseAttributeRow(const char *attributerow) {
	/* fetch attributes */
	int matched = sscanf(attributerow, "%*[^:]:%d%*[^:]:%d%*[^:]:%d%*[^:]:%d%*[^:]:%d%*[^:]:%d%s", &strength, &dexterity, &constitution, &intelligence, &wisdom, &charisma, effects[0]);
	if (matched < 7) {
		cerr << "Error parsing attribute line, expected 7 values, found " << matched << endl;
		cerr << attributerow << endl;
		return false;
	}
	if (effects[0][0] == 'L')
		alignment = LAWFUL;
	else if (effects[0][0] == 'N')
		alignment = NEUTRAL;
	else    
		alignment = CHAOTIC;
	return true;
}

bool Player::parseStatusRow(const char *statusrow) {
	/* fetch status */
	encumbrance = 0;
	hunger = 0;
	blind = false;
	confused = false;
	foodpoisoned = false;
	hallucinating = false;
	ill = false;
	slimed = false;
	stunned = false;
	int matched = sscanf(statusrow, "%*[^:]:%d%*[^:]:%d%*[^:]:%d(%d%*[^:]:%d(%d%*[^:]:%d%*[^:]:%d%*[^:]:%d%s%s%s%s%s", &dungeon, &zorkmids, &hitpoints, &hitpoints_max, &power, &power_max, &armor_class, &experience, &turn, effects[0], effects[1], effects[2], effects[3], effects[4]);
	if (matched < 9) {
		cerr << "Error parsing status line, expected at least 9 values, found " << matched << endl;
		cerr << statusrow << endl;
		return false;
	}
	int effects_found = matched - 9;
	for (int e = 0; e < effects_found; ++e) {
		if (strcmp(effects[e], "Burdened") == 0) {
			encumbrance = BURDENED;
		} else if (strcmp(effects[e], "Stressed") == 0) {
			encumbrance = STRESSED;
		} else if (strcmp(effects[e], "Strained") == 0) {
			encumbrance = STRAINED;
		} else if (strcmp(effects[e], "Overtaxed") == 0) {
			encumbrance = OVERTAXED;
		} else if (strcmp(effects[e], "Overloaded") == 0) {
			encumbrance = OVERLOADED;
		} else if (strcmp(effects[e], "Fainting") == 0) {
			hunger = FAINTING;
		} else if (strcmp(effects[e], "Weak") == 0) {
			hunger = WEAK;
		} else if (strcmp(effects[e], "Hungry") == 0) {
			hunger = HUNGRY;
		} else if (strcmp(effects[e], "Satiated") == 0) {
			hunger = SATIATED;
		} else if (strcmp(effects[e], "Oversatiated") == 0) {
			hunger = OVERSATIATED;
		} else if (strcmp(effects[e], "Blind") == 0) {
			blind = true;
		} else if (strcmp(effects[e], "Conf") == 0) {
			confused = true;
		} else if (strcmp(effects[e], "FoodPois") == 0) {
			foodpoisoned = true;
		} else if (strcmp(effects[e], "Hallu") == 0) {
			hallucinating = true;
		} else if (strcmp(effects[e], "Ill") == 0) {
			ill = true;
		} else if (strcmp(effects[e], "Slime") == 0) {
			slimed = true;
		} else if (strcmp(effects[e], "Stun") == 0) {
			stunned = true;
		}
	}
	return true;
}
