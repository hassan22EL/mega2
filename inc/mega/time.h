
/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   time.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 0 Byte  
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 *  
 */

#ifndef TIME_H
#define	TIME_H
/* ***************************************************************************************************************
 *                                 Micros                                                                   *
 * ***************************************************************************************************************
 */
/*
 * *******************************************************************
 *                             index buffer                          *
 * *******************************************************************
 * */

typedef enum {
    rtc_sec = 0,
    rtc_min = 1,
    rtc_hour = 2,
    rtc_dayw = 3,
    rtc_daym = 4,
    rtc_month = 5,
    rtc_year = 6
} rtc_buffer_index;
/*
 ****************************************************
 *                    Convert data to timestamp                     *
 * **************************************************
 * @param ptm : pointer to buffer of date data 
 * @return    : timestamp value based 2000
 */

time_t rtcConvertDateToTime(uint8_t *ptm);
/*
 ************************************************************
 *            Convert timestamp to data                     *
 * **********************************************************
 * @param time    : timestamp value since 2000
 * @return ptm    : pointer to buffer to store date 
 */
void rtcConvertTimeToDate(time_t Time, uint8_t *ptm);

#endif	/* TIME_H */

