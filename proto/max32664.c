/* max32664.c */

static HostCmdType cmd_get_status = {0x00, 0x00};
static uint8_t addr = 0x55;


static uint8_t issueHostCmd(HostCmdType cmd)
{
	// send family, index, data...
	// read status byte
	// return status byte 
}

static uint8_t getStatus(void)
{
	return issue_host_command(cmd_get_status);
}

max32664Init(uint8_t i2c_addr)
{
	if (i2c_addr != 0)
		addr = i2c_addr;

	
	
}