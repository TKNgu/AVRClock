/*
  TTSTime.h

  Author:Loovee
  2013-11-21

  The MIT License (MIT)
  Copyright (c) 2013 Seeed Technology Inc.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef __TTSTIME_H__
#define __TTSTIME_H__

#ifndef uchar
#define uchar unsigned char
#endif

#include "Wire.h"

class TTSTime {
private:
 uchar decToBcd(uchar val);
 uchar bcdToDec(uchar val);

public:
 TTSTime() { Wire.begin(); }
 void setTime(uchar hour, uchar min, uchar sec);  // set time
 void setTime(uchar, uchar, uchar, uchar, uchar, uchar, uchar);
 void getTime(uchar *hour, uchar *min, uchar *sec);  // get time
 void getTime(uchar *, uchar *, uchar *, uchar *, uchar *, uchar *, uchar *);
 uchar getHour();  // get hour
 uchar getMin();   // get minutes
 uchar getSec();   // get second
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
