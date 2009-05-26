#ifndef FIGHT_H
#define FIGHT_H

#include <set>
#include <string>
#include "Analyzer.h"

#define PRIORITY_FIGHT_ENGULFED 200

namespace event {
	class Event;
}

class Monster;

namespace analyzer {
	class Fight : public Analyzer {
	public:
		Fight();

		void analyze();
		void onEvent(event::Event *const event);

	private:
		std::set<std::string> projectiles; // weapons we can throw
		std::set<unsigned char> projectile_slots; // slots where we got weapons we should throw
	};
}
#endif
