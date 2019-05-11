int Contador = 0, ValorMenu = 0;;
bool CanClear = true, IsValid = false;
String ValorSerial = "";
void IncializeSerial() {

  Serial.begin(57600);
  Serial.flush();
  Serial.write("Serial Available\r\n");

}

void ReceiveSerialData() {

  char SerialData;
  if (Serial.available() != 0) {
    SerialData = Serial.read();


  if(SerialData != '\n'){

    if(CanClear == true){
          lcd.clear();
          CanClear = false;
    }

   //  LCDWriteLine(Contador, 0, String(SerialData));
	 ValorSerial += String(SerialData);
     Contador+= 7;

  }else{
    
    Serial.write(ValorSerial.c_str()); 
    Serial.println("");
    Contador = 0;
   // LCDWriteLine(Contador, 0, String(SerialData));
    CanClear = true;
    ProcessData(ValorSerial);
      ValorSerial = "";
  }
  
  }
}

void ProcessData(String Data){
    IsValid = false;

    if(Data == "Send CAN") {
           lcd.clear();
           LCDWriteLine(0, 0, "===CANBUS-SEND==");
           LCDWriteLine(0, 1, "ID   => ");
           LCDWriteLine(0, 2, "DATA => ");
           ValorMenu = 1;
		   IsValid = true;
    }

	if (ValorMenu == 1) {
		lcd.clear();
		LCDWriteLine(0, 0, "===CANBUS-SEND==");
		LCDWriteLine(0, 1, "ID   => ");
		LCDWriteLine(0, 2, "DATA => ");

		String ID = Data.substring(0, 8);
		String Bytes[] = { "","","","","","","","" };
		Bytes[0] = Data.substring(9, 11);
		Bytes[1] = Data.substring(12, 14);
		Bytes[2] = Data.substring(15, 17);
		Bytes[3] = Data.substring(18, 20);
		Bytes[4] = Data.substring(21, 23);
		Bytes[5] = Data.substring(24, 26);
		Bytes[6] = Data.substring(27, 29);
		Bytes[7] = Data.substring(30, 32);

		LCDWriteLine(35, 1, ID.c_str());
		LCDWriteLine(35, 2, Bytes[0].c_str());
		LCDWriteLine(47, 2, Bytes[1].c_str());
		LCDWriteLine(59, 2, Bytes[2].c_str());
		LCDWriteLine(71, 2, Bytes[3].c_str());
		LCDWriteLine(35, 3, Bytes[4].c_str());
		LCDWriteLine(47, 3, Bytes[5].c_str());
		LCDWriteLine(59, 3, Bytes[6].c_str());
		LCDWriteLine(71, 3, Bytes[7].c_str());

		  SendCAN(ID, Bytes[0].toInt(), Bytes[1].toInt(), Bytes[2].toInt(), Bytes[3].toInt(), Bytes[4].toInt(), Bytes[5].toInt(), Bytes[6].toInt(), Bytes[7].toInt());
	}


	if (Data == "Menu") {
		lcd.clear();
		DrawLogo();
		ValorMenu = 0;
		IsValid = true;
	}

	if (Data == "Brilho") {
		lcd.clear();
		LCDWriteLine(0, 0, " ==SET-BRILHO==");
		ValorMenu = 2;
		IsValid = true;
	}
	if (ValorMenu == 2) {

		float ValorBrilho = Data.toInt();
		float Valor;

		Valor = ((ValorBrilho / 100) * 255);
		analogWrite(8, Valor);
		Serial.println(Valor);
		lcd.clear();
		LCDWriteLine(0, 0, " ==SET-BRILHO==");
		LCDWriteLine(0, 2, " BRILHO => ");
		LCDWriteLine(37, 2, String(ValorBrilho));
		ValorMenu = 2;
		IsValid = true;

	}


	if (ValorMenu == 0 && IsValid == false) {
		lcd.clear();
		LCDWriteLine(0, 2, " =COMMAND-ERROR= ");
		delay(1000);
		lcd.clear();
		DrawLogo();
		ValorMenu = 0;
	}
}








