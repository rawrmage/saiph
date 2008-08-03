#ifndef ELBERETH_H
/* defines */
#define ELBERETH_H
/* messages */
#define ELBERETH_BURNED_TEXT "  Some text has been burned into the floor here.  "
#define ELBERETH_DIGGED_TEXT "  Something is engraved here on the floor.  "
#define ELBERETH_DUSTED_TEXT "  Something is written here in the dust.  "
#define ELBERETH_YOU_READ "  You read:"
/* Elbereth */
#define ELBERETH "Elbereth"

/* forward declare */
class Elbereth;

/* includes */
#include <string>
#include "../Analyzer.h"
#include "../Globals.h"
#include "../Request.h"
#include "../Saiph.h"

/* namespace */
using namespace std;

/* monitors health */
class Elbereth : public Analyzer {
	public:
		/* constructors */
		Elbereth(Saiph *saiph);

		/* methods */
		void parseMessages(const string &messages);
		bool request(const Request &request);

	private:
		/* variables */
		Saiph *saiph;
		int elbereth_count;
		bool burned;
		bool digged;
		bool dusted;
		bool did_look;
		bool append;
};
#endif
