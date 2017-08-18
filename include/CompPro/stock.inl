#if defined _stock_included
    #endinput
#endif


#define _stock_included

#include <amxmodx>

stock ColorPrint(id, const input[], any:...)
{
	static msg[191]
	vformat(msg, 190, input, 3)
	
	replace_all(msg, 190, "!g", "\4")
	replace_all(msg, 190, "!y", "\1")
	replace_all(msg, 190, "!t", "\3")
	
	replace_all(msg, 190, "^4", "\4")
	replace_all(msg, 190, "^1", "\1")
	replace_all(msg, 190, "^3", "\3")
	
	if(id)
	{
		message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, id);
		write_byte(id);
		write_string(msg);
		message_end();
		return;
	}
	static p[32], c, pl;
	get_players(p,c,"c")
	
	for (new i = 0; i < c; i++)
	{
		pl = p[i]
		message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, pl);
		write_byte(pl);
		write_string(msg);
		message_end();
	}
}
stock ErrorState( const errorcode, error[] )
{	
	
	static LogDat[16],LogFile[64]
	get_time("%Y_%m_%d", LogDat, 15);
	
	get_localinfo("amxx_logs",LogFile,63)
	formatex(LogFile,63,"%s/CompPro/Error_%s.log",LogFile,LogDat);
	 
	static szMsg[256];
	formatex(szMsg, 255, "Plugin [%s] take ERROR:[%s] [ErrorCode:#%d] | Visit: %s", PREFIX, error, errorcode, MAIN_SITE);
	log_to_file(LogFile,szMsg);
	set_fail_state(szMsg);
	return 0;
}
stock PrintMessage(const szMessage[], any:...)
{
	
	static szMsg[196];
	vformat(szMsg, charsmax(szMsg), szMessage, 2);
	
	static LogDat[16],LogFile[64]
	get_time("%Y_%m_%d", LogDat, 15);
	
	get_localinfo("amxx_logs",LogFile,63)
	formatex(LogFile,63,"%s/CompPro/Log_%s.log",LogFile,LogDat)
	
	log_to_file(LogFile,"[%s] %s",PREFIX,szMsg)
	return 0;
}
stock delete_comment( string[])
{
	static const BASE_COMMENT [] = { '#', ';', '/', '\\' };
	static const QUOTES = '\"';
	new bool: in_quotes = false;
	
	new len = strlen(string);
	for (new i; i < len; i++)
	{
		if( string[i] == QUOTES)
			in_quotes = !in_quotes;
		
		if(in_quotes)
			continue;
		
		for (new j; j < sizeof(BASE_COMMENT); j++)
		{
			if(string[i] == BASE_COMMENT[j])
			{
				string[i] = '\0';
				break;
			}
		}
	}
	
}
stock is_bad_char( data )
{
	if(data == 'c' || data == 'h' || data == 'd')
		return 0;
		
	return 1;
}
stock CheckStartComp(filedata[], &bool:check, start[], start_len, end[], end_len )
{
	if(equali(filedata, start, start_len))
	{
		check =true;
	}
	else if (equali(filedata, end, end_len))
		check =false;
}
stock is_bad_file(CurrNAME[], len)
{
	static const S_TRY[] = ".ini"
	static const DIM_LEN = 4;

	if ( ( len >= DIM_LEN ) && ( CurrNAME[ len - 1 ] == S_TRY[ 3 ] )
	&& ( CurrNAME[ len - 2 ] == S_TRY[ 2 ] ) && 
	( CurrNAME[ len - 3 ] == S_TRY[ 1 ] ) && ( CurrNAME[ len -4 ] == S_TRY[ 0 ] )) 
	return 0;
	
	return 1;
}
stock StartTaskComp(data[], number)
{
	new _data[256];
	copy(_data, 255, data)
	
	new fl[4], Float:f;
	strbreak(_data, fl, charsmax(fl), _data, charsmax(_data))
	
	f = str_to_float(fl);
	set_task(f, "TaskDisplayComp",TASK_DISPLAY_ID+number);
	
}
