float reinstateFloat(uint8_t * input[4]){
	int x;
	x &= ~0xFFFF;
	x |= input[0] << 24;
	x |= input[1] << 16;
	x |= input[2] << 8;
	x |= input[3];
	return float(x);
}
