#include "tft.h"

#if (USE_HORIZONTAL == 0)
uint16_t st7789_width = 52;
uint16_t st7789_hight = 40;
#endif
#if (USE_HORIZONTAL == 1)
uint16_t st7789_width = 53;
uint16_t st7789_hight = 40;
#endif
#if (USE_HORIZONTAL == 2)
uint16_t st7789_width = 40;
uint16_t st7789_hight = 53;
#endif
#if (USE_HORIZONTAL == 3)
uint16_t st7789_width = 40;
uint16_t st7789_hight = 52;
#endif

int TFTDebugNumber = 0;
void lcdWriteRegisterWord(TFT_t * dev, uint16_t addr, uint16_t data)
{
	spi_master_write_comm_word(dev, addr);
	spi_master_write_data_word(dev, data);
}


void lcdWriteRegisterByte(TFT_t * dev, uint8_t addr, uint16_t data)
{
	spi_master_write_comm_byte(dev, addr);
	spi_master_write_data_word(dev, data);
}

void lcdInit(TFT_t * dev, uint16_t model, int width, int height, int offsetx, int offsety)
{
	dev->_model = model;
	dev->_width = width;
	dev->_height = height;
	dev->_offsetx = offsetx;
	dev->_offsety = offsety;
	dev->_font_direction = DIRECTION0;
	dev->_font_fill = false;
	dev->_font_underline = false;

	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735) {
		if (dev->_model == 0x9340)
			ESP_LOGI(TAG,"Your TFT is ILI9340");
		if (dev->_model == 0x9341)
			ESP_LOGI(TAG,"Your TFT is ILI9341");
		if (dev->_model == 0x7735)
			ESP_LOGI(TAG,"Your TFT is ST7735");
		ESP_LOGI(TAG,"Screen width:%d",width);
		ESP_LOGI(TAG,"Screen height:%d",height);
		spi_master_write_comm_byte(dev, 0xC0);	//Power Control 1
		spi_master_write_data_byte(dev, 0x23);

		spi_master_write_comm_byte(dev, 0xC1);	//Power Control 2
		spi_master_write_data_byte(dev, 0x10);
	
		spi_master_write_comm_byte(dev, 0xC5);	//VCOM Control 1
		spi_master_write_data_byte(dev, 0x3E);
		spi_master_write_data_byte(dev, 0x28);
	
		spi_master_write_comm_byte(dev, 0xC7);	//VCOM Control 2
		spi_master_write_data_byte(dev, 0x86);

		spi_master_write_comm_byte(dev, 0x36);	//Memory Access Control
		spi_master_write_data_byte(dev, 0x08);	//Right top start, BGR color filter panel
		//spi_master_write_data_byte(dev, 0x00);//Right top start, RGB color filter panel

		spi_master_write_comm_byte(dev, 0x3A);	//Pixel Format Set
		spi_master_write_data_byte(dev, 0x55);	//65K color: 16-bit/pixel

		spi_master_write_comm_byte(dev, 0x20);	//Display Inversion OFF

		spi_master_write_comm_byte(dev, 0xB1);	//Frame Rate Control
		spi_master_write_data_byte(dev, 0x00);
		spi_master_write_data_byte(dev, 0x18);

		spi_master_write_comm_byte(dev, 0xB6);	//Display Function Control
		spi_master_write_data_byte(dev, 0x08);
		spi_master_write_data_byte(dev, 0xA2);	// REV:1 GS:0 SS:0 SM:0
		spi_master_write_data_byte(dev, 0x27);
		spi_master_write_data_byte(dev, 0x00);

		spi_master_write_comm_byte(dev, 0x26);	//Gamma Set
		spi_master_write_data_byte(dev, 0x01);

		spi_master_write_comm_byte(dev, 0xE0);	//Positive Gamma Correction
		spi_master_write_data_byte(dev, 0x0F);
		spi_master_write_data_byte(dev, 0x31);
		spi_master_write_data_byte(dev, 0x2B);
		spi_master_write_data_byte(dev, 0x0C);
		spi_master_write_data_byte(dev, 0x0E);
		spi_master_write_data_byte(dev, 0x08);
		spi_master_write_data_byte(dev, 0x4E);
		spi_master_write_data_byte(dev, 0xF1);
		spi_master_write_data_byte(dev, 0x37);
		spi_master_write_data_byte(dev, 0x07);
		spi_master_write_data_byte(dev, 0x10);
		spi_master_write_data_byte(dev, 0x03);
		spi_master_write_data_byte(dev, 0x0E);
		spi_master_write_data_byte(dev, 0x09);
		spi_master_write_data_byte(dev, 0x00);

		spi_master_write_comm_byte(dev, 0xE1);	//Negative Gamma Correction
		spi_master_write_data_byte(dev, 0x00);
		spi_master_write_data_byte(dev, 0x0E);
		spi_master_write_data_byte(dev, 0x14);
		spi_master_write_data_byte(dev, 0x03);
		spi_master_write_data_byte(dev, 0x11);
		spi_master_write_data_byte(dev, 0x07);
		spi_master_write_data_byte(dev, 0x31);
		spi_master_write_data_byte(dev, 0xC1);
		spi_master_write_data_byte(dev, 0x48);
		spi_master_write_data_byte(dev, 0x08);
		spi_master_write_data_byte(dev, 0x0F);
		spi_master_write_data_byte(dev, 0x0C);
		spi_master_write_data_byte(dev, 0x31);
		spi_master_write_data_byte(dev, 0x36);
		spi_master_write_data_byte(dev, 0x0F);

		spi_master_write_comm_byte(dev, 0x11);	//Sleep Out
		delayMS(120);

		spi_master_write_comm_byte(dev, 0x29);	//Display ON
	} // endif 0x9340/0x9341/0x7735
	if (dev->_model == 0x7789) {
		ESP_LOGI(TAG,"Your TFT is ST7789V");
		ESP_LOGI(TAG,"Screen width:%d",width);
		ESP_LOGI(TAG,"Screen height:%d",height);
		spi_master_write_comm_byte(dev, 0x36);	//Memory Data Access Control, MX=MV=1, MY=ML=MH=0, RGB=0
		if(USE_HORIZONTAL==0)spi_master_write_data_byte(dev, 0x00);
		else if(USE_HORIZONTAL==1)spi_master_write_data_byte(dev, 0xC0);
		else if(USE_HORIZONTAL==2)spi_master_write_data_byte(dev, 0x70);
		else spi_master_write_data_byte(dev, 0xA0);

		spi_master_write_comm_byte(dev, 0x3A);	//Interface Pixel Format, 16bits/pixel for RGB/MCU interface
		spi_master_write_data_byte(dev, 0x05);
	
		spi_master_write_comm_byte(dev, 0xB2);	//Porch Setting
		spi_master_write_data_byte(dev, 0x0c);
		spi_master_write_data_byte(dev, 0x0c);
		spi_master_write_data_byte(dev, 0x00);
		spi_master_write_data_byte(dev, 0x33);
		spi_master_write_data_byte(dev, 0x33);
	
		spi_master_write_comm_byte(dev, 0xB7);	//Gate Control, Vgh=13.65V, Vgl=-10.43V
		spi_master_write_data_byte(dev, 0x35);

		spi_master_write_comm_byte(dev, 0xBB);	//VCOM Setting, VCOM=1.175V
		spi_master_write_data_byte(dev, 0x19);	

		spi_master_write_comm_byte(dev, 0xC0);	//LCM Control, XOR: BGR, MX, MH
		spi_master_write_data_byte(dev, 0x2C);	

		spi_master_write_comm_byte(dev, 0xC2);	//VDV and VRH Command Enable, enable=1
		spi_master_write_data_byte(dev, 0x01);

		spi_master_write_comm_byte(dev, 0xC3);	//VRH Set, Vap=4.4+...
		spi_master_write_data_byte(dev, 0x12);

		spi_master_write_comm_byte(dev, 0xC4);	//VDV Set, VDV=0
		spi_master_write_data_byte(dev, 0x20);

		spi_master_write_comm_byte(dev, 0xC6);	//Frame Rate Control, 60Hz, inversion=0
		spi_master_write_data_byte(dev, 0x0f);

		spi_master_write_comm_byte(dev, 0xD0);	//Power Control 1, AVDD=6.8V, AVCL=-4.8V, VDDS=2.3V
		spi_master_write_data_byte(dev, 0xA4);
		spi_master_write_data_byte(dev, 0xA1);

		spi_master_write_comm_byte(dev, 0xE0);	//Positive Gamma Correction
		spi_master_write_data_byte(dev, 0xD0);
		spi_master_write_data_byte(dev, 0x04);
		spi_master_write_data_byte(dev, 0x0D);
		spi_master_write_data_byte(dev, 0x11);
		spi_master_write_data_byte(dev, 0x13);
		spi_master_write_data_byte(dev, 0x2B);
		spi_master_write_data_byte(dev, 0x3F);
		spi_master_write_data_byte(dev, 0x54);
		spi_master_write_data_byte(dev, 0x4C);
		spi_master_write_data_byte(dev, 0x18);
		spi_master_write_data_byte(dev, 0x0D);
		spi_master_write_data_byte(dev, 0x0B);
		spi_master_write_data_byte(dev, 0x1F);
		spi_master_write_data_byte(dev, 0x23);

		spi_master_write_comm_byte(dev, 0xE1);	//Negative Gamma Correction
		spi_master_write_data_byte(dev, 0xD0);
		spi_master_write_data_byte(dev, 0x04);
		spi_master_write_data_byte(dev, 0x0C);
		spi_master_write_data_byte(dev, 0x11);
		spi_master_write_data_byte(dev, 0x13);
		spi_master_write_data_byte(dev, 0x2C);
		spi_master_write_data_byte(dev, 0x3F);
		spi_master_write_data_byte(dev, 0x44);
		spi_master_write_data_byte(dev, 0x51);
		spi_master_write_data_byte(dev, 0x2F);
		spi_master_write_data_byte(dev, 0x1F);
		spi_master_write_data_byte(dev, 0x1F);
		spi_master_write_data_byte(dev, 0x20);
		spi_master_write_data_byte(dev, 0x23);
		
		spi_master_write_comm_byte(dev, 0x21);	//Sleep Out
		delayMS(120);

		spi_master_write_comm_byte(dev, 0x11);	//Sleep Out
		delayMS(120);

		spi_master_write_comm_byte(dev, 0x29);	//Display ON
		delayMS(120);
	} // endif 0X7789

	if (dev->_model == 0x9225) {
		ESP_LOGI(TAG,"Your TFT is ILI9225");
		ESP_LOGI(TAG,"Screen width:%d",width);
		ESP_LOGI(TAG,"Screen height:%d",height);
		lcdWriteRegisterByte(dev, 0x10, 0x0000); // Set SAP,DSTB,STB
		lcdWriteRegisterByte(dev, 0x11, 0x0000); // Set APON,PON,AON,VCI1EN,VC
		lcdWriteRegisterByte(dev, 0x12, 0x0000); // Set BT,DC1,DC2,DC3
		lcdWriteRegisterByte(dev, 0x13, 0x0000); // Set GVDD
		lcdWriteRegisterByte(dev, 0x14, 0x0000); // Set VCOMH/VCOML voltage
		delayMS(40);

		// Power-on sequence
		lcdWriteRegisterByte(dev, 0x11, 0x0018); // Set APON,PON,AON,VCI1EN,VC
		lcdWriteRegisterByte(dev, 0x12, 0x6121); // Set BT,DC1,DC2,DC3
		lcdWriteRegisterByte(dev, 0x13, 0x006F); // Set GVDD
		lcdWriteRegisterByte(dev, 0x14, 0x495F); // Set VCOMH/VCOML voltage
		lcdWriteRegisterByte(dev, 0x10, 0x0800); // Set SAP,DSTB,STB
		delayMS(10);
		lcdWriteRegisterByte(dev, 0x11, 0x103B); // Set APON,PON,AON,VCI1EN,VC
		delayMS(50);

		lcdWriteRegisterByte(dev, 0x01, 0x011C); // set the display line number and display direction
		lcdWriteRegisterByte(dev, 0x02, 0x0100); // set 1 line inversion
		lcdWriteRegisterByte(dev, 0x03, 0x1030); // set GRAM write direction and BGR=1.
		lcdWriteRegisterByte(dev, 0x07, 0x0000); // Display off
		lcdWriteRegisterByte(dev, 0x08, 0x0808); // set the back porch and front porch
		lcdWriteRegisterByte(dev, 0x0B, 0x1100); // set the clocks number per line
		lcdWriteRegisterByte(dev, 0x0C, 0x0000); // CPU interface
		//lcdWriteRegisterByte(dev, 0x0F, 0x0D01); // Set Osc
		lcdWriteRegisterByte(dev, 0x0F, 0x0801); // Set Osc
		lcdWriteRegisterByte(dev, 0x15, 0x0020); // Set VCI recycling
		lcdWriteRegisterByte(dev, 0x20, 0x0000); // RAM Address
		lcdWriteRegisterByte(dev, 0x21, 0x0000); // RAM Address

		// Set GRAM area
		lcdWriteRegisterByte(dev, 0x30, 0x0000);
		lcdWriteRegisterByte(dev, 0x31, 0x00DB);
		lcdWriteRegisterByte(dev, 0x32, 0x0000);
		lcdWriteRegisterByte(dev, 0x33, 0x0000);
		lcdWriteRegisterByte(dev, 0x34, 0x00DB);
		lcdWriteRegisterByte(dev, 0x35, 0x0000);
		lcdWriteRegisterByte(dev, 0x36, 0x00AF);
		lcdWriteRegisterByte(dev, 0x37, 0x0000);
		lcdWriteRegisterByte(dev, 0x38, 0x00DB);
		lcdWriteRegisterByte(dev, 0x39, 0x0000);

		// Adjust GAMMA Curve
		lcdWriteRegisterByte(dev, 0x50, 0x0000);
		lcdWriteRegisterByte(dev, 0x51, 0x0808);
		lcdWriteRegisterByte(dev, 0x52, 0x080A);
		lcdWriteRegisterByte(dev, 0x53, 0x000A);
		lcdWriteRegisterByte(dev, 0x54, 0x0A08);
		lcdWriteRegisterByte(dev, 0x55, 0x0808);
		lcdWriteRegisterByte(dev, 0x56, 0x0000);
		lcdWriteRegisterByte(dev, 0x57, 0x0A00);
		lcdWriteRegisterByte(dev, 0x58, 0x0710);
		lcdWriteRegisterByte(dev, 0x59, 0x0710);

		lcdWriteRegisterByte(dev, 0x07, 0x0012);
		delayMS(50); // Delay 50ms
		lcdWriteRegisterByte(dev, 0x07, 0x1017);
	} // endif 0x9225

	if (dev->_model == 0x9226) {
		ESP_LOGI(TAG,"Your TFT is ILI9225G");
		ESP_LOGI(TAG,"Screen width:%d",width);
		ESP_LOGI(TAG,"Screen height:%d",height);
		//lcdWriteRegisterByte(dev, 0x01, 0x011c);
		lcdWriteRegisterByte(dev, 0x01, 0x021c);
		lcdWriteRegisterByte(dev, 0x02, 0x0100);
		lcdWriteRegisterByte(dev, 0x03, 0x1030);
		lcdWriteRegisterByte(dev, 0x08, 0x0808); // set BP and FP
		lcdWriteRegisterByte(dev, 0x0B, 0x1100); // frame cycle
		lcdWriteRegisterByte(dev, 0x0C, 0x0000); // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
		lcdWriteRegisterByte(dev, 0x0F, 0x1401); // Set frame rate----0801
		lcdWriteRegisterByte(dev, 0x15, 0x0000); // set system interface
		lcdWriteRegisterByte(dev, 0x20, 0x0000); // Set GRAM Address
		lcdWriteRegisterByte(dev, 0x21, 0x0000); // Set GRAM Address
		//*************Power On sequence ****************//
		delayMS(50);
		lcdWriteRegisterByte(dev, 0x10, 0x0800); // Set SAP,DSTB,STB----0A00
		lcdWriteRegisterByte(dev, 0x11, 0x1F3F); // Set APON,PON,AON,VCI1EN,VC----1038
		delayMS(50);
		lcdWriteRegisterByte(dev, 0x12, 0x0121); // Internal reference voltage= Vci;----1121
		lcdWriteRegisterByte(dev, 0x13, 0x006F); // Set GVDD----0066
		lcdWriteRegisterByte(dev, 0x14, 0x4349); // Set VCOMH/VCOML voltage----5F60
		//-------------- Set GRAM area -----------------//
		lcdWriteRegisterByte(dev, 0x30, 0x0000);
		lcdWriteRegisterByte(dev, 0x31, 0x00DB);
		lcdWriteRegisterByte(dev, 0x32, 0x0000);
		lcdWriteRegisterByte(dev, 0x33, 0x0000);
		lcdWriteRegisterByte(dev, 0x34, 0x00DB);
		lcdWriteRegisterByte(dev, 0x35, 0x0000);
		lcdWriteRegisterByte(dev, 0x36, 0x00AF);
		lcdWriteRegisterByte(dev, 0x37, 0x0000);
		lcdWriteRegisterByte(dev, 0x38, 0x00DB);
		lcdWriteRegisterByte(dev, 0x39, 0x0000);
		// ----------- Adjust the Gamma Curve ----------//
		lcdWriteRegisterByte(dev, 0x50, 0x0001);
		lcdWriteRegisterByte(dev, 0x51, 0x200B);
		lcdWriteRegisterByte(dev, 0x52, 0x0000);
		lcdWriteRegisterByte(dev, 0x53, 0x0404);
		lcdWriteRegisterByte(dev, 0x54, 0x0C0C);
		lcdWriteRegisterByte(dev, 0x55, 0x000C);
		lcdWriteRegisterByte(dev, 0x56, 0x0101);
		lcdWriteRegisterByte(dev, 0x57, 0x0400);
		lcdWriteRegisterByte(dev, 0x58, 0x1108);
		lcdWriteRegisterByte(dev, 0x59, 0x050C);
		delayMS(50);
		lcdWriteRegisterByte(dev, 0x07,0x1017);
	} // endif 0x9226

	if(dev->_bl >= 0) {
		gpio_set_level( dev->_bl, 1 );
	}
}

// Draw pixel
// x:X coordinate
// y:Y coordinate
// color:color
void lcdDrawPixel(TFT_t * dev, uint16_t x, uint16_t y, uint16_t color){
	if (x >= dev->_width) return;
	if (y >= dev->_height) return;

	uint16_t _x = x + dev->_offsetx;
	uint16_t _y = y + dev->_offsety;

	//if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_addr(dev, _x, _x);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_addr(dev, _y, _y);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		spi_master_write_data_word(dev, color);
	} // endif 0x9340/0x9341

	if (dev->_model == 0x7735) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_data_word(dev, _x);
		spi_master_write_data_word(dev, _x);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_data_word(dev, _y);
		spi_master_write_data_word(dev, _y);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		spi_master_write_data_word(dev, color);
	} // endif 0x7735
	if (dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_data_word(dev, _x+st7789_width);
		spi_master_write_data_word(dev, _x+st7789_width);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_data_word(dev, _y+st7789_hight);
		spi_master_write_data_word(dev, _y+st7789_hight);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		spi_master_write_data_word(dev, color);
	} // endif 0x7789

	if (dev->_model == 0x9225) {
		lcdWriteRegisterByte(dev, 0x20, _x);
		lcdWriteRegisterByte(dev, 0x21, _y);
		spi_master_write_comm_byte(dev, 0x22);	// Memory Write
		spi_master_write_data_word(dev, color);
	} // endif 0x9225

	if (dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x36, _x);
		lcdWriteRegisterByte(dev, 0x37, _x);
		lcdWriteRegisterByte(dev, 0x38, _y);
		lcdWriteRegisterByte(dev, 0x39, _y);
		lcdWriteRegisterByte(dev, 0x20, _x);
		lcdWriteRegisterByte(dev, 0x21, _y); 
		spi_master_write_comm_byte(dev, 0x22);             
		spi_master_write_data_word(dev, color);
	} // endif 0x9226
}

// Add 202001
// Draw multi pixel
// x:X coordinate
// y:Y coordinate
// size:Number of colors
// colors:colors
void lcdDrawMultiPixels(TFT_t * dev, uint16_t x, uint16_t y, uint16_t size, uint16_t * colors) {
    if (x+size > dev->_width) return;
    if (y >= dev->_height) return;

    ESP_LOGD(TAG,"offset(x)=%d offset(y)=%d",dev->_offsetx,dev->_offsety);
    uint16_t _x1 = x + dev->_offsetx;
    uint16_t _x2 = _x1 + size;
    uint16_t _y1 = y + dev->_offsety;
    uint16_t _y2 = _y1;
    ESP_LOGD(TAG,"_x1=%d _x2=%d _y1=%d _y2=%d",_x1, _x2, _y1, _y2);

    //if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735) {
    if (dev->_model == 0x9340 || dev->_model == 0x9341) {
        spi_master_write_comm_byte(dev, 0x2A);  // set column(x) address
        spi_master_write_addr(dev, _x1, _x2);
        spi_master_write_comm_byte(dev, 0x2B);  // set Page(y) address
        spi_master_write_addr(dev, _y1, _y2);
        spi_master_write_comm_byte(dev, 0x2C);  //  Memory Write
        spi_master_write_colors(dev, colors, size);
    } // endif 0x9340/0x9341

    if (dev->_model == 0x7735) {
        spi_master_write_comm_byte(dev, 0x2A);  // set column(x) address
        spi_master_write_data_word(dev, _x1);
        spi_master_write_data_word(dev, _x2);
        spi_master_write_comm_byte(dev, 0x2B);  // set Page(y) address
        spi_master_write_data_word(dev, _y1);
        spi_master_write_data_word(dev, _y2);
        spi_master_write_comm_byte(dev, 0x2C);  //  Memory Write
        spi_master_write_colors(dev, colors, size);
    } // 0x7735
    if (dev->_model == 0x7789) {
        spi_master_write_comm_byte(dev, 0x2A);  // set column(x) address
        spi_master_write_data_word(dev, _x1+st7789_width);
        spi_master_write_data_word(dev, _x2+st7789_width);
        spi_master_write_comm_byte(dev, 0x2B);  // set Page(y) address
        spi_master_write_data_word(dev, _y1+st7789_hight);
        spi_master_write_data_word(dev, _y2+st7789_hight);
        spi_master_write_comm_byte(dev, 0x2C);  //  Memory Write
        spi_master_write_colors(dev, colors, size);
    } // 0x77389

    if (dev->_model == 0x9225) {
        for(int j=_y1;j<=_y2;j++){
            lcdWriteRegisterByte(dev, 0x20, _x1);
            lcdWriteRegisterByte(dev, 0x21, j);
            spi_master_write_comm_byte(dev, 0x22);  // Memory Write
            spi_master_write_colors(dev, colors, size);
        }
    } // endif 0x9225

    if (dev->_model == 0x9226) {
        for(int j=_x1;j<=_x2;j++) {
            lcdWriteRegisterByte(dev, 0x36, j);
            lcdWriteRegisterByte(dev, 0x37, j);
            lcdWriteRegisterByte(dev, 0x38, _y2);
            lcdWriteRegisterByte(dev, 0x39, _y1);
            lcdWriteRegisterByte(dev, 0x20, j);
            lcdWriteRegisterByte(dev, 0x21, _y1);
            spi_master_write_comm_byte(dev, 0x22);
            spi_master_write_colors(dev, colors, size);
        }
    } // endif 0x9226

}
//专门为lvgl写的

void lcdDrawMultiPixels_lvgl(TFT_t * dev, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t * colors) {
	// if (x2 >= dev->_width) return;
	// if (y2 >= dev->_height) return;

	uint16_t n = 0;


    if(TFTDebug)printf("[TFTDebug]:x1:%d\tx2:%d\ty1:%d\ty2:%d\t\n",x1, x2, y1, y2);
	//if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_addr(dev, x1, x2);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_addr(dev, y1, y2);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		for (int i = 0; i < x2-x1+1; ++i)
		{
			// for (int j = 0; j < y2-y1+1; ++j)
			// {
			// 	spi_master_write_data_word(dev, colors[(i+1)*j]);
			// }
			uint16_t size = y2-y1+1;
			spi_master_write_colors(dev, colors+size*i, size);
		}
		// spi_master_write_data_word(dev, color);
	} // endif 0x9340/0x9341

	// if (dev->_model == 0x7735) {
	// 	spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
	// 	spi_master_write_data_word(dev, _x);
	// 	spi_master_write_data_word(dev, _x);
	// 	spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
	// 	spi_master_write_data_word(dev, _y);
	// 	spi_master_write_data_word(dev, _y);
	// 	spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
	// 	spi_master_write_data_word(dev, color);
	// } // endif 0x7735

	// if (dev->_model == 0x9225) {
	// 	lcdWriteRegisterByte(dev, 0x20, _x);
	// 	lcdWriteRegisterByte(dev, 0x21, _y);
	// 	spi_master_write_comm_byte(dev, 0x22);	// Memory Write
	// 	spi_master_write_data_word(dev, color);
	// } // endif 0x9225

	// if (dev->_model == 0x9226) {
	// 	lcdWriteRegisterByte(dev, 0x36, _x);
	// 	lcdWriteRegisterByte(dev, 0x37, _x);
	// 	lcdWriteRegisterByte(dev, 0x38, _y);
	// 	lcdWriteRegisterByte(dev, 0x39, _y);
	// 	lcdWriteRegisterByte(dev, 0x20, _x);
	// 	lcdWriteRegisterByte(dev, 0x21, _y); 
	// 	spi_master_write_comm_byte(dev, 0x22);             
	// 	spi_master_write_data_word(dev, color);
	// } // endif 0x9226
}



// Draw rectangle of filling
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End X coordinate
// y2:End Y coordinate
// color:color
void lcdDrawFillRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	if (x1 >= dev->_width) return;
	if (x2 >= dev->_width) x2=dev->_width-1;
	if (y1 >= dev->_height) return;
	if (y2 >= dev->_height) y2=dev->_height-1;

	ESP_LOGD(TAG,"offset(x)=%d offset(y)=%d",dev->_offsetx,dev->_offsety);
	uint16_t _x1 = x1 + dev->_offsetx;
	uint16_t _x2 = x2 + dev->_offsetx;
	uint16_t _y1 = y1 + dev->_offsety;
	uint16_t _y2 = y2 + dev->_offsety;

	//if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_addr(dev, _x1, _x2);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_addr(dev, _y1, _y2);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		for(int i=_x1;i<=_x2;i++) {
			uint16_t size = _y2-_y1+1;
			spi_master_write_color(dev, color, size);
		}
	} // endif 0x9340/0x9341

	if (dev->_model == 0x7735) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_data_word(dev, _x1);
		spi_master_write_data_word(dev, _x2);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_data_word(dev, _y1);
		spi_master_write_data_word(dev, _y2);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		for(int i=_x1;i<=_x2;i++) {
			uint16_t size = _y2-_y1+1;
			spi_master_write_color(dev, color, size);
		}
	} // 0x7735
	if (dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x2A);	// set column(x) address
		spi_master_write_data_word(dev, _x1+st7789_width);
		spi_master_write_data_word(dev, _x2+st7789_width);
		spi_master_write_comm_byte(dev, 0x2B);	// set Page(y) address
		spi_master_write_data_word(dev, _y1+st7789_hight);
		spi_master_write_data_word(dev, _y2+st7789_hight);
		spi_master_write_comm_byte(dev, 0x2C);	//  Memory Write
		for(int i=_x1;i<=_x2;i++) {
			uint16_t size = _y2-_y1+1;
			spi_master_write_color(dev, color, size);
		}
	} // 0x7789

	if (dev->_model == 0x9225) {
		for(int j=_y1;j<=_y2;j++){
			lcdWriteRegisterByte(dev, 0x20, _x1);
			lcdWriteRegisterByte(dev, 0x21, j);
			spi_master_write_comm_byte(dev, 0x22);	// Memory Write
			uint16_t size = _x2-_x1+1;
			spi_master_write_color(dev, color, size);
		}
	} // endif 0x9225

	if (dev->_model == 0x9226) {
		for(int j=_x1;j<=_x2;j++) {
			lcdWriteRegisterByte(dev, 0x36, j);
			lcdWriteRegisterByte(dev, 0x37, j);
			lcdWriteRegisterByte(dev, 0x38, _y2);
			lcdWriteRegisterByte(dev, 0x39, _y1);
			lcdWriteRegisterByte(dev, 0x20, j);
			lcdWriteRegisterByte(dev, 0x21, _y1); 
			spi_master_write_comm_byte(dev, 0x22);             
			uint16_t size = _y2-_y1+1;
			spi_master_write_color(dev, color, size);
#if 0
			for(int i=_y1;i<=_y2;i++) {
				spi_master_write_data_word(dev, color);
			}
#endif
		}
	} // endif 0x9226

}

// Display OFF
void lcdDisplayOff(TFT_t * dev) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735 || dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x28);
	} // endif 0x9340/0x9341/0x7735

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x07, 0x1014);
	} // endif 0x9225/0x9226

}
 
// Display ON
void lcdDisplayOn(TFT_t * dev) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735 || dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x29);
	} // endif 0x9340/0x9341/0x7735

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x07, 0x1017);
	} // endif 0x9225/0x9226

}

// Display Inversion OFF
void lcdInversionOff(TFT_t * dev) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735 || dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x20);
	} // endif 0x9340/0x9341/0x7735

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x07, 0x1017);
	} // endif 0x9225/0x9226
}

// Display Inversion ON
void lcdInversionOn(TFT_t * dev) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735 || dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x21);
	} // endif 0x9340/0x9341/0x7735

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x07, 0x1013);
	} // endif 0x9225/0x9226
}

// Change Memory Access Control
void lcdBGRFilter(TFT_t * dev) {
	if (dev->_model == 0x9340 || dev->_model == 0x9341 || dev->_model == 0x7735 || dev->_model == 0x7789) {
		spi_master_write_comm_byte(dev, 0x36);	//Memory Access Control
		spi_master_write_data_byte(dev, 0x00);	//Right top start, RGB color filter panel
	} // endif 0x9340/0x9341/0x7735

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x03, 0x0030); // set GRAM write direction and BGR=0.
	} // endif 0x9225/0x9226
}
// Fill screen
// color:color
void lcdFillScreen(TFT_t * dev, uint16_t color) {
	lcdDrawFillRect(dev, 0, 0, dev->_width-1, dev->_height-1, color);
}

// Draw line
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End X coordinate
// y2:End Y coordinate
// color:color 
void lcdDrawLine(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	int i;
	int dx,dy;
	int sx,sy;
	int E;

	/* distance between two points */
	dx = ( x2 > x1 ) ? x2 - x1 : x1 - x2;
	dy = ( y2 > y1 ) ? y2 - y1 : y1 - y2;

	/* direction of two point */
	sx = ( x2 > x1 ) ? 1 : -1;
	sy = ( y2 > y1 ) ? 1 : -1;
	
	/* inclination < 1 */
	if ( dx > dy ) {
		E = -dx;
		for ( i = 0 ; i <= dx ; i++ ) {
			lcdDrawPixel(dev, x1, y1, color);
			x1 += sx;
			E += 2 * dy;
			if ( E >= 0 ) {
			y1 += sy;
			E -= 2 * dx;
		}
	}

	/* inclination >= 1 */
	} else {
		E = -dy;
		for ( i = 0 ; i <= dy ; i++ ) {
			lcdDrawPixel(dev, x1, y1, color);
			y1 += sy;
			E += 2 * dx;
			if ( E >= 0 ) {
				x1 += sx;
				E -= 2 * dy;
			}
		}
	}
}
/*
 * Draw line on screen from (x,y) point at given angle
 * Line drawing angle starts at lower right quadrant of the screen and is offseted by
 * '_angleOffset' global variable (default: -90 degrees)
 *
 * Params:
 *       x: horizontal start position
 *       y: vertical start position
 *   start: start offset from (x,y)
 *     len: length of the line
 *   angle: line angle in degrees
 *   color: line color
*/
//-----------------------------------------------------------------------------------------------------------
void TFTDrawLineByAngle(TFT_t * dev, uint16_t x, uint16_t y, uint16_t start, uint16_t len, uint16_t angle, uint16_t color)
{
	if (start == 0)
	{
		lcdDrawLine(
			dev,		
			x,
			y,
			x + len * cos((angle) * DEG_TO_RAD),
			y + len * sin((angle) * DEG_TO_RAD), 
			color);
	}
	else 
	{
		lcdDrawLine(
			dev,
			x + start * cos((angle) * DEG_TO_RAD),
			y + start * sin((angle) * DEG_TO_RAD),
			x + (start + len) * cos((angle) * DEG_TO_RAD),
			y + (start + len) * sin((angle) * DEG_TO_RAD), 
			color);
	}
}

// Draw rectangle
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// color:color
void lcdDrawRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	lcdDrawLine(dev, x1, y1, x2, y1, color);
	lcdDrawLine(dev, x2, y1, x2, y2, color);
	lcdDrawLine(dev, x2, y2, x1, y2, color);
	lcdDrawLine(dev, x1, y2, x1, y1, color);
}
// Fill rectangle
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// color:color
void lcdFillRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	if(TFTDebug)printf("[TFTDebug]：进入函数\n");
	int xx=0,yy=0;
	if(x1>x2)
	{
		xx = x1;
		x1 = x2;
		x2 = xx;
	}
	if(y1>y2)
	{
		yy = y1;
		y1 = y2;
		y2 = yy;
	}
	if(TFTDebug)printf("[TFTDebug]：开始画线\n");
	if(TFTDebug)printf("[TFTDebug]：x1：%d,y1:%d,x2:%d,y2%d\n",x1,y1,x2,y2);
	for (int i = 0; i < x2-x1; ++i)
	{
		lcdDrawLine(dev, x1+i, y1, x1 + i, y2, color);
	}
}

// Draw rectangle with angle
// xc:Center X coordinate
// yc:Center Y coordinate
// w:Width of rectangle
// h:Height of rectangle
// angle :Angle of rectangle
// color :color

//When the origin is (0, 0), the point (x1, y1) after rotating the point (x, y) by the angle is obtained by the following calculation.
// x1 = x * cos(angle) - y * sin(angle)
// y1 = x * sin(angle) + y * cos(angle)
void lcdDrawRectAngle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color) {
        double xd,yd,rd;
        int x1,y1;
        int x2,y2;
        int x3,y3;
        int x4,y4;
        rd = angle * M_PI / 180.0;
        xd = 0.0 - w/2;
        yd = h/2;
        x1 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y1 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        yd = 0.0 - yd;
        x2 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y2 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        xd = w/2;
        yd = h/2;
        x3 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y3 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        yd = 0.0 - yd;
        x4 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y4 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        lcdDrawLine(dev, x1, y1, x2, y2, color);
        lcdDrawLine(dev, x1, y1, x3, y3, color);
        lcdDrawLine(dev, x2, y2, x4, y4, color);
        lcdDrawLine(dev, x3, y3, x4, y4, color);
}


// Draw triangle
// xc:Center X coordinate
// yc:Center Y coordinate
// w:Width of triangle
// h:Height of triangle
// angle :Angle of triangle
// color :color

//When the origin is (0, 0), the point (x1, y1) after rotating the point (x, y) by the angle is obtained by the following calculation.
// x1 = x * cos(angle) - y * sin(angle)
// y1 = x * sin(angle) + y * cos(angle)
void lcdDrawTriangle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color) {
        double xd,yd,rd;
        int x1,y1;
        int x2,y2;
        int x3,y3;
        rd = -angle * M_PI / 180.0;
        xd = 0.0;
        yd = h/2;
        x1 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y1 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        xd = w/2;
        yd = 0.0 - yd;
        x2 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y2 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        xd = 0.0 - w/2;
        x3 = (int)(xd * cos(rd) - yd * sin(rd) + xc);
        y3 = (int)(xd * sin(rd) + yd * cos(rd) + yc);

        lcdDrawLine(dev, x1, y1, x2, y2, color);
        lcdDrawLine(dev, x1, y1, x3, y3, color);
        lcdDrawLine(dev, x2, y2, x3, y3, color);
}


// Draw circle
// x0:Central X coordinate
// y0:Central Y coordinate
// r:radius
// color:color
void lcdDrawCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
	int x;
	int y;
	int err;
	int old_err;

	x=0;
	y=-r;
	err=2-2*r;
	do{
		lcdDrawPixel(dev, x0-x, y0+y, color); 
		lcdDrawPixel(dev, x0-y, y0-x, color); 
		lcdDrawPixel(dev, x0+x, y0-y, color); 
		lcdDrawPixel(dev, x0+y, y0+x, color); 
		if ((old_err=err)<=x)   err+=++x*2+1;
		if (old_err>y || err>x) err+=++y*2+1;    
	} while(y<0);
}

// Draw circle of filling
// x0:Central X coordinate
// y0:Central Y coordinate
// r:radius
// color:color
void lcdFillCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
	int x;
	int y;
	int err;
	int old_err;
	int ChangeX;

	x=0;
	y=-r;
	err=2-2*r;
	ChangeX=1;
	do{
		if(ChangeX) {
			lcdDrawLine(dev, x0-x, y0-y, x0-x, y0+y, color);
			lcdDrawLine(dev, x0+x, y0-y, x0+x, y0+y, color);
		} // endif
		ChangeX=(old_err=err)<=x;
		if (ChangeX)            err+=++x*2+1;
		if (old_err>y || err>x) err+=++y*2+1;
	} while(y<=0);
} 

//----------------------------------------------------------------------------------------------------------------
static void _draw_ellipse_section(TFT_t * dev, uint16_t x, uint16_t y, uint16_t x0, uint16_t y0, uint16_t color, uint8_t option)
{
    // upper right
    if ( option & TFT_ELLIPSE_UPPER_RIGHT )	lcdDrawPixel(dev, x0 + x, y0 - y, color);
    // upper left
    if ( option & TFT_ELLIPSE_UPPER_LEFT ) 	lcdDrawPixel(dev, x0 - x, y0 - y, color);
    // lower right
    if ( option & TFT_ELLIPSE_LOWER_RIGHT )	lcdDrawPixel(dev, x0 + x, y0 + y, color);
    // lower left
    if ( option & TFT_ELLIPSE_LOWER_LEFT ) 	lcdDrawPixel(dev, x0 - x, y0 + y, color);
}
/*
 * Draw ellipse on screen
 * 
 * Params:
 *       x0: ellipse center x position
 *       y0: ellipse center x position
 *       rx: ellipse horizontal radius
 *       ry: ellipse vertical radius
 *   option: drawing options, multiple options can be combined
                1 (TFT_ELLIPSE_UPPER_RIGHT) draw upper right corner
                2 (TFT_ELLIPSE_UPPER_LEFT)  draw upper left corner
                4 (TFT_ELLIPSE_LOWER_LEFT)  draw lower left corner
                8 (TFT_ELLIPSE_LOWER_RIGHT) draw lower right corner
             to draw the whole ellipse use option value 15 (1 | 2 | 4 | 8)
 * 
 *   color: circle color
*/
//=====================================================================================================
void TFTDrawEllipse(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry, uint16_t color, uint8_t option)
{
	// x0 += dispWin.x1;
	// y0 += dispWin.y1;

	uint16_t x, y;
	int32_t xchg, ychg;
	int32_t err;
	int32_t rxrx2;
	int32_t ryry2;
	int32_t stopx, stopy;

	rxrx2 = rx;
	rxrx2 *= rx;
	rxrx2 *= 2;

	ryry2 = ry;
	ryry2 *= ry;
	ryry2 *= 2;

	x = rx;
	y = 0;

	xchg = 1;
	xchg -= rx;
	xchg -= rx;
	xchg *= ry;
	xchg *= ry;

	ychg = rx;
	ychg *= rx;

	err = 0;

	stopx = ryry2;
	stopx *= rx;
	stopy = 0;

	while( stopx >= stopy ) {
		_draw_ellipse_section(dev, x, y, x0, y0, color, option);
		y++;
		stopy += rxrx2;
		err += ychg;
		ychg += rxrx2;
		if ( 2*err+xchg > 0 ) {
			x--;
			stopx -= ryry2;
			err += xchg;
			xchg += ryry2;
		}
	}

	x = 0;
	y = ry;

	xchg = ry;
	xchg *= ry;

	ychg = 1;
	ychg -= ry;
	ychg -= ry;
	ychg *= rx;
	ychg *= rx;

	err = 0;

	stopx = 0;

	stopy = rxrx2;
	stopy *= ry;

	while( stopx <= stopy ) {
		_draw_ellipse_section(dev, x, y, x0, y0, color, option);
		x++;
		stopx += ryry2;
		err += xchg;
		xchg += ryry2;
		if ( 2*err+ychg > 0 ) {
			y--;
			stopy -= rxrx2;
			err += ychg;
			ychg += rxrx2;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------
static void _draw_filled_ellipse_section(TFT_t * dev, uint16_t x, uint16_t y, uint16_t x0, uint16_t y0, uint16_t color, uint8_t option)
{
    // upper right
    if ( option & TFT_ELLIPSE_UPPER_RIGHT ) lcdDrawLine(dev, x0+x, y0-y, x0+x+1, y0, color);
    // upper left
    if ( option & TFT_ELLIPSE_UPPER_LEFT ) 	lcdDrawLine(dev, x0-x, y0-y, x0-x, y0, color);
    // lower right
    if ( option & TFT_ELLIPSE_LOWER_RIGHT ) lcdDrawLine(dev, x0+x, y0, x0+x, y0+y, color);
    // lower left
    if ( option & TFT_ELLIPSE_LOWER_LEFT ) 	lcdDrawLine(dev, x0-x, y0, x0-x, y0+y, color);
}

//=====================================================================================================
void TFTFillEllipse(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry, uint16_t color, uint8_t option)
{
	// x0 += dispWin.x1;
	// y0 += dispWin.y1;

	uint16_t x, y;
	int32_t xchg, ychg;
	int32_t err;
	int32_t rxrx2;
	int32_t ryry2;
	int32_t stopx, stopy;

	rxrx2 = rx;
	rxrx2 *= rx;
	rxrx2 *= 2;

	ryry2 = ry;
	ryry2 *= ry;
	ryry2 *= 2;

	x = rx;
	y = 0;

	xchg = 1;
	xchg -= rx;
	xchg -= rx;
	xchg *= ry;
	xchg *= ry;

	ychg = rx;
	ychg *= rx;

	err = 0;

	stopx = ryry2;
	stopx *= rx;
	stopy = 0;

	while( stopx >= stopy ) {
		_draw_filled_ellipse_section(dev, x, y, x0, y0, color, option);
		y++;
		stopy += rxrx2;
		err += ychg;
		ychg += rxrx2;
		if ( 2*err+xchg > 0 ) {
			x--;
			stopx -= ryry2;
			err += xchg;
			xchg += ryry2;
		}
	}

	x = 0;
	y = ry;

	xchg = ry;
	xchg *= ry;

	ychg = 1;
	ychg -= ry;
	ychg -= ry;
	ychg *= rx;
	ychg *= rx;

	err = 0;

	stopx = 0;

	stopy = rxrx2;
	stopy *= ry;

	while( stopx <= stopy ) {
		_draw_filled_ellipse_section(dev, x, y, x0, y0, color, option);
		x++;
		stopx += ryry2;
		err += xchg;
		xchg += ryry2;
		if ( 2*err+ychg > 0 ) {
			y--;
			stopy -= rxrx2;
			err += ychg;
			ychg += rxrx2;
		}
	}
}

// Draw rectangle with round corner
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// r:radius
// color:color
void lcdDrawRoundRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, uint16_t color) {
	int x;
	int y;
	int err;
	int old_err;
	unsigned char temp;

	if(x1>x2) {
		temp=x1; x1=x2; x2=temp;
	} // endif
	  
	if(y1>y2) {
		temp=y1; y1=y2; y2=temp;
	} // endif

	ESP_LOGD(TAG, "x1=%d x2=%d delta=%d r=%d",x1, x2, x2-x1, r);
	ESP_LOGD(TAG, "y1=%d y2=%d delta=%d r=%d",y1, y2, y2-y1, r);
	if (x2-x1 < r) return; // Add 20190517
	if (y2-y1 < r) return; // Add 20190517

	x=0;
	y=-r;
	err=2-2*r;

	do{
		if(x) {
			lcdDrawPixel(dev, x1+r-x, y1+r+y, color); 
			lcdDrawPixel(dev, x2-r+x, y1+r+y, color); 
			lcdDrawPixel(dev, x1+r-x, y2-r-y, color); 
			lcdDrawPixel(dev, x2-r+x, y2-r-y, color);
		} // endif 
		if ((old_err=err)<=x)   err+=++x*2+1;
		if (old_err>y || err>x) err+=++y*2+1;    
	} while(y<0);

	ESP_LOGD(TAG, "x1+r=%d x2-r=%d",x1+r, x2-r);
	lcdDrawLine(dev, x1+r,y1  ,x2-r,y1  ,color);
	lcdDrawLine(dev, x1+r,y2  ,x2-r,y2  ,color);
	ESP_LOGD(TAG, "y1+r=%d y2-r=%d",y1+r, y2-r);
	lcdDrawLine(dev, x1  ,y1+r,x1  ,y2-r,color);
	lcdDrawLine(dev, x2  ,y1+r,x2  ,y2-r,color);  
} 

// Draw arrow
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// w:Width of the botom
// color:color
// Thanks http://k-hiura.cocolog-nifty.com/blog/2010/11/post-2a62.html
void lcdDrawArrow(TFT_t * dev, uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color) {
	double Vx= x1 - x0;
	double Vy= y1 - y0;
	double v = sqrt(Vx*Vx+Vy*Vy);
	//   printf("v=%f\n",v);
	double Ux= Vx/v;
	double Uy= Vy/v;

	uint16_t L[2],R[2];
	L[0]= x1 - Uy*w - Ux*v;
	L[1]= y1 + Ux*w - Uy*v;
	R[0]= x1 + Uy*w - Ux*v;
	R[1]= y1 - Ux*w - Uy*v;
	//   printf("L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);

	//   lcdDrawLine(x0,y0,x1,y1,color);
	lcdDrawLine(dev, x1, y1, L[0], L[1], color);
	lcdDrawLine(dev, x1, y1, R[0], R[1], color);
	lcdDrawLine(dev, L[0], L[1], R[0], R[1], color);
}


// Draw arrow of filling
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End   X coordinate
// y2:End   Y coordinate
// w:Width of the botom
// color:color
void lcdDrawFillArrow(TFT_t * dev, uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t w,uint16_t color) {
	double Vx= x1 - x0;
	double Vy= y1 - y0;
	double v = sqrt(Vx*Vx+Vy*Vy);
	//   printf("v=%f\n",v);
	double Ux= Vx/v;
	double Uy= Vy/v;

	uint16_t L[2],R[2];
	L[0]= x1 - Uy*w - Ux*v;
	L[1]= y1 + Ux*w - Uy*v;
	R[0]= x1 + Uy*w - Ux*v;
	R[1]= y1 - Ux*w - Uy*v;
	//   printf("L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);

	lcdDrawLine(dev, x0, y0, x1, y1, color);
	lcdDrawLine(dev, x1, y1, L[0], L[1], color);
	lcdDrawLine(dev, x1, y1, R[0], R[1], color);
	lcdDrawLine(dev, L[0], L[1], R[0], R[1], color);

	int ww;
	for(ww=w-1;ww>0;ww--) {
		L[0]= x1 - Uy*ww - Ux*v;
		L[1]= y1 + Ux*ww - Uy*v;
		R[0]= x1 + Uy*ww - Ux*v;
		R[1]= y1 - Ux*ww - Uy*v;
		//     printf("Fill>L=%d-%d R=%d-%d\n",L[0],L[1],R[0],R[1]);
		lcdDrawLine(dev, x1, y1, L[0], L[1], color);
		lcdDrawLine(dev, x1, y1, R[0], R[1], color);
	}
}


// RGB565 conversion
// RGB565 is R(5)+G(6)+B(5)=16bit color format.
// Bit image "RRRRRGGGGGGBBBBB"
uint16_t rgb565_conv(uint16_t r,uint16_t g,uint16_t b) {
	return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

// Draw ASCII character
// x:X coordinate
// y:Y coordinate
// ascii: ascii code
// color:color
int lcdDrawChar(TFT_t * dev, FontxFile *fxs, uint16_t x, uint16_t y, uint8_t ascii, uint16_t color) {
	uint16_t xx,yy,bit,ofs;
	unsigned char fonts[128]; // font pattern
	unsigned char pw, ph;
	int h,w;
	uint16_t mask;
	bool rc;

	if(_DEBUG_)printf("_font_direction=%d\n",dev->_font_direction);
	rc = GetFontx(fxs, ascii, fonts, &pw, &ph);
	if(_DEBUG_)printf("GetFontx rc=%d pw=%d ph=%d\n",rc,pw,ph);
	if (!rc) return 0;

	uint16_t xd1 = 0;
	uint16_t yd1 = 0;
	uint16_t xd2 = 0;
	uint16_t yd2 = 0;
	uint16_t xss = 0;
	uint16_t yss = 0;
	uint16_t xsd = 0;
	uint16_t ysd = 0;
	int next = 0;
        uint16_t x0  = 0;
        uint16_t x1  = 0;
        uint16_t y0  = 0;
        uint16_t y1  = 0;
	if (dev->_font_direction == 0) {
		xd1 = +1;
		yd1 = +1; //-1;
		xd2 =  0;
		yd2 =  0;
		xss =  x;
		yss =  y - (ph - 1);
		xsd =  1;
		ysd =  0;
		next = x + pw;

                x0  = x;
                y0  = y - (ph-1);
                x1  = x + (pw-1);
                y1  = y;
	} else if (dev->_font_direction == 2) {
		xd1 = -1;
		yd1 = -1; //+1;
		xd2 =  0;
		yd2 =  0;
		xss =  x;
		yss =  y + ph + 1;
		xsd =  1;
		ysd =  0;
		next = x - pw;

                x0  = x - (pw-1);
                y0  = y;
                x1  = x;
                y1  = y + (ph-1);
	} else if (dev->_font_direction == 1) {
		xd1 =  0;
		yd1 =  0;
		xd2 = -1;
		yd2 = +1; //-1;
		xss =  x + ph;
		yss =  y;
		xsd =  0;
		ysd =  1;
		next = y + pw; //y - pw;

                x0  = x;
                y0  = y;
                x1  = x + (ph-1);
                y1  = y + (pw-1);
	} else if (dev->_font_direction == 3) {
		xd1 =  0;
		yd1 =  0;
		xd2 = +1;
		yd2 = -1; //+1;
		xss =  x - (ph - 1);
		yss =  y;
		xsd =  0;
		ysd =  1;
		next = y - pw; //y + pw;

                x0  = x - (ph-1);
                y0  = y - (pw-1);
                x1  = x;
                y1  = y;
	}

        if (dev->_font_fill) lcdDrawFillRect(dev, x0, y0, x1, y1, dev->_font_fill_color);

	int bits;
	if(_DEBUG_)printf("xss=%d yss=%d\n",xss,yss);
	ofs = 0;
	yy = yss;
	xx = xss;
	for(h=0;h<ph;h++) {
		if(xsd) xx = xss;
		if(ysd) yy = yss;
		//    for(w=0;w<(pw/8);w++) {
		bits = pw;
		for(w=0;w<((pw+4)/8);w++) {
			mask = 0x80;
			for(bit=0;bit<8;bit++) {
				bits--;
				if (bits < 0) continue;
				//if(_DEBUG_)printf("xx=%d yy=%d mask=%02x fonts[%d]=%02x\n",xx,yy,mask,ofs,fonts[ofs]);
				if (fonts[ofs] & mask) {
					lcdDrawPixel(dev, xx, yy, color);
				} else {
					//if (dev->_font_fill) lcdDrawPixel(dev, xx, yy, dev->_font_fill_color);
				}
				if (h == (ph-2) && dev->_font_underline)
					lcdDrawPixel(dev, xx, yy, dev->_font_underline_color);
				if (h == (ph-1) && dev->_font_underline)
					lcdDrawPixel(dev, xx, yy, dev->_font_underline_color);
				xx = xx + xd1;
				yy = yy + yd2;
				mask = mask >> 1;
			}
			ofs++;
		}
		yy = yy + yd1;
		xx = xx + xd2;
	}

	if (next < 0) next = 0;
	return next;
}

int lcdDrawString(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, uint8_t * ascii, uint16_t color) {
	int length = strlen((char *)ascii);
	if(_DEBUG_)printf("lcdDrawString length=%d\n",length);
	for(int i=0;i<length;i++) {
		if(_DEBUG_)printf("ascii[%d]=%x x=%d y=%d\n",i,ascii[i],x,y);
		if (dev->_font_direction == 0)
			x = lcdDrawChar(dev, fx, x, y, ascii[i], color);
		if (dev->_font_direction == 1)
			y = lcdDrawChar(dev, fx, x, y, ascii[i], color);
		if (dev->_font_direction == 2)
			x = lcdDrawChar(dev, fx, x, y, ascii[i], color);
		if (dev->_font_direction == 3)
			y = lcdDrawChar(dev, fx, x, y, ascii[i], color);
	}
	if (dev->_font_direction == 0) return x;
	if (dev->_font_direction == 2) return x;
	if (dev->_font_direction == 1) return y;
	if (dev->_font_direction == 3) return y;
	return 0;
}


#if 0
// Draw SJIS character
// x:X coordinate
// y:Y coordinate
// sjis: SJIS code
// color:color
int lcdDrawSJISChar(TFT_t * dev, FontxFile *fxs, uint16_t x,uint16_t y,uint16_t sjis,uint16_t color) {
	uint16_t xx,yy,bit,ofs;
	unsigned char fonts[128]; // font pattern
	unsigned char pw, ph;
	int h,w;
	uint16_t mask;
	bool rc;

	if(_DEBUG_)printf("_font_direction=%d\n",dev->_font_direction);
	//  sjis = UTF2SJIS(utf8);
	//if(_DEBUG_)printf("sjis=%04x\n",sjis);

	rc = GetFontx(fxs, sjis, fonts, &pw, &ph); // SJIS -> Font pattern
	if(_DEBUG_)printf("GetFontx rc=%d pw=%d ph=%d\n",rc,pw,ph);
	if (!rc) return 0;

	uint16_t xd1, yd1;
	uint16_t xd2, yd2;
	uint16_t xss, yss;
	uint16_t xsd, ysd;
	int next;
	if (dev->_font_direction == 0) {
		xd1 = +1;
		yd1 = -1;
		xd2 =  0;
		yd2 =  0;
		xss =  x;
		yss =  y + ph - 1;
		xsd =  1;
		ysd =  0;
		next = x + pw;
	} else if (dev->_font_direction == 2) {
		xd1 = -1;
		yd1 = +1;
		xd2 =  0;
		yd2 =  0;
		xss =  x;
		yss =  y - ph + 1;
		xsd =  1;
		ysd =  0;
		next = x - pw;
	} else if (dev->_font_direction == 1) {
		xd1 =  0;
		yd1 =  0;
		xd2 = -1;
		yd2 = -1;
		xss =  x + ph;
		yss =  y;
		xsd =  0;
		ysd =  1;
		next = y - pw;
	} else if (dev->_font_direction == 3) {
		xd1 =  0;
		yd1 =  0;
		xd2 = +1;
		yd2 = +1;
		xss =  x - ph - 1;
		yss =  y;
		xsd =  0;
		ysd =  1;
		next = y + pw;
	}

	int bits;
	if(_DEBUG_)printf("xss=%d yss=%d\n",xss,yss);
	ofs = 0;
	yy = yss;
	xx = xss;
	for(h=0;h<ph;h++) {
		if(xsd) xx = xss;
		if(ysd) yy = yss;
		//    for(w=0;w<(pw/8);w++) {
		bits = pw;
		for(w=0;w<((pw+4)/8);w++) {
			mask = 0x80;
			for(bit=0;bit<8;bit++) {
				bits--;
				if (bits < 0) continue;
				//if(_DEBUG_)printf("xx=%d yy=%d mask=%02x fonts[%d]=%02x\n",xx,yy,mask,ofs,fonts[ofs]);
				if (fonts[ofs] & mask) {
					lcdDrawPixel(dev, xx, yy, color);
				} else {
					if (dev->_font_fill) lcdDrawPixel(dev, xx, yy, dev->_font_fill_color);
				}
				if (h == (ph-2) && dev->_font_underline)
					lcdDrawPixel(xx, yy, dev->_font_underline_color);
				if (h == (ph-1) && dev->_font_underline)
					lcdDrawPixel(xx, yy, dev->_font_underline_color);
				xx = xx + xd1;
				yy = yy + yd2;
				mask = mask >> 1;
			}
			ofs++;
		}
		yy = yy + yd1;
		xx = xx + xd2;
	}

	if (next < 0) next = 0;
	return next;
}

// Draw UTF8 character
// x:X coordinate
// y:Y coordinate
// utf8: UTF8 code
// color:color
int lcdDrawUTF8Char(TFT_t * dev, FontxFile *fx, uint16_t x,uint16_t y,uint8_t *utf8,uint16_t color) {
	uint16_t sjis[1];

	sjis[0] = UTF2SJIS(utf8);
	if(_DEBUG_)printf("sjis=%04x\n",sjis[0]);
	return lcdDrawSJISChar(dev, fx, x, y, sjis[0], color);
}

// Draw UTF8 string
// x:X coordinate
// y:Y coordinate
// utfs: UTF8 string
// color:color
int lcdDrawUTF8String(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, unsigned char *utfs, uint16_t color) {

	int i;
	int spos;
	uint16_t sjis[64];
	spos = String2SJIS(utfs, strlen((char *)utfs), sjis, 64);
	if(_DEBUG_)printf("spos=%d\n",spos);
	for(i=0;i<spos;i++) {
		if(_DEBUG_)printf("sjis[%d]=%x y=%d\n",i,sjis[i],y);
		if (dev->_font_direction == 0)
			x = lcdDrawSJISChar(dev, fx, x, y, sjis[i], color);
		if (dev->_font_direction == 1)
			y = lcdDrawSJISChar(dev, fx, x, y, sjis[i], color);
		if (dev->_font_direction == 2)
			x = lcdDrawSJISChar(dev, fx, x, y, sjis[i], color);
		if (dev->_font_direction == 3)
			y = lcdDrawSJISChar(dev, fx, x, y, sjis[i], color);
	}
	if (dev->_font_direction == 0) return x;
	if (dev->_font_direction == 2) return x;
	if (dev->_font_direction == 1) return y;
	if (dev->_font_direction == 3) return y;
	return 0;
}
#endif

// Set font direction
// dir:Direction
void lcdSetFontDirection(TFT_t * dev, uint16_t dir) {
	dev->_font_direction = dir;
}

// Set font filling
// color:fill color
void lcdSetFontFill(TFT_t * dev, uint16_t color) {
	dev->_font_fill = true;
	dev->_font_fill_color = color;
}

// UnSet font filling
void lcdUnsetFontFill(TFT_t * dev) {
	dev->_font_fill = false;
}

// Set font underline
// color:frame color
void lcdSetFontUnderLine(TFT_t * dev, uint16_t color) {
	dev->_font_underline = true;
	dev->_font_underline_color = color;
}

// UnSet font underline
void lcdUnsetFontUnderLine(TFT_t * dev) {
	dev->_font_underline = false;
}

// Backlight OFF
void lcdBacklightOff(TFT_t * dev) {
	if(dev->_bl >= 0) {
		gpio_set_level( dev->_bl, 0 );
	}
}

// Backlight ON
void lcdBacklightOn(TFT_t * dev) {
	if(dev->_bl >= 0) {
		gpio_set_level( dev->_bl, 1 );
	}
}

// Vertical Scrolling Definition
// tfa:Top Fixed Area
// vsa:Vertical Scrolling Area
// bfa:Bottom Fixed Area
void lcdSetScrollArea(TFT_t * dev, uint16_t tfa, uint16_t vsa, uint16_t bfa){
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x33);	// Vertical Scrolling Definition
		spi_master_write_data_word(dev, tfa);
		spi_master_write_data_word(dev, vsa);
		spi_master_write_data_word(dev, bfa);
		//spi_master_write_comm_byte(dev, 0x12);	// Partial Mode ON
	} // endif 0x9340/0x9341

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x31, vsa);	// Specify scroll end and step at the scroll display
		lcdWriteRegisterByte(dev, 0x32, tfa);	// Specify scroll start and step at the scroll display
#if 0
		spi_master_write_comm_byte(dev, 0x31);	// Specify scroll end address at the scroll display
		spi_master_write_data_word(dev, vsa);
		spi_master_write_comm_byte(dev, 0x32);	// Specify scroll start address at the scroll display
		spi_master_write_data_word(dev, tfa);
#endif
	} // endif 0x9225/0x9226
}

void lcdResetScrollArea(TFT_t * dev){
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x33);	// Vertical Scrolling Definition
		spi_master_write_data_word(dev, 0);
		spi_master_write_data_word(dev, 0x140);
		spi_master_write_data_word(dev, 0);
	} // endif 0x9340/0x9341

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x31, 0x0);	// Specify scroll end and step at the scroll display
		lcdWriteRegisterByte(dev, 0x32, 0x0);	// Specify scroll start and step at the scroll display
		//lcdWriteRegisterByte(dev, 0x31, vsa);	// Specify scroll end and step at the scroll display
		//lcdWriteRegisterByte(dev, 0x32, tfa);	// Specify scroll start and step at the scroll display
	} // endif 0x9225/0x9226
}

// Vertical Scrolling Start Address
// vsp:Vertical Scrolling Start Address
void lcdScroll(TFT_t * dev, uint16_t vsp){
	if (dev->_model == 0x9340 || dev->_model == 0x9341) {
		spi_master_write_comm_byte(dev, 0x37);	// Vertical Scrolling Start Address
		spi_master_write_data_word(dev, vsp);
	} // endif 0x9340/0x9341

	if (dev->_model == 0x9225 || dev->_model == 0x9226) {
		lcdWriteRegisterByte(dev, 0x33, vsp);	// Vertical Scrolling Start Address
#if 0
		spi_master_write_comm_byte(dev, 0x33);	// Vertical Scrolling Start Address
		spi_master_write_data_word(dev, vsp);
#endif
	} // endif 0x9225/0x9226
}

uint16_t TFT_INIT(void)
{
	spi_master_init(&dev, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);

	#if CONFIG_ILI9225
		uint16_t model = 0x9225;
	#endif
	#if CONFIG_ILI9225G
		uint16_t model = 0x9226;
	#endif
	#if CONFIG_ILI9340
		uint16_t model = 0x9340;
	#endif
	#if CONFIG_ILI9341
		uint16_t model = 0x9341;
	#endif
	#if CONFIG_ST7735
		uint16_t model = 0x7735;
	#endif
	#if CONFIG_ST7789V
		uint16_t model = 0x7789;
	#endif
		lcdInit(&dev, model, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

	#if CONFIG_INVERSION
		ESP_LOGI(TAG, "Enable Display Inversion");
		lcdInversionOn(&dev);
	#endif

	#if CONFIG_RGB_COLOR
		ESP_LOGI(TAG, "Change BGR filter to RGB filter");
		lcdBGRFilter(&dev);
	#endif
	lcdFillScreen(&dev, BLACK);
	return model;

} 
void TFT_SPIP_FREE(void)
{
	printf("remove\n");
	spi_bus_remove_device(dev._SPIHandle);
	printf("HSPI_HOST\n");
	spi_bus_free(HSPI_HOST);	
}
