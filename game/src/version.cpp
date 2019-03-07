#include <stdio.h>

void WriteVersion()
{
#ifndef __WIN32__
	FILE* fp = fopen("CMake-Version.txt", "w");

	if (fp)
	{
		fprintf(fp, "[VANILLA-CMake]r71480\n");
		fclose(fp);
	}
#endif
}

