#ifndef MESSAGES_H
#define MESSAGES_H

#ifndef MSG_HEADER
#define MSG_HEADER

#include "MAIN_INCLUDES.h"
//#include "MainForm.h"

void loadMessages();
//Ìåíþ
#define MENU_VIEW 			1
#define menu_view_r 		"Âèä"
#define menu_view_e 		"View"
#define MENU_LANGUAGE 		2
#define menu_Itm_Language_r "Âûáîð ÿçûêà"
#define menu_Itm_Language_e "Change language"
#define MENU_TXT_SIZE 		3
#define menu_Itm_TextSize_r "Ðàçìåð òåêñòà"
#define menu_Itm_TextSize_e "Text size"
#define MENU_IMSTRUMENTS 	4
#define menu_Itm_Tools_r 	"Èíñòðóìåíòû"
#define menu_Itm_Tools_e 	"Tools"
#define MENU_LOG			5
#define menu_Itm_Log_r 		"Ôàéë æóðíàëà"
#define menu_Itm_Log_e 		"Log-files"
#define MENU_LOG_USE		6
#define menu_Itm_UseLog_r 	"Èñïîëüçîâàòü log-ôàéë"
#define menu_Itm_UseLog_e 	"Use"
#define MENU_LOG_EXT		7
#define menu_Itm_ExtLog_e 	"Use extended Log"
#define menu_Itm_ExtLog_r 	"Èñïîëüçîâàòü ðàñøèðåííûé Log"
#define MENU_RESET_PATH     8
#define menu_Itm_ResetPath_e "Use default directories"
#define menu_Itm_ResetPath_r "Ñáðîñèòü ïóòè ïî óìîë÷àíèþ"
#define MENU_SAVE_TO_FILE	9
#define menu_Itm_SaveScreen_r "Ñîõðàíèòü âûâîä â ôàéë"
#define menu_Itm_SaveScreen_e "Save output to file"
#define MENU_NET_SETTINGS	10
#define menu_Itm_Net_e 		"Net"
#define menu_Itm_Net_r 		"Ñåòü"
#define DBG_IP				11
#define menu_Itm_DebIP_e	"Debug IP-address"
#define menu_Itm_DebIP_r 	"Ðåæèì îòëàäêè IP-àäðåñà"
#define REFRESH_IP 			12
#define menu_Itm_UpdateIP_e "Update IP-address"
#define menu_Itm_UpdateIP_r "Îáíîâèòü IP-àäðåñ"
#define EDIT_IP				13
#define menu_Itm_EditIP_e 	"Edit IP-address"
#define menu_Itm_EditIP_r 	"Ðåäàêòèðîâàòü IP-àäðåñ"
#define MENU_HELP			14
#define menu_Itm_Help_r 	"Ïîìîùü"
#define menu_Itm_Help_e 	"Help"
#define MENU_F1				15
#define menu_Itm_Man_e 		"MonC_R Help"
#define menu_Itm_Man_r 		"Ñïðàâêà"
#define MENU_ABOUT  		16
#define menu_Itm_About_e 	"About..."
#define menu_Itm_About_r 	"Î ïðîãðàììå..."
#define MENU_FILE 			17
#define menu_file_r 		"Ôàéë"
#define menu_file_e 		"File"
#define MENU_SCRIPT 		18
#define menu_scroipt_r 		"Ñöåíàðèé"
#define menu_scroipt_e 		"Script"
#define NEW_SCRIPT 			28
#define new_script_r 		"Ñîçäàòü íîâûé"
#define new_script_e 		"New"
#define OPEN_SCRIPT 		20
#define open_scr_r 			"Îòêðûòü..."
#define open_scr_e			 "Open..."
#define SAVE_SCRIPT 		21
#define save_scr_r 			"Ñîõðàíèòü"
#define save_scr_e 			"Save"
#define SAVEAS_SCRIPT 		22
#define saveas_scr_r 		"Ñîõðàíèòü êàê..."
#define saveas_scr_e 		"Save as..."
#define RUN_SCR				23
#define run_scr_r  			"Çàïóñòèòü"
#define run_scr_e 			"Run"
#define COMP_RUN			24
#define compile_scr_r		"Êîìïèë. è çàïóñê"
#define compile_scr_e 		"Compile and run"
#define STEP_RUN 			25
#define step_scr_r 			"Ïîøàãîâûé çàïóñê"
#define step_scr_e			"Run by step"
#define BREAK_SC			26
#define break_scr_r 		"Ïðåðâàòü"
#define break_scr_e 		"Stop"
#define MENU_ENCODING 		27
#define encod_output_r  	"Êîäèðîâêà"
#define encod_output_e 		"Encoding"
//Âåðõíÿÿ ïàíåëü
#define MOD_LBL 			29
#define Label13_r 			"Ìîäóëü/Èçäåëèå"
#define Label13_e 			"Module/Product"
#define NUM_MOD_LBL 		30
#define Label14_rus 		"Íîìåð ìîäóëÿ"
#define Label14_eng 		"Module Number"
#define REPORT_CLICK 		31
#define CheckBox1_rus 		"Îò÷žò"
#define CheckBox1_eng 		"Report"
#define CAPT_CLICK	 		32
#define CaptureBox_r 		"Capture"
#define CaptureBox_e 		"Capture"
#define USB_LBL 			33
#define Label21_rus 		"USB-ðåëå"
#define Label21_eng 		"USB-relay"
#define TECH_BTN 			34
#define TechModeBtn_eng 	"Tech. mode"
#define TechModeBtn_rus 	"Òåõí. ðåæèì"
#define CONNECT_BTN 		35
#define ConBtnConnect_rus 	"Ïîäêëþ÷èòüñÿ"
#define ConBtnConnect_eng 	"Connect"
#define ConBtnDisconnect_rus "Îòêëþ÷èòüñÿ"
#define ConBtnDisconnect_eng "Disconnect"
#define USB_BTN 			36
#define Btn7_ON_rus 		"Âêë"
#define Btn7_OFF_rus 		"Âûêë"
#define Btn7_ON_eng 		"On"
#define Btn7_OFF_eng 		"Off"
//Íàçâàíèÿ âêëàäîê
#define TAB1_CAP 			19
#define tab1_r 				"Íàñòðîéêè"
#define tab1_e 				"Settings"
#define TAB2_CAP			37
#define tab2_r 				"Ìîíèòîð"
#define tab2_e 				"Monitor"
#define TAB3_CAP 			38
#define tab3_r 				"Îòëàä÷èê"
#define tab3_e 				"Debug"
#define TAB4_CAP 			39
#define tab4_r 				"Ðåæèì êîíòðîëÿ"
#define tab4_e 				"Control mode"
//Âêëàäêà Íàñòðîéêè
#define SET_LBL 			40
#define com_sett_r 			"Íàñòðîéêè COM-ïîðòà"
#define com_sett_e 			"COM-port settings"
#define COM_LBL 			41
#define com_lbl_r 			"ÑOM-ïîðò"
#define com_lbl_e 			"COM-port"
#define SPEED_LBL 			42
#define	StaticText2_rus 	"Ñêîðîñòü COM-ïîðòà"
#define	StaticText2_eng 	"Speed of COM Port"
#define BITS_LBL 			43
#define	Label3_rus 			"Áèòû äàííûõ"
#define	Label3_eng 			"Data bits"
#define PAR_LBL 			44
#define	Label4_rus 			"×žòíîñòü"
#define	Label4_eng 			"Parity"
#define STP_LBL 			45
#define	Label5_rus 			"Ñòîïîâûå áèòû"
#define	Label5_eng 			"Stop bits"
#define RFID_LBL 			46
#define Label23_rus 		"RFID COM-ïîðò"
#define Label23_eng 		"RFID COM-port"
#define PROC_PARAM_LBL 		47
#define proc_params_r		"Ïàðàìåòðû ïðîöåññîðà ìîäóëÿ"
#define proc_params_e 		"Processor`s parameters"
#define RAZR_LBL 			48
#define razr_r 				"Ðàçðÿäíîñòü"
#define razr_e 				"Capacity"
#define ARCH_LBL 			49
#define arch_r				"Àðõèòåêòóðà"
#define arch_e 				"Architecture"
#define BIO_LBL 			50
#define bios_r 				"Íîâûé BIOS"
#define bios_e 				"New BIOS"
#define WRK_FILES_LBL 		51
#define wrk_settings_r 		"Íàñòðîéêè ðàáî÷èõ ôàéëîâ"
#define wrk_settings_e 		"Working files settings"
#define STEND_LBL 			52
#define stend_r 			"Ñòåíä"
#define stend_e 			"Stend"
#define REP_LBL 			53
#define rep_r 				"Ïóòü ê ôàéëàì îò÷žòîâ"
#define rep_e 				"Reports path"
#define CAPT_LBL 			54
#define cap_r 				"Ïóòü ê Capture-ôàéëàì"
#define cap_e 				"Capture path"
#define SAVE_BTN 			55
#define sv_stend_r 			"Ñîõðàíèòü"
#define sv_stend_e 			"Save"
#define CAPTURE_MODE_LBL 	56
#define capMode_r 			"Ðåæèì Capture"
#define capMode_e 			"Capture mode"
#define TEXT_MODE_LBL 		57
#define textMode_r 			"Òåêñòîâûé"
#define textMode_e 			"Text"
#define BIN_MODE_LBL 		58
#define binMode_r 			"Áèíàðíûé"
#define binMode_e 			"Binary"
//Ïàíåëü ñ êíîïêàìè óïðàâëåíèÿ ñöåíàðèåì
#define OPEN_PANEL			59
#define hint_open_r			"Îòêðûòü ôàéë ñöåíàðèÿ"
#define hint_open_e			"Open script"
#define NEW_PANEL			60
#define hint_new_r			"Ñîçäàòü íîâûé ñöåíàðèé"
#define hint_new_e			"Create new script"
#define ADD_PANEL			61
#define hint_add_r			"Äîáàâèòü ñòðîêó"
#define hint_add_e			"Add new string"
#define DELETE_PANEL		62
#define hint_del_r			"Óäàëèòü ñòðîêó"
#define hint_del_e			"Delete selected string"
#define INS_PANEL			63
#define hint_ins_r			"Âñòàâèòü ñòðîêó"
#define hint_ins_e			"Insert string"
#define SAVE_PANEL			64
#define hint_save_r			"Ñîõðàíèòü ñöåíàðèé"
#define hint_save_e			"Save script"
#define SAVEAS_PANEL		65
#define hint_saveas_r		"Ñîõðàíèòü ñöåíàðèé êàê.."
#define hint_saveas_e		"Save script as..."
#define RUN_PANEL			66
#define hint_run_r			"Çàïóñòèòü ñöåíàðèé"
#define hint_run_e			"Run script"
#define STOP_PANEL			67
#define hint_stop_r			"Îñòàíîâèòü ñöåíàðèé"
#define hint_stop_e			"Stop script"
#define STEP_PANEL			68
#define hint_step_r			"Ïîøàãîâûé çàïóñê ñöåíàðèÿ"
#define hint_step_e			"Run script by step"
#define COMPILE_PANEL		69
#define hint_comp_r			"Êîìïèëÿöèÿ è çàïóñê"
#define hint_comp_e			"Compile and run"
//Âûïàä-èå ìåíþ ïî ïðàâîé êíîïêå íà Edit-àõ "Íàñòðîéêè"
#define INI_DEL				70
#define del_from_ini_r 		"Óäàëèòü èç ini-ôàéëà"
#define del_from_ini_e 		"Delete from ini-file"
#define DEF_PATH			71
#define def_path_r 			"Óñòàíîâèòü êàòàëîã ïî óìîë÷àíèþ"
#define def_path_e 			"Set default path"
#define REP_CMD				72
#define rep_cmd_r 			"Ïîâòîð êîìàíäû"
#define rep_cmd_e 			"Repeat operation"
#define OP_SZ				73
#define op_sz_r 			"Ðàçìåð äàííûõ"
#define op_sz_e 			"Data size"
#define OP_INOUT			74
#define op_inout_r 			"Îïåðàöèè â ïðîñòðàíñòâå ââîäà/âûâîäà"
#define op_inout_e 			"I/O operations"
#define RD_DATA_CAP			75
#define rd_data_cap_r		"Ñ÷èòàííûå äàííûå"
#define rd_data_cap_e		"Data In"
#define WR_DATA_CAP			76
#define wr_data_cap_r		"Çàïèñûâàåìûå äàííûå"
#define wr_data_cap_e		"Data Out"
#define RD_BTNPort			77
#define rd_btnp_r           "Ñ÷èòàòü èç ïîðòà"
#define rd_btnp_e           "Get from port"
#define WR_BTNPort			78
#define wr_btnp_r           "Çàïèñàòü â ïîðò "
#define wr_btnp_e           "Send to port"
#define MEM_OPS				79
#define mem_ops_r           "Îïåðàöèè ñ ïàìÿòüþ"
#define mem_ops_e			"Memory Operations"
#define FR_TO_FL			80
#define fr_to_fl_r          "Èñïîëüçîâàòü ôàéë"
#define fr_to_fl_e			"Use file"
#define FL_SZ_M				81
#define fl_sz_m_r           "Ðàçìåð ôàéëà"
#define fl_sz_m_e			"Size"
#define	RD_DATA_MEM			82
#define	WR_DATA_MEM			83
#define RD_MEM_BTN			84
#define rd_mem_btn_r		"Ñ÷èòàòü"
#define rd_mem_btn_e		"Get from"
#define WR_MEM_BTN			85
#define wr_mem_btn_r		"Îòïðàâèòü"
#define wr_mem_btn_e		"Send to"
#define JMP_MEM_BTN			86
#define jmp_mem_btn_r		"Ïåðåéòè ïî àäð."
#define jmp_mem_btn_e		"Jump"
#define STAT_LBL			87
#define stst_r 				"Ñòàòóñ:"
#define stst_e 				"Status:"
#define CANCEL_BTN  		88
#define can_btn_r 			"Îòìåíà"
#define can_btn_e 			"Cancel"
#define STAT_FLD  			89
#define stat_fld_r 			"Log ñîáûòèé"
#define stat_fld_e 			"Event log"
#define	CON_STATUS_BAR		90
#define	CON_STATUS_BAR_r	"Ïîäêëþ÷åíî ê "
#define	CON_STATUS_BAR_e	"Connected to "
#define	DISCON_STATUS_BAR	91
#define	DISCON_STATUS_BAR_r	"Îòêëþ÷åíî"
#define	DISCON_STATUS_BAR_e	"Disconnected"
#define CONSOLE_CAP			92
#define CONSOLE_CAP_r		"Êîíñîëü"
#define CONSOLE_CAP_e		"Console"
#define TERMINAL_CAP		93
#define TERMINAL_CAP_r      "Òåðìèíàë"
#define TERMINAL_CAP_e		"Terminal"
#define SIZE_CAP			94
#define SIZE_CAP_r          "Ðàçìåð: "
#define SIZE_CAP_e          "Size: "
#define CHSM_CAP			95
#define CHSM_CAP_r			"ÊíòðÑì: "
#define CHSM_CAP_e          "ChSm: "
#define REP_CAP				96
#define REP_CAP_r           "Ïîâòîð: "
#define REP_CAP_e           "Repeat: "


//ÑÎÎÁÙÅÍÈß
//Äëÿ îïðåäåëåíèÿ òèïà âûâîäèìîãî ñîîáùåíèÿ
#define MSG_TYPE_ERR_BOX		1000
#define MSG_TYPE_WRN_BOX    	2000
#define MSG_TYPE_LOG_WR	    	3000
#define MSG_TYPE_CAPT_WR	    4000
#define MSG_TYPE_RPRT_WR	    	5000
#define MSG_TYPE_RPRT_WR_TIME    	5001
#define MSG_TYPE_RPRT_WR_DT_TIME	5002
#define MSG_TYPE_STAT_WR	    6000
#define MSG_TYPE_PSI_STAT		7000
#define MSG_TYPE_PSI_STATBAR	8000
#define NO_NEED_FOR_TRANS	 	530
#define SIMPLE_OUTPUT		 	531

 //Áèáëèîòåêà USB-ðåëå

#define LIB_NOT_FOUND			500
#define Lib_not_found_msg_r   	"Áèáëèîòåêà %s íå îáíàðóæåíà"
#define Lib_not_found_msg_e    	"Unable to find %s library "
#define LIB_ADDR_BAD			501
#define Lib_bad_addresses_r 	"Îøèáêà â îïðåäåëåíèè àäðåñîâ ôóíêöèé ïðè çàãðóçêå %s"
#define Lib_bad_addresses_e    	"Unable to retrieve the address of a function from %s"
#define LIB_ERR_CODE			502
#define Lib_errcode_r   		"Áèáëèîòåêà %s íå çàãðóæåíà. Êîä îøèáêè %d "
#define Lib_errcode_e   		"Unable to load %s library. Error code %d "
#define NO_RELE_FOUND			503
#define Lib_no_rel_r   			"USB-ðåëå íå îáíàðóæåíû"
#define Lib_no_rel_e   			"Unable to detect any relays"
#define RELEY_DETECTED 			504
#define Lib_detected_rel_r   	"Îáíàðóæåíû %s ðåëå"
#define Lib_detected_rel_e  	"Detected %s relays"
#define DETECT_ONE_RELE			"Îáíàðóæåíî è âêëþ÷åíî ðåëå, ID=%d"
#define DETECT_SOME_RELES		"Âñå ðåëå (%d) âêëþ÷åíû"
#define FILE_REWITE				505
#define file_rewrite_r   		"Ïåðåñîõðàíèòü ôàéë ñöåíàðèÿ?"
#define file_rewrite_e 		  	"Would you like to overwrite the script?"
#define REPORT_OPEN_ERROR 		506
#define err_Open_report_e 		"Unable to open Report file"
#define err_Open_report_r 		"Íåâîçìîæíî îòêðûòü ôàéë îò÷žòà"
#define ERROR_TITLE 			507
#define ERROR_CAPTION_e 		"Error"
#define ERROR_CAPTION_r 		"Îøèáêà"
#define WARNING_TITLE 			508
#define WARNING_CAPTION_e 		"Warning"
#define WARNING_CAPTION_r 		"Ïðåäóïðåæäåíèå"
#define SCRIPT_NOT_SELECT 		509
#define err_Script_not_selected_r 		"Ñêðèïò äëÿ çàïóñêà íå âûáðàí"
#define err_Script_not_selected_e 	 	"Select the script to run!"
#define LOG_FILE_NOT_OPEN   	510
#define err_log_open_r 			"Íå óäàåòñÿ îòêðûòü log-ôàéë"
#define err_log_open_e 			"Unable to open log-file"
#define ERROR_OPEN_COM			511
#define err_open_com_r  		"Íå óäàåòñÿ îòêðûòü COM-ïîðò "
#define err_open_com_e  		"ÑOM port cannot be opened!"
#define FORM_CLOSE				512
#define close_form_msg_e 		"Are you sure you want to close the application?"
#define close_form_msg_r 		"Âû óâåðåíû, ÷òî õîòèòå çàêðûòü ïðèëîæåíèå?"
#define ERR_VAL_INPUT			513
#define err_input_value_r  		"Äàííûå äîëæíû áûòü â äåñÿòè÷íîé ÑÑ!"
#define err_input_value_e 		"Data must mast be in DEC!"
#define ERR_VAL_IN_HEX			514
#define err_input_inHex_r   	"Äàííûå äîëæíû áûòü â øåñòíàäöàòåðè÷íîé ÑÑ!"
#define err_input_inHex_e   	"Data must be in HEX!"
#define ERR_VAL_SIZE			515
#define err_address_size_r 		"Íåâåðíàÿ ðàçìåðíîñòü àäðåñà!"
#define err_address_size_e 		"Bad size of address!"
#define REPEAT_NUM				516
#define msg_Repeat_num_e 		"Repeat: %d"
#define msg_Repeat_num_r 		"Ïîâòîð: %d"
#define ERR_OPEN_CAPTURE		517
#define err_capture_open_e 		"Unable to open capture file"
#define err_capture_open_r 		"Íå óäàžòñÿ îòêðûòü Capture-ôàéë"
#define ERR_TEST_EMPTY			518
#define err_no_data_toSave_r	"Íåò äàííûõ äëÿ ñîõðàíåíèÿ"
#define err_no_data_toSave_e	"No text to save"
#define ERR_OPEN_SV_FILE		519
#define err_saveFromScreen_open_e 		"Unable to open file"
#define err_saveFromScreen_open_r 		"Íå óäàžòñÿ îòêðûòü ôàéë äëÿ ñîõðàíåíèÿ äàííûõ"
#define ERR_INI_OPEN			520
#define err_ini_open_r 			"Íå óäàåòñÿ îòêðûòü ini-ôàéë"
#define err_ini_open_e 			"Unable to open ini-file"
#define FILE_EXIST				521
#define FILE_EXIST_r            "Ôàéë óæå ñóùåñòâóåò. Çàìåíèòü?"
#define FILE_EXIST_e			"File is already exists. Overwrite it?"
#define SAVE_AS_MSG				522
#define SAVE_AS_MSG_r          	"Ñîõðàíèòü êàê"
#define SAVE_AS_MSG_e           "Save as"
#define ERROR_NO_SIZE			523
#define ERROR_NO_SIZE_r         "Îøèáêà: íå óêàçàíî êîëè÷åñòâî áàéòîâ!!!"
#define ERROR_NO_SIZE_e         "Error: Input number of bytes!!!"
#define BYTES_LEFT				524
#define BYTES_LEFT_r            "Îñòàëîñü %d áàéò"
#define BYTES_LEFT_e            "Remain %d bytes"
#define RUN_STR_NUM				525
#define RUN_STR_NUM_r			"Âûïîëíÿåòñÿ %d ñòðîêà"
#define RUN_STR_NUM_e           "Proc %d string"
#define UNABVLE_OPEN_FILE		526
#define UNABVLE_OPEN_FILE_r		"Íå óäàžòñÿ îòêðûòü ôàéë %s"
#define UNABVLE_OPEN_FILE_e		"Unable to open file %s"
/*
#define RPRT_STOP				527
#define RPRT_RUN				528     */

#define CAPTURE_BIN				529
#define papture_bin_r			"Çàõâàò bin"
#define papture_bin_e			"Capture bin"
#define OUT_TWO_STRINGS 		531
#define RFID_ERR				532
#define NO_RFID_NUM_r			"Íå ââåäží íîìåð COM-ïîðòà RFID!"
#define NO_RFID_NUM_e			"Input COM-port number for RFID!"
#define RFID_ERR_OPEN			533
#define RFID_ERR_OPEN_r			"Íå óäàžòñÿ îòêðûòü COM-ïîðò RFID"
#define RFID_ERR_OPEN_e			"Unable to open COM-port RFID"
#define	RFID_SETCOM_ERR         534
#define	RFID_SETCOM_ERR_r		"Ôóíêöèÿ SetCommState() hRFID_COM âåðíóëà ÍÅÍÎÐÌÓ"
#define	RFID_SETCOM_ERR_e		"SetCommState() hRFID_COM returns false"
#define ERR_OPEN_FILE 			535
#define	ERR_OPEN_FILE_r			"Íåâîçìîæíî îòêðûòü ôàéë!"
#define	ERR_OPEN_FILE_e			"File opening error!"
#define	ERR_DETECT_FILE			536
#define	ERR_DETECT_FILE_r		"Ôàéë %s íå îáíàðóæåí!"
#define	ERR_DETECT_FILE_e		"File %s not found!"
#define ERR_SCRIPT_FORMAT		537
#define ERR_SCRIPT_FORMAT_r		"Íåâåðíûé ôîðìàò ôàéëà!"
#define ERR_SCRIPT_FORMAT_e		"Invalid file format"
#define ERR_FILE_SIZE			538
#define ERR_FILE_SIZE_r			"Íåâåðíûé ðàçìåð ôàéëà!"
#define ERR_FILE_SIZE_e			"Invalid file size!"
#define MSG_ASK_FOR_REWR		539
#define MSG_ASK_FOR_REWR_r		"Ïåðåçàïèñàòü ôàéë?"
#define MSG_ASK_FOR_REWR_e      "Would you like to overwrite the script?"
#define ERR_INI_FIND			540
#define err_ini_find_r 			"Íå óäàëîñü îáíàðóæèòü ini-ôàéë, íåêîòîðûå ôóíêöèè ìîãóò áûòü íåäîñòóïíû"
#define err_ini_find_e 			"Unable to find ini-file"
#define EMPTY_FILEPATH          541
#define EMPTY_FILEPATH_r        "Óêàæèòå ïóòü ê ôàéëó"
#define EMPTY_FILEPATH_e        "Specify the path to the file"
#define TECH_MODE_r				"Ïåðåâîä ìîäóëÿ â òåõíîëîãè÷åñêèé ðåæèì"
#define ON_USB_ERR				542
#define ON_USB_ERR_r			"Îøèáêà ïðè âêëþ÷åíèè USB-ðåëå!"
#define ON_USB_ERR_e			"Error turn on USB_relay!"
#define ON_USB_OK				543
#define ON_USB_OK_r				"USB-ðåëå âêëþ÷åíû óñïåøíî"
#define ON_USB_OK_e				"USB-relay turns on successfully"
#define OFF_USB_ERR				544
#define OFF_USB_ERR_r			"Îøèáêà ïðè âûêëþ÷åíèè USB-ðåëå!"
#define OFF_USB_ERR_e			"Error turn off USB_relay!"
#define OFF_USB_OK				545
#define OFF_USB_OK_r			"USB-ðåëå âûêëþ÷åíû óñïåøíî"
#define OFF_USB_OK_e			"USB-relay turns oàà successfully"
#define REPEAT_OP_MSG			546
#define REPEAT_OP_MSG_r         "Ïîâòîðÿþùàÿñÿ îòïðàâêà äàííûõ.."
#define REPEAT_OP_MSG_e         "Repeat sending data.."
#define SND_OP_MSG				547
#define SND_OP_MSG_r            "Îòïðàâêà äàííûõ..."
#define SND_OP_MSG_e			"Sending data..."
#define NO_ADDRESS_IN			548
#define NO_ADDRESS_IN_r			"Íå ââåäåí àäðåñ!"
#define NO_ADDRESS_IN_e         "Input address!"
#define OPERATION_COMP			549
#define OPERATION_COMP_r 		"Îïåðàöèÿ çàâåðøåíà"
#define OPERATION_COMP_e        "Operation completed"
#define CRC_ERROR				550
#define CRC_ERROR_r				"Îøèáêà CRC32"
#define CRC_ERROR_e             "CRC32 error"
#define REPEAT_RD_MSG			551
#define REPEAT_RD_MSG_r         "Ïîâòîðÿþùååñÿ ÷òåíèå äàííûõ.."
#define REPEAT_RD_MSG_e			"Repeat reading data.."
#define RD_MSG					552
#define RD_MSG_r         		"×òåíèå äàííûõ.."
#define RD_MSG_e				"Reading data.."
#define JMP_MSG					553
#define JMP_MSG_r				"Ïåðåõîä ïî àäðåñó..."
#define JMP_MSG_e				"Jump..."


#define REPORT_OPEN 			"Ôàéë îò÷žòà %s îòêðûò"
#define REPRT_CLOSE				"Ôàéë îò÷žòà çàêðûò"
#define RPRT_PSI				"Ôàéë îò÷žòà îòêðûò â ðåæèìå ÏÑÈ"
#define RPRT_DBG				"Ôàéë îò÷žòà îòêðûò â ðåæèìå ðàçðàáîò÷èêà"
#define RPRT_STAND				"Ñòåíä: %s"
#define RPRT_NAME				"Íàèìåíîâàíèå: %s"
#define RPRT_NMBR				"Íoìåð: %s"
#define RPRT_STOP   			"Ñöåíàðèé çàâåðøèëñÿ"
#define RPRT_RUN				"Ñöåíàðèé %s çàïóùåí"
#define RPRT_EMPTY_STR			" "
#define RPRT_REPEAT_NUM			"Êîëè÷åñòâî ïîâòîðåíèé: %d"
#define RPRT_REP_INFO			"Ïîâòîð ¹%d"
#define RPRT_WR_TO_PORT 		"Çàïèñü â ïîðò 0x%x äàííûõ 0x%x"
#define RPRT_RD_FRM_PORT		"×òåíèå èç ïîðòà 0x%x äàííûõ 0x%x"
#define RPRT_RD_FROM_MEM		"×òåíèå ñ àäðåñà 0x%x äàííûõ 0x%x"
#define RPRT_WR_TO_MEM			"Çàïèñü ïî àäðåñó 0x%x äàííûõ 0x%x"
#define RPRT_FILE_LOAD			"Çàãðóæåí ôàéë: %s"



#define RPRT_RUN_TEST			"Òåñò çàïóùåí"
#define RPRT_TEST_STOP			"Òåñò çàêîí÷åí"
#define RPRT_FAIL_TECH			"Ñáîé â òåõíîëîãè÷åñêîì êàíàëå"
#define RPRT_TTL_CHSM			"Îáùàÿ êîíòðîëüíàÿ ñóììà: %s"
#define RPRT_LOAD_FL_NAME		"Çàãðóæàåìûé ôàéë: %s"
#define TIME_STR 				" %s"
#define DEC_STR					"%d"
#define SCRIPT_COMPLETED		"Ñöåíàðèé âûïîëíåí"
#define SCRIPT_COMP_AND_RUN		"Ñöåíàðèé %s ñêîìïèëèðîâàí è çàïóùåí"
#define SCRIPT_INTERRUPTED		"Ñöåíàðèé %s ïðåðâàí"
#define OPERATION_INTERRUPTED	"Îïåðàöèÿ ïðåðâàíà"
#define TECH_MODE				"Ïåðåâîä ìîäóëÿ â òåõíîëîãè÷åñêèé ðåæèì"
#define OPERATION_CRC32_ERR 	"Îøèáêà CRC32"
#define OPERATON_END			OPERATION_COMP_r


#define READ_MSG				"Âû÷èòàíî 0x%x"

#define RPRT_CHK_SUM			"Êîíòðîëüíàÿ ñóììà: 0x%x"
#define RPRT_LOAD_ADDRESS		"Çàãðóçî÷íûé àäðåñ: 0x%x"
#define READ_FROM_PRT			"×òåíèå äàííûõ(%s) èç ïîðòà 0x%x"
#define READ_FROM_PRT_REP		"Ïîâòîðÿþùååñÿ ÷òåíèå äàííûõ(%s) èç ïîðòà 0x%x %d ðàç"
#define RD_FROM_MEM				"×òåíèå äàííûõ(%s) ñ àäðåñà â ïàìÿòè 0x%x"
#define RD_FROM_MEM_REP         "Ïîâòîðÿþùååñÿ ÷òåíèå äàííûõ(%s) ñ àäðåñà â ïàìÿòè 0x%x %d ðàç"
#define WR_TO_MEM               "Çàïèñü 0x%x (%s) ïî àäðåñó â ïàìÿòè 0x%x"
#define WR_TO_MEM_REP           "Ïîâòîðÿþùàÿñÿ çàïèñü 0x%x (%s) ïî àäðåñó â ïàìÿòè 0x%x %d ðàç"
#define WR_TO_PORT				"Çàïèñü 0x%x (%s) â ïîðò 0x%x"
#define WR_TO_PORT_REP          "Ïîâòîðÿþùàÿñÿ çàïèñü 0x%x (%s) â ïîðò 0x%x %d ðàç"
#define RD_FROM_MEM_TO_FILE 	"Âû÷èòàòü %d áàéò ñ àäðåñà 0õ%x â ôàéë %s"
#define WR_FROM_FILE_TO_MEM		"Çàïèñü %d áàéò èç ôàéëà %s ïî àäðåñó 0x%x"
#define RESULT_MSG				"Ðåóëüòàò: 0x%x"
#define CHK_SUM_STR				"ÊîíòðÑì 0x%x"
#define LOG_FILE_SZ 			"Ðàçìåð ôàéëà %d áàéò"
#define RPRT_FILE_SIZE			"Ðàçìåð ôàéëà: %d áàéò"
#define JUMP_AND_WAIT_MSG		"Ïåðåõîä ïî àäðåñó 0x%x è îæèäàíèå îêîí÷àíèÿ îïåðàöèè"
#define JUMP_MSG				"Ïåðåõîä ïî àäðåñó 0x%x"
#define OPEN_CAPTURE_BIN		"Ôàéë ñ âûâîäèìûìè äàííûìè %s îòêðûò"
#define OPEN_CAPTURE_TXT		"Ôàéë ñ âûâîäèìûìè äàííûìè %s îòêðûò â òåêñòîâîì ðåæèìå"
#define CLOSE_CAPTURE			"Ôàéë ñ âûâîäèìûìè äàííûìè çàêðûò"
#define	FILE_OPEND				"Ôàéë %s îòêðûò"
#define SCRIPT_OPEN_ERR			"Îøèáêà ïðè îòêðûòèè ñöåíàðèÿ %s"
#define LOG_FILE_CLOSED			"log-ôàéë çàêðûò"
#define ERROR_MSG_SCRIPT		"ÎØÈÁÊÀ Â ÑÒÐÎÊÀÕ:"
#define UNABLE_TO_OPEN			"Ôàéë %s íå ìîæåò áûòü îòêðûò"
#define BAD_WR_SIZE				"Çàïèñûâàåìîå êîëè÷åñòâî áàéòîâ ïðåâûøàåò ðàçìåð ôàéëà"
#define SAVE_SCRIPT_MSG			"Ñöåíàðèé %s ñîõðàíží"
#define SAVE_SCRIPT_MSG_OLD		"Ñöåíàðèé %s ñîõðàíží â ñòàðîì ôîðìàòå"

#define MSG_ADD					"Ê àäðåñó 0x%x äîáàâëåíî ñìåùåíèå 0x%x"
#define MSG_COMPARE 			"Ñðàâíåíèå 0x%x è 0x%x"
#define MSG_LABEL				"Ïåðåõîä íà ìåòêó %s"
#define MSG_REP_LBL				"Ïîâòîðÿåì %d ðàç êîìàíäû, íà÷èíàÿ ñ ìåòêè %s"
#define MSG_CHECK_ZERO			"Åñëè ðåçóëüòàò ïðåäûäóùåãî âûðàæåíèÿ ÍÎËÜ, òî ïåðåõîä íà ìåòêó %s"
#define MSG_CHECK_NOT_ZERO 		"Åñëè ðåçóëüòàò ïðåäûäóùåãî ñîîáùåíèÿ ÍÅ ÍÎËÜ, òî ïåðåõîä íà ìåòêó %s"
#define MSG_CALL 				"Âûçîâ ïî ìåòêå %s"
#define MSG_RET					"Âîçâðàò èç ôóíêöèè"
#define MSG_CMP_MEM				"Ñðàâíåíèå äàííûõ, ëåæàùèõ â ïàìÿòè ïî àäðåñàì 0x%x è 0x%x"
#define MSG_MOV_MEM				"Ïîìåñòèòü äàííûå 0x%x èç àäðåñà 0x%x ïî àäðåñó 0x%x"
#define MSG_MOV_PORT			"Ïîìåñòèòü äàííûå 0x%x èç àäðåñà â ïàìÿòè 0x%x â ïîðò 0x%x"
#define MSG_MOV_PORT_MEM 		"Ïîìåñòèòü äàííûå 0x%x èç ïîðòà 0x%x ïî àäðåñó â ïàìÿòè 0x%x"
#define MSG_JMP_ADDR			"Ïåðåõîä ïî àäðåñó 0x%x"
#define MSG_LOAD_AND_RUN		"Çàïèñü ôàéëà %s ïî àäðåñó â ïàìÿòè 0x%x è çàïóñê"
#define DELAY_MSG				"Çàäåðæêà íà %d ñåêóíä"
#define MSG_LOAD_FILE			"Çàïèñü ôàéëà %s ïî àäðåñó â ïàìÿòè 0x%x"
#define MSG_OUT_TEXT			"Âûâîäèìûé òåêñò %s"
#define MSG_WAIT_RESTART		"Îæèäàíèå ïåðåçàãðóçêè îò ìîäóëÿ"
#define MSG_GET_TYPE			"Îïðåäåëåí òèï ìîäóëÿ: %x"
#define MSG_GET_REP_STATE		"Îïðåäåëåíî êîëè÷åñòâî ïîâòîðîâ: %d"
#define MSG_GET_SCRIPT_RESULT	"Ïîëó÷åíèå ðåçóëüòàòà ðàáîòû ñöåíàðèÿ"
#define MSG_GET_SCRIPT_RESULT_OK	"Ñöåíàðèé çàâåðøèëñÿ ÍÎÐÌÎÉ"
#define MSG_GET_SCRIPT_RESULT_ER	"Ñöåíàðèé çàâåðøèëñÿ ÍÅÍÎÐÌÎÉ"
#define MSG_THIRT_APP_RUN_PARAMS	"Çàïóñê ñòîðîííåãî ïðèëîæåíèÿ %s ñ ïàðàìåòðàìè %s "
#define MSG_THIRT_APP_RUN		"Çàïóñê ñòîðîííåãî ïðèëîæåíèÿ %s "
#define MSG_THIRT_APP_RUN_WT	"Çàïóñê ñòîðîííåãî ïðèëîæåíèÿ %s ñ ïàðàìåòðàìè %s è îæèäàíèå îêîí÷àíèÿ "
#define MSG_SHARE_BROKE			"Ôàéë äëÿ âçàèìîäåéñòâèÿ íå îòêðûò!"
#define ERR_RUN_APP				"Íå óäàëîñü çàïóñòèòü ïðèëîæåíèå %s"
#define APP_OK_STOP            	"Ïðèëîæåíèå %s çàâåðøèëîñü áåç îøèáîê"
#define APP_ERR_STOP            "Ïðèëîæåíèå %s çàâåðøèëîñü ñ îøèáêîé. Êîä îøèáêè 0x%x"
#define DATA_FROM_SCREEN_SAVED 	"Äàííûå ñ ýêðàíà ñîõðàíåíû â ôàéë %s"

#define RELEY_ERR				"Îøèáêà ïðè ðàáîòå ñ ðåëå"
#define NO_CONNECTION			"Íåîáõîäèìî ïîäêëþ÷åíèå ê COM-ïîðòó!"
#define DO_U_WANT_SAVE			"Âû õîòèòå ñîõðàíèòü ñöåíàðèé "


#endif

#endif // MESSAGES_H
