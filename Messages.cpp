#include "Messages.h"


void loadMessages() {
//    Form1->AddToMessagesVector( MENU_VIEW, menu_view_r, menu_view_e);
//    Form1->AddToMessagesVector( MENU_LANGUAGE, menu_Itm_Language_r, menu_Itm_Language_e);
//    Form1->AddToMessagesVector( MENU_TXT_SIZE, menu_Itm_TextSize_r, menu_Itm_TextSize_e);
//    Form1->AddToMessagesVector( MENU_IMSTRUMENTS, menu_Itm_Tools_r, menu_Itm_Tools_e);
//    Form1->AddToMessagesVector( MENU_LOG, menu_Itm_Log_r, menu_Itm_Log_e);
//    Form1->AddToMessagesVector( MENU_LOG_USE, menu_Itm_UseLog_r, menu_Itm_UseLog_e);
//    Form1->AddToMessagesVector( MENU_LOG_EXT, menu_Itm_ExtLog_r, menu_Itm_ExtLog_e);
//    Form1->AddToMessagesVector( MENU_RESET_PATH, menu_Itm_ResetPath_r, menu_Itm_ResetPath_e);
//    Form1->AddToMessagesVector( MENU_SAVE_TO_FILE, menu_Itm_SaveScreen_r, menu_Itm_SaveScreen_e);
//    Form1->AddToMessagesVector( MENU_NET_SETTINGS, menu_Itm_Net_r, menu_Itm_Net_e);
//    Form1->AddToMessagesVector( DBG_IP, menu_Itm_DebIP_r, menu_Itm_DebIP_e);
//    Form1->AddToMessagesVector( REFRESH_IP, menu_Itm_UpdateIP_r, menu_Itm_UpdateIP_e);
//    Form1->AddToMessagesVector( EDIT_IP, menu_Itm_EditIP_r, menu_Itm_EditIP_e);
//    Form1->AddToMessagesVector( MENU_HELP, menu_Itm_Help_r, menu_Itm_Help_e);
//    Form1->AddToMessagesVector( MENU_F1, menu_Itm_Man_r, menu_Itm_Man_e);
//    Form1->AddToMessagesVector( MENU_ABOUT, menu_Itm_About_r, menu_Itm_About_e);
//    Form1->AddToMessagesVector( MENU_FILE, menu_file_r, menu_file_e);
//    Form1->AddToMessagesVector( MENU_SCRIPT, menu_scroipt_r, menu_scroipt_e );
//    Form1->AddToMessagesVector( NEW_SCRIPT, new_script_r, new_script_e);
//    Form1->AddToMessagesVector( OPEN_SCRIPT, open_scr_r, open_scr_e);
//    Form1->AddToMessagesVector( SAVE_SCRIPT, save_scr_r, save_scr_e);
//    Form1->AddToMessagesVector( SAVEAS_SCRIPT, saveas_scr_r, saveas_scr_e);
//    Form1->AddToMessagesVector( RUN_SCR, run_scr_r, run_scr_e);
//    Form1->AddToMessagesVector( COMP_RUN, compile_scr_r, compile_scr_e);
//    Form1->AddToMessagesVector( STEP_RUN, step_scr_r, step_scr_e);
//    Form1->AddToMessagesVector( BREAK_SC, break_scr_r, break_scr_e);
//    Form1->AddToMessagesVector( MENU_ENCODING, encod_output_r, encod_output_e);
//    Form1->AddToMessagesVector( MOD_LBL, Label13_r, Label13_e);
//    Form1->AddToMessagesVector( NUM_MOD_LBL, Label14_rus, Label14_eng);
//    Form1->AddToMessagesVector( CAPT_CLICK, CaptureBox_r, CaptureBox_e);
//    Form1->AddToMessagesVector( REPORT_CLICK, CheckBox1_rus, CheckBox1_eng);
//    Form1->AddToMessagesVector( USB_LBL, Label21_rus, Label21_eng);
//    Form1->AddToMessagesVector( TECH_BTN, TechModeBtn_rus, TechModeBtn_eng);
//    Form1->AddToMessagesVector( CON_STATUS_BAR, CON_STATUS_BAR_r, CON_STATUS_BAR_e);
//    Form1->AddToMessagesVector( DISCON_STATUS_BAR, DISCON_STATUS_BAR_r, DISCON_STATUS_BAR_e);
//    Form1->AddToMessagesVector( CONSOLE_CAP, CONSOLE_CAP_r, CONSOLE_CAP_e);
//    Form1->AddToMessagesVector( SIZE_CAP, SIZE_CAP_r, SIZE_CAP_e);
//    Form1->AddToMessagesVector( CHSM_CAP, CHSM_CAP_r, CHSM_CAP_e);
//    Form1->AddToMessagesVector( REP_CAP, REP_CAP_r, REP_CAP_e);

//    Form1->AddToMessagesVector( CONNECT_BTN, ConBtnConnect_rus, ConBtnConnect_eng);
//    Form1->AddToMessagesVector( CONNECT_BTN, ConBtnDisconnect_rus, ConBtnDisconnect_eng);

//    Form1->AddToMessagesVector( USB_BTN, Btn7_ON_rus, Btn7_ON_eng);
//    Form1->AddToMessagesVector( USB_BTN, Btn7_OFF_rus, Btn7_OFF_eng);

//    Form1->AddToMessagesVector( LIB_NOT_FOUND, Lib_not_found_msg_r, Lib_not_found_msg_e);
//    Form1->AddToMessagesVector( LIB_ADDR_BAD, Lib_bad_addresses_r, Lib_bad_addresses_e);
//    Form1->AddToMessagesVector( LIB_ERR_CODE, Lib_errcode_r, Lib_errcode_e);
//    Form1->AddToMessagesVector( NO_RELE_FOUND, Lib_no_rel_r, Lib_no_rel_e);
//    Form1->AddToMessagesVector( RELEY_DETECTED, Lib_detected_rel_r, Lib_detected_rel_e);
//    Form1->AddToMessagesVector( FILE_REWITE, file_rewrite_r, file_rewrite_e);
//    Form1->AddToMessagesVector( REPORT_OPEN_ERROR, err_Open_report_r, err_Open_report_e);
//    Form1->AddToMessagesVector( ERROR_TITLE, ERROR_CAPTION_r, ERROR_CAPTION_e);
//    Form1->AddToMessagesVector( WARNING_TITLE, WARNING_CAPTION_r, WARNING_CAPTION_e);
//    Form1->AddToMessagesVector( SCRIPT_NOT_SELECT, err_Script_not_selected_r, err_Script_not_selected_e);
//    Form1->AddToMessagesVector( LOG_FILE_NOT_OPEN, err_log_open_r, err_log_open_e);
//    Form1->AddToMessagesVector( ERROR_OPEN_COM, err_open_com_r, err_open_com_e);
//    Form1->AddToMessagesVector( FORM_CLOSE, close_form_msg_r, close_form_msg_e);
//    Form1->AddToMessagesVector( ERR_VAL_INPUT, err_input_value_r, err_input_value_e);
//    Form1->AddToMessagesVector( ERR_VAL_IN_HEX, err_input_inHex_r, err_input_inHex_e);
//    Form1->AddToMessagesVector( ERR_VAL_SIZE, err_address_size_r, err_address_size_e);
//    Form1->AddToMessagesVector( ERR_OPEN_CAPTURE, err_capture_open_r, err_capture_open_e);
//    Form1->AddToMessagesVector( ERR_TEST_EMPTY, err_no_data_toSave_r, err_no_data_toSave_e);
//    Form1->AddToMessagesVector( ERR_OPEN_SV_FILE, err_saveFromScreen_open_r, err_saveFromScreen_open_e);
//    Form1->AddToMessagesVector( ERR_INI_OPEN, err_ini_open_r, err_ini_open_e);
//    Form1->AddToMessagesVector( TAB1_CAP, tab1_r, tab1_e);
//    Form1->AddToMessagesVector( TAB2_CAP, tab2_r, tab2_e);
//    Form1->AddToMessagesVector( TAB3_CAP, tab3_r, tab3_e);
//    Form1->AddToMessagesVector( TAB4_CAP, tab4_r, tab4_e);
//    Form1->AddToMessagesVector( SET_LBL, com_sett_r, com_sett_e);
//    Form1->AddToMessagesVector( COM_LBL, com_lbl_r, com_lbl_e);
//    Form1->AddToMessagesVector( SPEED_LBL, StaticText2_rus, StaticText2_eng);
//    Form1->AddToMessagesVector( BITS_LBL, Label3_rus, Label3_eng);
//    Form1->AddToMessagesVector( PAR_LBL, Label4_rus, Label4_eng);
//    Form1->AddToMessagesVector( STP_LBL, Label5_rus, Label5_eng);
//    Form1->AddToMessagesVector( RFID_LBL, Label23_rus, Label23_eng);
//    Form1->AddToMessagesVector( PROC_PARAM_LBL, proc_params_r, proc_params_e);
//    Form1->AddToMessagesVector( RAZR_LBL, razr_r, razr_e);
//    Form1->AddToMessagesVector( ARCH_LBL, arch_r, arch_e);
//    Form1->AddToMessagesVector( BIO_LBL, bios_r, bios_e);
//    Form1->AddToMessagesVector( WRK_FILES_LBL, wrk_settings_r, wrk_settings_e);
//    Form1->AddToMessagesVector( STEND_LBL, stend_r, stend_e);
//    Form1->AddToMessagesVector( REP_LBL, rep_r, rep_e);
//    Form1->AddToMessagesVector( CAPT_LBL, cap_r, cap_e);
//    Form1->AddToMessagesVector( SAVE_BTN, sv_stend_r, sv_stend_e);
//    Form1->AddToMessagesVector( CAPTURE_MODE_LBL, capMode_r, capMode_e);
//    Form1->AddToMessagesVector( TEXT_MODE_LBL, textMode_r, textMode_e);
//    Form1->AddToMessagesVector( BIN_MODE_LBL, binMode_r, binMode_e);

//    Form1->AddToMessagesVector( OPEN_PANEL, hint_open_r, hint_open_e);
//    Form1->AddToMessagesVector( NEW_PANEL, hint_new_r, hint_new_e);
//    Form1->AddToMessagesVector( ADD_PANEL, hint_add_r, hint_add_e);
//    Form1->AddToMessagesVector( DELETE_PANEL, hint_del_r, hint_del_e);
//    Form1->AddToMessagesVector( INS_PANEL, hint_ins_r, hint_ins_e);
//    Form1->AddToMessagesVector( SAVE_PANEL, hint_save_r, hint_save_e);
//    Form1->AddToMessagesVector( SAVEAS_PANEL, hint_saveas_r, hint_saveas_e);
//    Form1->AddToMessagesVector( FILE_EXIST, FILE_EXIST_r, FILE_EXIST_e );
//    Form1->AddToMessagesVector( SAVE_AS_MSG, SAVE_AS_MSG_r, SAVE_AS_MSG_e );
//    Form1->AddToMessagesVector( ERROR_NO_SIZE, ERROR_NO_SIZE_r, ERROR_NO_SIZE_e );
//    Form1->AddToMessagesVector( BYTES_LEFT, BYTES_LEFT_r, BYTES_LEFT_e );
//    Form1->AddToMessagesVector( UNABVLE_OPEN_FILE, UNABVLE_OPEN_FILE_r, UNABVLE_OPEN_FILE_e );

//    Form1->AddToMessagesVector( RUN_STR_NUM, RUN_STR_NUM_r, RUN_STR_NUM_e );

//    Form1->AddToMessagesVector( RUN_PANEL, hint_run_r, hint_run_e);
//    Form1->AddToMessagesVector( STOP_PANEL, hint_stop_r, hint_stop_e);
//    Form1->AddToMessagesVector( STEP_PANEL, hint_step_r, hint_step_e);
//    Form1->AddToMessagesVector( COMPILE_PANEL, hint_comp_r, hint_comp_e);

//    Form1->AddToMessagesVector( INI_DEL, del_from_ini_r, del_from_ini_e);
//    Form1->AddToMessagesVector( DEF_PATH, def_path_r, def_path_e);
//    Form1->AddToMessagesVector( CAPTURE_BIN, papture_bin_r, papture_bin_e);
//    Form1->AddToMessagesVector( CAPTURE_BIN, papture_bin_r, papture_bin_e);
//    Form1->AddToMessagesVector( RFID_ERR, NO_RFID_NUM_r, NO_RFID_NUM_r);
//    Form1->AddToMessagesVector( RFID_ERR_OPEN, RFID_ERR_OPEN_r, RFID_ERR_OPEN_e);
//    Form1->AddToMessagesVector( RFID_SETCOM_ERR, RFID_SETCOM_ERR_r, RFID_SETCOM_ERR_e);

//    Form1->AddToMessagesVector( REP_CMD, rep_cmd_r, rep_cmd_e);
//    Form1->AddToMessagesVector( OP_SZ, op_sz_r, op_sz_e);
//    Form1->AddToMessagesVector( OP_INOUT, op_inout_r, op_inout_e);
//    Form1->AddToMessagesVector( RD_DATA_CAP, rd_data_cap_r, rd_data_cap_e);
//    Form1->AddToMessagesVector( WR_DATA_CAP, wr_data_cap_r, wr_data_cap_e);
//    Form1->AddToMessagesVector( RD_BTNPort, rd_btnp_r, rd_btnp_e);
//    Form1->AddToMessagesVector( WR_BTNPort, wr_btnp_r, wr_btnp_e);
//    Form1->AddToMessagesVector( MEM_OPS, mem_ops_r, mem_ops_e);
//    Form1->AddToMessagesVector( FR_TO_FL, fr_to_fl_r, fr_to_fl_e);
//    Form1->AddToMessagesVector( FL_SZ_M, fl_sz_m_r, fl_sz_m_e);
//    Form1->AddToMessagesVector( RD_DATA_MEM, rd_data_cap_r, rd_data_cap_e);
//    Form1->AddToMessagesVector( WR_DATA_MEM, wr_data_cap_r, wr_data_cap_e);
//    Form1->AddToMessagesVector( RD_MEM_BTN, rd_mem_btn_r, rd_mem_btn_e);
//    Form1->AddToMessagesVector( WR_MEM_BTN, wr_mem_btn_r, wr_mem_btn_e);
//    Form1->AddToMessagesVector( JMP_MEM_BTN, jmp_mem_btn_r, jmp_mem_btn_e);
//    Form1->AddToMessagesVector( STAT_LBL, stst_r, stst_e);
//    Form1->AddToMessagesVector( CANCEL_BTN, can_btn_r, can_btn_e);
//    Form1->AddToMessagesVector( STAT_FLD, stat_fld_r, stat_fld_e);
//    Form1->AddToMessagesVector( ERR_OPEN_FILE, ERR_OPEN_FILE_r, ERR_OPEN_FILE_e);
//    Form1->AddToMessagesVector( ERR_DETECT_FILE, ERR_DETECT_FILE_r, ERR_DETECT_FILE_e);
//    Form1->AddToMessagesVector( ERR_SCRIPT_FORMAT, ERR_SCRIPT_FORMAT_r, ERR_SCRIPT_FORMAT_e);
//    Form1->AddToMessagesVector( ERR_FILE_SIZE, ERR_FILE_SIZE_r, ERR_FILE_SIZE_e);
//    Form1->AddToMessagesVector( MSG_ASK_FOR_REWR, MSG_ASK_FOR_REWR_r, MSG_ASK_FOR_REWR_e);
//    Form1->AddToMessagesVector( ERR_INI_FIND, err_ini_find_r, err_ini_find_e);
//    Form1->AddToMessagesVector( EMPTY_FILEPATH, EMPTY_FILEPATH_r, EMPTY_FILEPATH_e);
//    Form1->AddToMessagesVector( ON_USB_ERR,ON_USB_ERR_r,ON_USB_ERR_e);
//    Form1->AddToMessagesVector( ON_USB_OK, ON_USB_OK_r,ON_USB_OK_e);
//    Form1->AddToMessagesVector( OFF_USB_ERR, OFF_USB_ERR_r,OFF_USB_ERR_e);
//    Form1->AddToMessagesVector( OFF_USB_OK, OFF_USB_OK_r,OFF_USB_OK_e);
//    Form1->AddToMessagesVector( REPEAT_OP_MSG, REPEAT_OP_MSG_r, REPEAT_OP_MSG_e);
//    Form1->AddToMessagesVector( SND_OP_MSG, SND_OP_MSG_r, SND_OP_MSG_e);
//    Form1->AddToMessagesVector( NO_ADDRESS_IN, NO_ADDRESS_IN_r, NO_ADDRESS_IN_e);
//    Form1->AddToMessagesVector( OPERATION_COMP, OPERATION_COMP_r, OPERATION_COMP_e);
//    Form1->AddToMessagesVector( CRC_ERROR, CRC_ERROR_r, CRC_ERROR_e);
//    Form1->AddToMessagesVector( REPEAT_RD_MSG,REPEAT_RD_MSG_r, REPEAT_RD_MSG_e);
//    Form1->AddToMessagesVector( RD_MSG, RD_MSG_r, RD_MSG_e);
//    Form1->AddToMessagesVector( JMP_MSG, JMP_MSG_r, JMP_MSG_e);
}
