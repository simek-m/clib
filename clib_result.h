// err_t represents a return value.
// TODO:
// - It can be expanded to hold additional metadata.
// - Idea: Make it a struct of int (errno) and an optional pointer
//         If the errno == 0, no pointer. Otherwise pointer to
//         metadata (msg, context).
//         Caveats: allocations and not just stack?
// - Idea: inspiration from HRESULT?
typedef int err_t;

// TODO: is it a bad idea performance-wise
// TODO: (overhead, passing through registers, ...)?
// TODO: Type-safety?
typedef clib_result_t struct {
	bool is_ok;
	union {
	    // Result.
	    void *ok;
	    // Error.
	    err_t err;
	} result;
} clib_result_t;
