#include "../log.h"

int main() {
	file_init();
	
	set_file_name("test_log.txt");
	log(false, LOG_INFO, "Informations....");
	log(false, LOG_WARNING, "This is soooo coooooooool!!!!");
	log(false, LOG_ERROR, "Uh oh... ", "This is big stuff now...");

	struct custom_log_level test_custom_log = {
		WHITE,
		"Test",
	};
	custom_log(false, test_custom_log, "This", " is", " just", " a", " test", ".");
	
	test_custom_log.color = BLUE;
	custom_log(false, test_custom_log, "This is yet another test :D");

	custom_log(true, test_custom_log, "This will be saved to a file");
}
