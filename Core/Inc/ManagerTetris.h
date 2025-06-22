/*
 * ManagerTetris.h
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#ifndef INC_MANAGERTETRIS_H_
#define INC_MANAGERTETRIS_H_

#define CUSTOMI 0x7C
#define CUSTOMO 1
#define CUSTOML 2
#define CUSTOMS 3
#define CUSTOMZ 4
#define CUSTOMT 5
#define CUSTOMJ 6


void initGame(void);
void taskTetris(void);
int gameRunning(void);

#endif /* INC_MANAGERTETRIS_H_ */
