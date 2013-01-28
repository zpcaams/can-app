/******************************************************************************
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    fieldrobot  Copyright (C) 2013  ZhouPeng CAAMS	<zp_caams@163.com>

    @file can-app.c
    Xilinx Zynq CAN PS test app for ZED board.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/sockios.h>
#include <net/if.h>

int main(void)
{
	int s;
	struct sockaddr_can addr;
	struct can_frame frame;
	int nbytes;
	int i;
    struct ifreq ifr;

	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(s==-1){
		fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
		exit(1);
	}

    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr);

	bzero(&addr, sizeof(struct sockaddr_can));
    addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	bind(s, (struct sockaddr *)&addr, sizeof(addr));

	frame.can_id = 0x01;
	frame.can_dlc = 8;
	for (i=0;i<frame.can_dlc;i++){
		frame.data[i] = i;
	}

	for(i=0;i<1;i++){
		nbytes = write(s, &frame, sizeof(struct can_frame));
		if (nbytes < 0){
			fprintf(stderr, "raw write error:%s\n\a", strerror(errno));
			exit(1);
		}

		if(nbytes < sizeof(struct can_frame)){
			fprintf(stderr, "write incomplete CAN frame\n\a");
			exit(1);
		}
		sleep(1);
		printf("can frame sent %d\n", i);
	}

	sleep(1);
	nbytes = read(s, &frame, sizeof(struct can_frame));
	if (nbytes < 0){
		fprintf(stderr, "raw read error:%s\n\a", strerror(errno));
		exit(1);
	}

	if(nbytes < sizeof(struct can_frame)){
		fprintf(stderr, "read incomplete CAN frame\n\a");
		exit(1);
	}
	printf("Frame can_id:%d, can_dlc:%d\n", frame.can_id, frame.can_dlc);

	for (i=0;i<frame.can_dlc;i++){
		printf("Frame can_data%d: %d\n", i, frame.data[i]);
	}

	close(s);

	puts("Hello Can World!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
