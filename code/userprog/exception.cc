// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
	int	type = kernel->machine->ReadRegister(2);
	int	val;
	int 	op1,op2;
	static	int	offset=0;
	static bool firstMet=1;	
    switch (which) {
	case SyscallException:
	    switch(type) {
		case SC_Halt:
		    DEBUG(dbgAddr, "Shutdown, initiated by user program.\n");
   		    kernel->interrupt->Halt();
		    break;
		case SC_PrintInt:
			val=kernel->machine->ReadRegister(4);
			cout << "Print integer:" <<val << endl;
			return;
			break;
/*		case SC_Exec:
			DEBUG(dbgAddr, "Exec\n");
			val = kernel->machine->ReadRegister(4);
			kernel->StringCopy(tmpStr, retVal, 1024);
			cout << "Exec: " << val << endl;
			val = kernel->Exec(val);
			kernel->machine->WriteRegister(2, val);
			return;
*/	
		case SC_ThreadYield:
			cout << "Call ThreadYield\n" ; 
			kernel->currentThread->Yield();	
			return;
			break;
		case SC_Exit:
			DEBUG(dbgAddr, "Program exit\n");
			val=kernel->machine->ReadRegister(4);
			cout << "return value:" << val << endl;
			kernel->currentThread->Finish();
			break;
		case SC_OSAdd:
			DEBUG(dbgFile,"Add" << kernel->machine->ReadRegister(4) <<"+" << kernel->machine->ReadRegister(5) << "\n");
				op1=(int)kernel->machine->ReadRegister(4);
				op2=(int)kernel->machine->ReadRegister(5);
				val = op1+op2;
				cout << val <<"\n";
				kernel->machine->WriteRegister(6,(int)val);
			DEBUG(dbShow,"Add returning with" <<val <<"\n");
			return ;
			break;
		case SC_Log:{
			cout << "-------------this is Log---------------" << endl;
			val = 61%26;
			char lowwer = 'a'+val;
			char upper ='A'+val;
			if(firstMet){
				if(kernel->fileSystem->Open("NachOS.log")!=NULL){
					kernel->fileSystem->Remove("NachOS.log");
				}
				kernel->fileSystem->Create("NachOS.log");
				
				
				cout <<"*****MY MAGIC NUMBER IS:"<< val << endl;
				
				cout <<"*****MY MAGIC LETTERS ARE: " <<  lowwer <<" " << upper << endl;
				
				firstMet=0;	
			}
			OpenFile *opened = kernel->fileSystem->Open("NachOS.log");
			cout <<"ascii of input is: "<< kernel->machine->ReadRegister(4)<<"(which is:"<<(char)kernel->machine->ReadRegister(4)<<")" << endl;
			offset = offset+opened->WriteAt("[B10815061_Log]",15,offset);
			//cout << "offset after writing [b10815061_Log] is : " << offset << endl;
			char tmp = (char)kernel->machine->ReadRegister(4);
			char* inputForWrite = &tmp;


			if(tmp == upper||tmp == lowwer){
				cout << "ERROR " << endl;
				offset=offset+opened->WriteAt("Error",5,offset);
			//	cout << "offset after writing Error is : " << offset << endl;
				 
			}
			else{
				offset = offset +opened->WriteAt(inputForWrite,1,offset);
			//	cout << "offset after writing inputForWrite is : "<<offset << endl;
				}			
			offset = offset + opened->WriteAt("\n",1,offset);
		
			//cout << "current offset = " << offset << endl;
			return;
			break;
			}
		default:
		    cerr << "Unexpected system call " << type << "\n";
 		    break;
	    }
	    break;
	case PageFaultException:
		/*    Page Fault Exception    */
	    break;
	default:
	    cerr << "Unexpected user mode exception" << which << "\n";
	    break;
    }
    cout << type << " touched the assertionfailed\n";
    ASSERTNOTREACHED();
}
