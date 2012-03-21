#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
 * MLSTACK definition.
 */

/*
 * MLSTACK used to keep all the data items of a dom tree and a parser
 * like elements, attributes, text, tokens in continious chunks of memory
 * called segments. No reallocations occur, just an new segment is allocated
 * when more memory needed to keep incoming data. The segment size should be
 * tuned in order to minimize memory fragmentation. No item deletion is defined,
 * so the vector is static. All the segments a freed when the whole vector is 
 * freed.
 */

#define MLSTACK(type)								\
struct {									\
	size_t sgcnt; 	/* segments count */					\
	size_t sgsz;	/* segment size */					\
	size_t upper;	/* the highest allocated segment's index */		\
	int sg;	/* current segment's index */					\
	size_t si;	/* current element's index in the current
				   segment, use signed to be able to handle
				   segment switch */				\
	type** data;	/* array of pointers to segments */			\
}

#define MLSTACK_DUMP(s) do {							\
	printf("stack:\n");							\
	printf("\tsgcnt: %d\n", (s)->sgcnt);					\
	printf("\tsgsz: %d\n", (s)->sgsz);					\
	printf("\tupper: %d\n", (s)->upper);					\
	printf("\tsg: %d\n", (s)->sg);						\
	printf("\tsi: %d\n", (s)->si);						\
} while (0)

#define MLSTACK_INIT(s, cnt, sz) do {						\
	(s)->sgcnt = (cnt);							\
	(s)->sgsz = (sz);							\
	(s)->data = malloc(sizeof(*((s)->data)) * (cnt));			\
	(s)->data[0] = malloc(sizeof(**((s)->data)) * (sz));			\
	(s)->upper = 0;								\
	(s)->sg = 0;								\
	(s)->si = 0;								\
} while (0)

#define MLSTACK_FREE(s) do {							\
	for ((s)->sg = 0; (s)->sg <= (s)->upper; (s)->sg++)			\
		free((s)->data[(s)->sg]);					\
	free((s)->data);							\
} while (0)

#define MLSTACK_PUSH(s, e) do {							\
	(s)->data[(s)->sg][(s)->si] = (e);					\
	(s)->si++;								\
	if ((s)->si == (s)->sgsz) {						\
		(s)->sg++;							\
		(s)->si = 0;							\
	}									\
	if ((s)->sg > (s)->upper) {						\
		(s)->upper++;							\
		assert((s)->upper != (s)->sgcnt					\
				&& "Insufficient MLSTACK segment count\n");	\
		(s)->data[(s)->sg] = malloc((s)->sgsz				\
				* sizeof(**((s)->data)));			\
	}									\
} while (0)

/* allocate new element and assign it's address to ept */
#define MLSTACK_PUSH_NEW(s, eptr) do {						\
	(eptr) = & ((s)->data[(s)->sg][(s)->si]);				\
	(s)->si++;								\
	if ((s)->si == (s)->sgsz) {						\
		(s)->sg++;							\
		(s)->si = 0;							\
	}									\
	if ((s)->sg > (s)->upper) {						\
		(s)->upper++;							\
		assert((s)->upper != (s)->sgcnt					\
				&& "Insufficient MLSTACK segment count\n");	\
		(s)->data[(s)->sg] = malloc((s)->sgsz				\
				* sizeof(**((s)->data)));			\
	}									\
} while (0)

#define MLSTACK_POP(s, eptr) do {						\
	if ((s)->si == 0) {							\
		(s)->sg--;							\
		(s)->si = (s)->sgsz;						\
	}									\
	(s)->si--;								\
	assert((s)->sg >= 0 && "No items in stack\n");				\
	*(eptr) = (s)->data[(s)->sg][(s)->si];					\
} while (0)

#define MLSTACK_POPREF(s, eptr) do {						\
	if ((s)->si == 0) {							\
		(s)->sg--;							\
		(s)->si = (s)->sgsz;						\
	}									\
	(s)->si--;								\
	assert((s)->sg >= 0 && "No items in stack\n");				\
	eptr = &((s)->data[(s)->sg][(s)->si]);					\
} while (0)

#define MLSTACK_SKIP_POP(s) do {						\
	if ((s)->si == 0) {							\
		(s)->sg--;							\
		(s)->si = (s)->sgsz;						\
	}									\
	(s)->si--;								\
	assert((s)->sg >= 0 && "No items in stack\n");				\
} while (0)

#define MLSTACK_TOP(s) ( ((s)->si == 0) ? \
	(((s)->sg - 1 < 0) ? \
		NULL \
		: &((s)->data[(s)->sg - 1][(s)->sgsz - 1])) \
	: &((s)->data[(s)->sg][(s)->si - 1]) )

