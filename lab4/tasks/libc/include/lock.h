/** @file lock.h
 *
 * @brief Declares task creation interface
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-21
 */

#ifndef LOCK_H
#define LOCK_H

#include <bits/types.h>

int mutex_create();
int mutex_lock(int mutex);
int mutex_unlock(int mutex);

#endif /* LOCK_H */
