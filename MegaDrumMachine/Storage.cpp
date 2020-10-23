// 
// 
// 

#include "Storage.h"

uint32_t Storage::getAvailKits()
{
	String sfx = String(".kit");
	uint32_t kits = 0;
	if (SD.begin()) {
		for (int i = 0; i < 32; i++) {
			String fn = String(i, 10);
			fn = fn + sfx;
			if (SD.exists(fn)) {
				kits = kits | (0x01 << i);
			}
		}
	}
	SD.end();
	return kits;
}

bool Storage::saveKit(int kitSlot, DrumKit*kit)
{
	String sfx = String(".kit");
	String filename = String(kitSlot, 10) + sfx;
	if (SD.begin()) {
		if (SD.exists(filename)) {
			SD.remove(filename);
			File kitFile = SD.open(filename, FILE_WRITE);
			kitFile.write(SD_KIT_FILE_HEADER);
			char* conv;
			conv = (char*)kit;
			kitFile.write(conv, sizeof(DrumKit));
			kitFile.flush();
			kitFile.close();
		}
		SD.end();
	}
	return true;
}

DrumKit Storage::loadKit(byte kitSlot)
{
	String sfx = String(".kit");
	String filename = String(kitSlot, 10) + sfx;
	DrumKit kitBuffer;
	if (SD.begin()) {
		if (SD.exists(filename)) {
			File DrumKitInput = SD.open(filename);
			char* sBuff = SD_KIT_FILE_HEADER;
			bool header = true;
			for (int i = 0; i < 16; i++) {
				if (DrumKitInput.read() != sBuff[i]) {
					header = false;
				}
			}
			if (header) {
				DrumKitInput.readBytes((char*)&kitBuffer, sizeof(DrumKit));
			}
			DrumKitInput.close();
		}
		SD.end();
	}
	return kitBuffer;
}



