#include "ns.h"
#include <inc/lib.h>

extern union Nsipc nsipcbuf;

void
input(envid_t ns_envid)
{
	binaryname = "ns_input";

	// LAB 6: Your code here:
	// 	- read a packet from the device driver
	//	- send it to the network server
	// Hint: When you IPC a page to the network server, it will be
	// reading from it for a while, so don't immediately receive
	// another packet in to the same physical page.
	
	char buffer[1518];
	int length;

	while(1)
	{
		while((length=sys_net_try_recv(buffer)) < 0)
		{

		}

		nsipcbuf.pkt.jp_len=length;
		memmove((void *)nsipcbuf.pkt.jp_data, (void *)buffer, length);

		ipc_send(ns_envid, NSREQ_INPUT, &nsipcbuf, PTE_P|PTE_U|PTE_W);

		sys_yield();
		sys_yield();
		sys_yield();
	}
}
