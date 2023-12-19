#include "../log.h"

int main() {
	log(LOG_INFO, "Informations....");
	log(LOG_WARNING, "This is soooo coooooooool!!!!");
	log(LOG_ERROR, "Uh oh... ", "This is big stuff now...");

	struct custom_log_level test_custom_log = {
		WHITE,
		"Test",
	};
	custom_log(test_custom_log, "This", " is", " just", " a", " test", ".");
	
	test_custom_log.color = BLUE;
	custom_log(test_custom_log, "This is yet another test :D");
}