#include "syscall.h"
main(){
	PrintInt(88);
	ThreadYield();
	PrintInt(99);
}
