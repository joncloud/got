#ifndef RES_INT_H_
#define RES_INT_H_

#include "res_man.h"

/**
 * Reads all entries into memory from the open @ref res_fp file.
 */
int res_rentries(void);

/**
 * Writes all entries from memory into the open @ref res_fp file.
 */
int res_wentries(void);

#endif
