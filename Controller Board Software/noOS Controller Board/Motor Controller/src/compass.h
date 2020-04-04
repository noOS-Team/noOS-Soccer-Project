/************************************************************************/
/* Author: Marc Spieler                                                 */
/* Team: noOS                                                           */
/* Created: 01.04.2020                                                  */
/************************************************************************/

#ifndef COMPASS_H
#define COMPASS_H

#include "asf.h"

void compassInit(void);
void compassMaintenance(void);
void setGoalReference(Bool inverted);
void compassCalibrationStep(void);
void setCompassIsBusy(void);
uint8_t compass_is_busy(void);

#endif
