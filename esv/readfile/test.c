#include "node.h"



int main(void)
{
	init();
	FILE* fp = fopen("test.txt", "r");
	char* line = NULL;
	readFile(fp, line);
	TestGetType("strings.en.header");
	TestGetType("config.update.interval");
	GetInt("config.loglevel");
	GetString("strings.en.button_cancel");
	GetText("button_ok", "noa");
	Delete("strings.en");
	getchar();
}
