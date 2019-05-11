MCP_CAN CAN0(10);     // Set CS to pin 10


void InicializeCAN() {


	if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized!");
	else Serial.println("Error Initializing MCP2515...");

	CAN0.setMode(MCP_NORMAL); 
}



void SendCAN(String ID, byte Byte0, byte Byte1, byte Byte2, byte Byte3, byte Byte4, byte Byte5, byte Byte6, byte Byte7)
{
	byte data[8] = { Byte0, Byte1, Byte2, Byte3, Byte4, Byte5, Byte6, Byte7 };

	byte sndStat = CAN0.sendMsgBuf(ID.toInt(), 0, 8, data);
	if (sndStat == CAN_OK) {
		LCDWriteLine(0, 5, " == ENVIADO ==");
	}
	else {
		LCDWriteLine(0, 5, " == ERROR ==");
	}
}




