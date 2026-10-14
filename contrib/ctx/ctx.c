#include "postgres.h"

#include "access/htup_details.h"
#include "commands/async.h"
#include "commands/trigger.h"
#include "executor/spi.h"
#include "lib/stringinfo.h"
#include "utils/rel.h"
#include "utils/memutils.h"
#include "utils/syscache.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(test_ctx);

Datum
test_ctx(PG_FUNCTION_ARGS)
{
	MemoryContext newAset = AllocSetContextCreate(CurrentMemoryContext,
												 "parent aset",
												 ALLOCSET_DEFAULT_SIZES);

	// create and remove context, so further context woulf be created
	// from freelist
	MemoryContext deleteAse = AllocSetContextCreate(CurrentMemoryContext,
												 "to delete aset",
												 ALLOCSET_DEFAULT_SIZES);
	MemoryContextDelete(deleteAse);

	MemoryContext newGen = GenerationContextCreate(newAset, "midle gen ctx",
													SLAB_DEFAULT_BLOCK_SIZE,
													SLAB_DEFAULT_BLOCK_SIZE,
													SLAB_DEFAULT_BLOCK_SIZE
	);

	MemoryContext asetLast = AllocSetContextCreate(newGen,
												"leaf aset",
												 ALLOCSET_DEFAULT_SIZES);

	MemoryContextDelete(newGen);
	MemoryContextDelete(asetLast);
	PG_RETURN_VOID();
}
