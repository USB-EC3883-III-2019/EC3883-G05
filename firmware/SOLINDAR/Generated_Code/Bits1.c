/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Bits1.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : BitsIO
**     Version     : Component 02.108, Driver 03.28, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-21, 12:55, # CodeGen: 77
**     Abstract    :
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This component is set to work in Output direction only.
**     Settings    :
**         Port name                   : PTC
**
**         Bit mask of the port        : $000F
**         Number of bits/pins         : 4
**         Single bit numbers          : 0 to 3
**         Values range                : 0 to 15
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTCD      [$0004]
**         Port control register       : PTCDD     [$0005]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    34   |   PTC0_TPM3CH0
**                    1      |    33   |   PTC1_TPM3CH1
**                    2      |    25   |   PTC2_TPM3CH2
**                    3      |    24   |   PTC3_TPM3CH3
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents    :
**         GetDir - bool Bits1_GetDir(void);
**         GetVal - byte Bits1_GetVal(void);
**         PutVal - void Bits1_PutVal(byte Val);
**         GetBit - bool Bits1_GetBit(byte Bit);
**         PutBit - void Bits1_PutBit(byte Bit, bool Val);
**         SetBit - void Bits1_SetBit(byte Bit);
**         ClrBit - void Bits1_ClrBit(byte Bit);
**         NegBit - void Bits1_NegBit(byte Bit);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Bits1.c
** @version 03.28
** @brief
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This component is set to work in Output direction only.
*/         
/*!
**  @addtogroup Bits1_module Bits1 module documentation
**  @{
*/         

/* MODULE Bits1. */

#include "Bits1.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Bits1_GetMsk (component BitsIO)
**
**     Description :
**         The method returns a bit mask which corresponds to the 
**         required bit position.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static const  byte Bits1_Table[4U] = { /* Table of mask constants */
   0x01U, 0x02U, 0x04U, 0x08U
};

static byte Bits1_GetMsk (byte PinIndex)
{
  return (byte)((PinIndex<4U) ? Bits1_Table[PinIndex] : 0U); /* Check range and return appropriate bit mask */
}

/*
** ===================================================================
**     Method      :  Bits1_GetVal (component BitsIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 15)
** ===================================================================
*/
byte Bits1_GetVal(void)
{
  return (byte)(getReg8(PTCD) & 0x0FU); /* Return port data */
}

/*
** ===================================================================
**     Method      :  Bits1_PutVal (component BitsIO)
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 15)
**     Returns     : Nothing
** ===================================================================
*/
void Bits1_PutVal(byte Val)
{
  Val &= 0x0FU;                        /* Mask output value */
  setReg8(PTCD, (getReg8(PTCD) & (byte)(~(byte)0x0FU)) | Val); /* Put masked value on port */
}

/*
** ===================================================================
**     Method      :  Bits1_GetBit (component BitsIO)
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 3)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Bits1_GetBit(byte Bit)
{
  byte const Mask = Bits1_GetMsk(Bit); /* Temporary variable - bit mask to test */
  return (bool)(((getReg8(PTCD) & Mask) == Mask)? 1U: 0U); /* Test if specified bit of port register is set */
}

/*
** ===================================================================
**     Method      :  Bits1_PutBit (component BitsIO)
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 3)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Bits1_PutBit(byte Bit, bool Val)
{
  byte const Mask = Bits1_GetMsk(Bit); /* Temporary variable - put bit mask */
  if (Val) {
    setReg8Bits(PTCD, Mask);           /* [bit (Bit)]=0x01U */
  } else { /* !Val */
    clrReg8Bits(PTCD, Mask);           /* [bit (Bit)]=0x00U */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  Bits1_ClrBit (component BitsIO)
**     Description :
**         This method clears (sets to zero) the specified bit
**         of the output value.
**         [ It is the same as "PutBit(Bit,FALSE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to clear (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Bits1_ClrBit(byte Bit)
{
  byte const Mask = Bits1_GetMsk(Bit); /* Temporary variable - set bit mask */
  clrReg8Bits(PTCD, Mask);             /* [bit (Bit)]=0x00U */
}

/*
** ===================================================================
**     Method      :  Bits1_SetBit (component BitsIO)
**     Description :
**         This method sets (sets to one) the specified bit of the
**         output value.
**         [ It is the same as "PutBit(Bit,TRUE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to set (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Bits1_SetBit(byte Bit)
{
  byte const Mask = Bits1_GetMsk(Bit); /* Temporary variable - set bit mask */
  setReg8Bits(PTCD, Mask);             /* [bit (Bit)]=0x01U */
}

/*
** ===================================================================
**     Method      :  Bits1_NegBit (component BitsIO)
**     Description :
**         This method negates (inverts) the specified bit of the
**         output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to invert (0 to 31)
**     Returns     : Nothing
** ===================================================================
*/
void Bits1_NegBit(byte Bit)
{
  byte const Mask = Bits1_GetMsk(Bit); /* Temporary variable - set bit mask */
  setReg8(PTCTOG, Mask);               /* [bit (Bit)]=0x01U */
}

/*
** ===================================================================
**     Method      :  Bits1_GetDir (component BitsIO)
**     Description :
**         This method returns direction of the component.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the component (always <true>, Output only)
**                      <false> = Input, <true> = Output
** ===================================================================
*/
/*
bool Bits1_GetDir(void)

**  This method is implemented as a macro. See Bits1.h file.  **
*/


/* END Bits1. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
