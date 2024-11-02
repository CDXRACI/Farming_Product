/* __FM_RTC_C */

#include "fm_rtc.h"

FM_V0x_Parameters_RTC_t              FM_V0x_RTC_Pars  ;
FM_V0x_Parameters_RTC_t              FM_V0x_Get_RTC   ;
FM_V0x_RTC_States_t                  FM_V0x_RTC_States;
RTC_TimeTypeDef                                  pTime;
RTC_HandleTypeDef                                 hrtc;
RTC_TimeTypeDef                                  sTime;
RTC_DateTypeDef                           DateToUpdate;

uint8_t g_check = 0;
uint8_t g_check_1 = 0;

extern void Error_Handler(void);

bool FM_V0x_Rtc_Init( void ) {

        FM_V0x_RTC_States = FM_V0x_RTC_STATE_FLAG_IS_OFF;

        DBG_OUT("-->[RTC_STATE] \"FM_RTC_V0x is initializing...\"\r\n");
        DBG_OUT_RAW("--> Time and Data are initializing. Format is: xxh-yymin-zzs. Mode is:%d\r\n", FM_V0x_RTC_States);

        /*----Set Time and Date: DB: CDP.Darkness ---*/
        FM_V0x_RTC_Pars.Set_Hour   =       FM_V0X_PARS_SET_HOUR; 
        FM_V0x_RTC_Pars.Set_Min    =       FM_V0X_PARS_SET_MIN ;
        FM_V0x_RTC_Pars.Set_Second =       FM_V0X_PARS_SET_SEC ;
        FM_V0x_RTC_Pars.Set_Day    =       FM_V0X_PARS_SET_DAY ;
        FM_V0x_RTC_Pars.Set_Mon    =       FM_V0X_PARS_SET_MONT;
        FM_V0x_RTC_Pars.Set_Year   =       FM_V0X_PARS_SET_YEAR;
    
        FM_V0x_RTC_States = FM_V0x_RTC_STATE_FLAG_IS_ON;
        DBG_OUT_RAW("[RTC STATE]: RTC is intialized. Mode is: %d\r\n", FM_V0x_RTC_States);

        FM_V0x_RTC_Set_Time(FM_V0x_RTC_Pars );
        FM_V0x_RTC_Set_Date(FM_V0x_RTC_Pars );
        
        if( !((FM_V0x_RTC_Pars.Set_Hour < FM_V0x_SET_0_HOUR_DEF ) || (FM_V0x_RTC_Pars.Set_Hour > FM_V0x_SET_23_HOUR_DEF )) ){
            return false;
        } else {
            return FM_V0x_RTC_States;
        }
}

uint8_t FM_V0x_RTC_Set_Time (FM_V0x_Parameters_RTC_t  RTC_SetTime ){

        if( FM_V0x_RTC_States == FM_V0x_RTC_STATE_FLAG_IS_ON ){
            hrtc.Instance = RTC;   
            if (( RTC_SetTime.Set_Hour >= FM_V0x_CHECK_TIME_IS_24HOUR ) && ( RTC_SetTime.Set_Hour < FM_V0x_CHECK_TIME_IS_0HOUR  )){
                DBG_OUT("-->BUG: Hour in RTC's Setting is not seted \r\n");
                return false;
            }
            hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
            hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
            if (HAL_RTC_Init( &hrtc ) != HAL_OK ){
                Error_Handler( ); }
            // if( HAL_RTCEx_BKUPRead( &hrtc, RTC_BKP_DR1 ) != FM_V0x_RTC_MEMORY_ADDRESS ){
            sTime.Hours   =  RTC_SetTime.Set_Hour;
            sTime.Minutes =  RTC_SetTime.Set_Min;
            sTime.Seconds =  RTC_SetTime.Set_Second; 

            if (HAL_RTC_SetTime( &hrtc, &sTime, RTC_FORMAT_BCD ) != HAL_OK ){
                Error_Handler( );}
      
            // HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, FM_V0x_RTC_MEMORY_ADDRESS );}
            FM_V0x_RTC_States  = FM_V0x_RTC_STATE_FLAG_IS_2;
            DBG_OUT_RAW("[RTC STATE]: Set time for RTC . Mode is: %d\r\n", FM_V0x_RTC_States);
        }
        if (( sTime.Hours >= FM_V0x_CHECK_TIME_IS_24HOUR ) || ( sTime.Hours < FM_V0x_CHECK_TIME_IS_0HOUR )){
                DBG_OUT( "-->BUG: Hour in RTC isn't set!\r\n" );
                return false;
        } else {
                return FM_V0x_RTC_States;
        }
}

uint8_t FM_V0x_RTC_Set_Date (FM_V0x_Parameters_RTC_t  RTC_SetDate  ){

        if( FM_V0x_RTC_States == FM_V0x_RTC_STATE_FLAG_IS_2 ){

            hrtc.Instance = RTC;     

            if (( RTC_SetDate.Set_Day   > 31 )  && ( RTC_SetDate.Set_Day < 0 )){
                DBG_OUT("-->BUG: Day in RTC  is not seted \r\n");  
                return false; }
            hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
            hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
          
            if (HAL_RTC_Init( &hrtc ) != HAL_OK ){
                Error_Handler( ); }

            DateToUpdate.Month   = RTC_SetDate.Set_Mon ;
            DateToUpdate.Date    = RTC_SetDate.Set_Day ;
            DateToUpdate.Year    = RTC_SetDate.Set_Year;

            if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK){
                Error_Handler(); }
          
            FM_V0x_RTC_States  = FM_V0x_RTC_STATE_FLAG_IS_3;
            DBG_OUT_RAW("[RTC STATE]: Set Date for RTC . Mode is: %d\r\n", FM_V0x_RTC_States);   
        }  
        if (( DateToUpdate.Date >= FM_V0x_CHECK_TIME_IS_24HOUR ) && ( DateToUpdate.Date < FM_V0x_CHECK_TIME_IS_0HOUR )) {
                DBG_OUT( "-->BUG: Hour in RTC isn't set!\r\n" );
                return false;
        } else { return  FM_V0x_RTC_States; }       
}
uint8_t g_Alam_Con_Flag = 0;

bool FM_V0x_RTC_Set_RTC ( ) {
       HAL_RTC_GetTime(&hrtc, &pTime, RTC_FORMAT_BIN);
        RTC_AlarmTypeDef sAlarm         = {0};
        sAlarm.AlarmTime.Hours          =  pTime.Hours;   
        sAlarm.AlarmTime.Minutes        =  pTime.Minutes + 1;
  
        if( g_check_1 == 0 ){
             sAlarm.AlarmTime.Seconds = pTime.Seconds;
             g_check_1 = 1;
        } else if ( g_check_1 == 1){
            sAlarm.AlarmTime.Seconds =  pTime.Seconds - 1;

        }
        sAlarm.Alarm = RTC_ALARM_A;
        if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK) {
        Error_Handler(); }
    return true;
}

uint8_t FM_V0x_RTC_Get_Time ( FM_V0x_Parameters_RTC_t  *RTC_GetTime ){
        
        if( FM_V0x_RTC_States == FM_V0x_RTC_STATE_FLAG_IS_3 ){

            HAL_RTC_GetTime(&hrtc, &pTime, RTC_FORMAT_BIN);
            RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour   = pTime.Hours;
            RTC_GetTime->FM_V0x_Get_TimeDate.Get_Min    = pTime.Minutes;
            if( g_check == 0 ){
            RTC_GetTime->FM_V0x_Get_TimeDate.Get_Second = pTime.Seconds;
            g_check = 1;
            }
            else if ( g_check == 1 ){
                RTC_GetTime->FM_V0x_Get_TimeDate.Get_Second = pTime.Seconds - 1;
            } else {
                // do nothing
            }
            (( RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour >= FM_V0x_SET_19_HOUR_DEF ) || (RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour < FM_V0x_SET_6_HOUR_DEF )) ? ( FM_V0X_RTC_WKUP_FLAG = FM_V0x_RTC_WKUP_FLAG_ON ):\
                                                                                                                       ( FM_V0X_RTC_WKUP_FLAG = FM_V0x_RTC_WKUP_FLAG_OFF );
            FM_V0x_RTC_States  = FM_V0x_RTC_STATE_FLAG_IS_4;
            DBG_OUT("RTC_STATE: =====================****RTC****========================\r\n");
            DBG_OUT_RAW("[RTC STATE]: RTC gets time. Mode is: %d. ",FM_V0x_RTC_States );
            DBG_OUT_RAW("Time is: %d %d %d\r\n",    RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour  ,  RTC_GetTime->FM_V0x_Get_TimeDate.Get_Min  ,  RTC_GetTime->FM_V0x_Get_TimeDate.Get_Second );
        }
        if ((   RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour     >= FM_V0x_CHECK_TIME_IS_24HOUR )   && (      RTC_GetTime->FM_V0x_Get_TimeDate.Get_Hour     < FM_V0x_CHECK_TIME_IS_0HOUR )) {
                DBG_OUT( "-->BUG: Hour in RTC isn't set!\r\n" );
                return false;
        } else { return   FM_V0x_RTC_States  ;}
}

uint8_t FM_V0x_RTC_Get_Date (FM_V0x_Parameters_RTC_t  *RTC_GetDate  ){
        if( FM_V0x_RTC_States == FM_V0x_RTC_STATE_FLAG_IS_4 ){

            HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN );
            RTC_GetDate->FM_V0x_Get_TimeDate.Get_Day    = DateToUpdate.Date;
            RTC_GetDate->FM_V0x_Get_TimeDate.Get_Mon    = DateToUpdate.Month;
            RTC_GetDate->FM_V0x_Get_TimeDate.Get_Year   = DateToUpdate.Year;
            FM_V0x_RTC_States  = FM_V0x_RTC_STATE_FLAG_IS_5;
            DBG_OUT_RAW("[RTC STATE]: RTC gets date. Mode is: %d. ",FM_V0x_RTC_States );
            DBG_OUT_RAW("Date is: %02d:%02d:%02d\r\n",    RTC_GetDate->FM_V0x_Get_TimeDate.Get_Day  ,  RTC_GetDate->FM_V0x_Get_TimeDate.Get_Mon  ,  RTC_GetDate->FM_V0x_Get_TimeDate.Get_Year );
            DBG_OUT("RTC_STATE: =====================****RTC****========================\r\n");
        } 
          FM_V0x_RTC_WakeUp(FM_V0x_Get_RTC);    
        if ((   RTC_GetDate->FM_V0x_Get_TimeDate.Get_Day     >= FM_V0x_CHECK_TIME_IS_24HOUR )   && (      RTC_GetDate->FM_V0x_Get_TimeDate.Get_Day     < FM_V0x_CHECK_TIME_IS_0HOUR )) {
                DBG_OUT( "-->BUG: Hour in RTC isn't set!\r\n" );
                return false;
            } else {
                return   RTC_GetDate->FM_V0x_Get_TimeDate.Get_Day  ;
        }

}

bool FM_V0x_RTC_WakeUp   ( FM_V0x_Parameters_RTC_t RTC_WakeUp){

         FM_V0x_RTC_WakeUp_States_t RTC_WakeUp_States = FM_V0x_FLAG_IS_0_DEF;
         if( FM_V0x_RTC_States == FM_V0x_RTC_STATE_FLAG_IS_5 ){

            if((RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour > FM_V0x_SET_23_HOUR_DEF           )||\
            ( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour < FM_V0x_SET_0_HOUR_DEF              )){
                    return false;
            }

            else if ((( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_16_HOUR_DEF ) && (RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Min == FM_V0x_SET_30_MIN_DEF ))||\
                    (( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_6_HOUR_DEF   ) && (RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Min == FM_V0x_SET_30_MIN_DEF )) ){

                            // FM_FUNC_GPIO_BUZZER_HIGH();
                            // FM_FUNC_Delay_5s();
                            // FM_FUNC_GPIO_BUZZER_LOW();
                            DBG_OUT("[RTC WKUP]: ............*****--LIGHT IS OFF. PUMP IS ON. STR IS OFF--****............\r\n");
                            FM_FUNC_GPIO_LIGHT_LOW();
                            FM_FUNC_GPIO_STR_LOW();
                            FM_FUNC_GPIO_PUMP_HIGH();
                            FM_FUNC_DELAY_60S();
                            FM_FUNC_GPIO_PUMP_LOW();
                            RTC_WakeUp_States = FM_V0x_FLAG_IS_1_DEF;
                            DBG_OUT("[RTC WKUP]: ............*****--LIGHT IS OFF. PUMP IS OFF. STR IS OFF--****............\r\n");
                            DBG_OUT_RAW("[RTC WKUP]: RTC WAKE UP. Mode is: %d.\r\n ",RTC_WakeUp_States );

            }

            else if ((( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_18_HOUR_DEF ) && (FM_V0X_RTC_WKUP_FLAG == FM_V0x_RTC_WKUP_FLAG_OFF  ))||\
                    (( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_6_HOUR_DEF   ) && (FM_V0X_RTC_WKUP_FLAG == FM_V0x_RTC_WKUP_FLAG_OFF  ))){
                             DBG_OUT("[RTC FLAG: ............*****--FLAG ISN'T SET--****............\r\n");
                    }

            else if ((( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_18_HOUR_DEF ) && (RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Min == FM_V0x_SET_30_MIN_DEF  ))||\
                    (( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour == FM_V0x_SET_6_HOUR_DEF   ) && (RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Min == FM_V0x_SET_0_MIN_DEF ))){
                            FM_V0X_RTC_WKUP_FLAG = FM_V0x_RTC_WKUP_FLAG_ON;
                             DBG_OUT("[RTC FLAG: ............*****--FLAG IS SET--****............\r\n");
                    }

            
            else if ((( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour >= FM_V0x_SET_18_HOUR_DEF ) && (FM_V0X_RTC_WKUP_FLAG == FM_V0x_RTC_WKUP_FLAG_ON  ))||\
                    (( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour <= FM_V0x_SET_6_HOUR_DEF   ) && (FM_V0X_RTC_WKUP_FLAG == FM_V0x_RTC_WKUP_FLAG_ON  ))){
                       
                            DBG_OUT("[RTC WKUP]: ............*****--LIGHT IS OFF WHICH IS READY TO ACTIVE--****..........\r\n");
                            // FM_FUNC_GPIO_BUZZER_HIGH();
                            // FUNC_DELAY_MS(175);
                            // FM_FUNC_GPIO_BUZZER_LOW();
                            FM_FUNC_GPIO_PUMP_LOW();
                            FM_FUNC_GPIO_STR_LOW();
                            FM_FUNC_GPIO_LIGHT_HIGH();
                            // FM_FUNC_GPIO_LED_STATUS_HIGH( );
                            RTC_WakeUp_States = FM_V0x_FLAG_IS_2_DEF;
                            DBG_OUT("[RTC WKUP]: ............*****--LIGHT IS ON. PUMP IS OFF. STR IS OFF--****...........\r\n");
                            DBG_OUT_RAW("[RTC WKUP]: RTC WAKE UP. Mode is: %d.\r\n ",RTC_WakeUp_States );
                }

            else if (( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour < FM_V0x_SET_18_HOUR_DEF )&&\
                    ( RTC_WakeUp.FM_V0x_Get_TimeDate.Get_Hour > FM_V0x_SET_6_HOUR_DEF   )){
                             FM_V0X_RTC_WKUP_FLAG = FM_V0x_RTC_WKUP_FLAG_OFF;
                            // FM_FUNC_GPIO_BUZZER_HIGH();
                            // FM_FUNC_Delay_5s();
                            // FM_FUNC_GPIO_BUZZER_LOW();
                            FM_FUNC_GPIO_PUMP_LOW();
                            FM_FUNC_GPIO_STR_LOW();
                            FM_FUNC_GPIO_LIGHT_LOW();
                             FM_FUNC_GPIO_LED_STATUS_LOW( );
                            RTC_WakeUp_States = FM_V0x_FLAG_IS_3_DEF;
                            DBG_OUT("[RTC WKUP]: ............*****--LIGHT IS OFF. PUMP IS OFF. STR IS OFF--****............\r\n");
                            DBG_OUT_RAW("[RTC WKUP]: RTC WAKE UP. Mode is: %d.\r\n ",RTC_WakeUp_States );
            }
    }

        FM_V0x_RTC_States = FM_V0x_RTC_STATE_FLAG_IS_3;
        if( RTC_WakeUp_States == FM_V0x_FLAG_IS_0_DEF ){
            return false;
        } else {   

        return  RTC_WakeUp_States;
        }
}

void FM_V0x_RTC_Loop(  ){
  FM_V0x_RTC_Get_Time(&FM_V0x_Get_RTC );
  FM_V0x_RTC_Get_Date(&FM_V0x_Get_RTC );

}

// //   FM_V0X_RTC_Con2Int = FM_RTC_ConV;
//   DBG_OUT_RAW("[TIME_RTC]: %02s:%02s\r\n", mydate, mytime);  
// //    uint8_t day = FM_V0X_RTC_Con2Int(mydate + 4);
//    uint8_t hours = FM_V0X_RTC_Con2Int(FM_RTC_ConV(mytime), 1);
//    uint8_t min   = FM_V0X_RTC_Con2Int(FM_RTC_ConV(mytime + 3), 1);
//    uint8_t sec   = FM_V0X_RTC_Con2Int(FM_RTC_ConV(mytime + 6), 1);

//    uint8_t mon  = FM_RTC_Conv_Mon(mydate);
//    uint8_t year  = FM_V0X_RTC_Con2Int(FM_RTC_ConV(mydate + 9), 1);
//    uint8_t day   = FM_V0X_RTC_Con2Int(FM_RTC_ConV(mydate + 4), 1);
//    DBG_OUT_RAW("[TIME_RTC1]: %02d:%02d:%02d\r\n", hours, min, sec );
//    DBG_OUT_RAW("[TIME_RTC1]: %02d:%02d:%02d\r\n", mon, year, day );

uint8_t FM_V0X_RTC_Con2Int( uint8_t (*func )( char* p), bool enable ){
    if( !enable){
        DBG_OUT_ERR("### RTC ERROR: Mode is: %d\r\n", enable);
        return false;
    }
    return *func;
}
uint8_t FM_RTC_ConV( char* p) {
  uint8_t cv = 0;
  if ('0' <= *p && *p <= 'p')
    cv = *p - 48;
  return 10 * cv + *++p - 48;
  /*
    11:
    49 - 48 =1
    10 + 49 - 48 = 11

    EX: 23
    50 - 48 =2
    20 + 51 - 48 = 23kk
  */
}

uint8_t FM_RTC_Conv_Mon( char *m ){
    uint8_t l_var = 0;
    switch(m[0]){
        case 'J': 
        l_var = (m[1] == 'a')? 1 : ((m[2] == 'n')  ? 6 : 7 );
        break;

        case 'F':
            l_var =  2;
            break;
        case 'A':
            l_var = ( m[2] == 'r' )? 4:8;
            break;
        case 'M':
            l_var = ( m[2] == 'r' )? 3:5;
            break;
        case 'S':
            l_var = 9;
            break;
        case 'O':
            l_var = 10;
            break;
        case 'N':
             l_var = 11;
             break;
        case 'D':
             l_var = 12;
             break;
        default:
        break;
    }
    return l_var;
}