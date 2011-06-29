// narly_tester.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "dll_all.h"
#include "dll_seh_aslr.h"
#include "dll_seh_dep.h"
#include "dll_safeseh_gs.h"

int main()
{
	printf("called function in dll with: %s turned on\n", narly_testing::SehAslr::A());
	printf("called function in dll with: %s turned on\n", narly_testing::SehDep::A());
	printf("called function in dll with: %s turned on\n", narly_testing::SafeSehGs::A());
	printf("called function in dll with: %s turned on\n", narly_testing::All::A());

	__asm{
		int 3
	}

	return 0;
}