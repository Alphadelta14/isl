#ifndef ISL_BAND_PRIVATE_H
#define ISL_BAND_PRIVATE_H

#include <isl/band.h>
#include <isl/list.h>
#include <isl/schedule.h>
#include <isl/union_map.h>

/* Information about a band within a schedule.
 *
 * n is the number of scheduling dimensions within the band.
 * parallel is an array of length n, indicating whether a scheduling dimension
 *	is parallel.
 * map is the partial map corresponding to this band.
 * schedule is the schedule that contains this band.
 * parent is the parent of this band (or NULL if the band is a root).
 * children are the children of this band (or NULL if the band is a leaf).
 *
 * To avoid circular dependences in the reference counting,
 * the schedule and parent pointers are not reference counted.
 * isl_band_copy increments the reference count of schedule to ensure
 * that outside references to the band keep the schedule alive.
 */
struct isl_band {
	int ref;

	int n;
	int *parallel;

	isl_union_map *map;
	isl_schedule *schedule;
	isl_band *parent;
	isl_band_list *children;
};

#endif
