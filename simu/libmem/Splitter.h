/* License & includes {{{1 */
/* 
   ESESC: Super ESCalar simulator
   Copyright (C) 2010 University of California, Santa Cruz.

   Contributed by Jose Renau
                  Basilio Fraguela

This file is part of ESESC.

ESESC is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation;
either version 2, or (at your option) any later version.

ESESC is distributed in the  hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
ESESC; see the file COPYING. If not, write to the Free Software Foundation, 59
Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef SPLITTER_H
#define SPLITTER_H

#include "GStats.h"
#include "Port.h"
#include "MemRequest.h"
#include "MemObj.h"
/* }}} */

class Splitter: public MemObj {
protected:
  PortGeneric **scratchPort;
  //MRouter *routerLeft; // For scratch memory

  MemObj *lower_level;
  MemObj *lower_levelLeft;

  uint32_t numBanks;
  uint32_t numBankMask;

public:
  Splitter(MemorySystem* current, const char *device_descr_section, const char *device_name = NULL);
  ~Splitter() {}

  Time_t nextReadSlot(       const MemRequest *mreq);
  Time_t nextWriteSlot(      const MemRequest *mreq);
  Time_t nextBusReadSlot(    const MemRequest *mreq);
  Time_t nextPushDownSlot(   const MemRequest *mreq);
  Time_t nextPushUpSlot(     const MemRequest *mreq);
  Time_t nextInvalidateSlot( const MemRequest *mreq);

  // processor direct requests
  void read(MemRequest  *req);
  void write(MemRequest *req);
  void writeAddress(MemRequest *req);

  // DOWN
  void busRead(MemRequest *req);
  void pushDown(MemRequest *req);
  
  // UP
  void pushUp(MemRequest *req);
  void invalidate(MemRequest *req);

  // Status/state
  uint16_t getLineSize() const;

  bool canAcceptRead(DInst *dinst) const;
  bool canAcceptWrite(DInst *dinst) const;

  TimeDelta_t ffread(AddrType addr, DataType data);
  TimeDelta_t ffwrite(AddrType addr, DataType data);
  void        ffinvalidate(AddrType addr, int32_t lineSize);

};

#endif
