/*
 * defines.hpp
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef COMMON_DEFINES_HPP_
#define COMMON_DEFINES_HPP_

#define WHICHFUNC fprintf (stderr, "%s\n", __FUNCTION__);
#define WHICHLINE fprintf (stderr, "%d\n", __LINE__);

typedef enum { True, False } Boolean;


#endif /* COMMON_DEFINES_HPP_ */
