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

    Xilinx Zynq CAN PS test app for ZED board.
    Main C code is written under eclipse.

	HOWTO use this demo
	1.(Hardware) 
		another can device is required for this demo,
		connect it to zynq with can phy.
	2.(Software) 
		build your bitstream file with can0 enable,
		route the can_tx can_rx to mio/emio, then to a can phy.

		build new BOOT.BIN, recompile linux kernel with NFS file
		system is a good choice for debugging.
		
		follow and modify the command in ZedSetup, 
		I hope that is clear for most linux user :)

******************************************************************************/
