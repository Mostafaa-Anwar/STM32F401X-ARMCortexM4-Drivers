/*
 * Bit_Math.h
 *
 *  Created on: Mar 21, 2023
 *      Author: Mostafa Anwar
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define Set_Bit(REG,BITNUM) (REG |= (1<<BITNUM)) 

#define Clr_Bit(REG,BITNUM) (REG &= (~(1<<BITNUM)))
 
#define TOG_BIT(REG,BITNUM) (REG ^= (1<<BITNUM))

#define Get_Bit(REG,BITNUM) ((REG >> (BITNUM))&1)



#define SET_BIT(REG,BITNUM) (REG |= (1<<BITNUM)) 

#define CLR_BIT(REG,BITNUM) (REG &= (~(1<<BITNUM)))
 
#define TOG_BIT(REG,BITNUM) (REG ^= (1<<BITNUM))

#define GET_BIT(REG,BITNUM) ((REG >> (BITNUM))&1)


#endif /* BIT_MATH_H_ */