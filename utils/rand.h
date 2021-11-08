#ifndef RAND_H
#define RAND_H

/*
 * Generates a pseudo-random number between min and max.
 *
 * @param  min bottom end of range (inclusive).
 * @param  max top end of range (exclusive).
 * @return random number in the given range.
 */
int randint(int min, int max);

#endif