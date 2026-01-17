# Test Suite for Graph API (C)

A complete unit test suite for a **directed** Graph ADT written in C, built with the **Check** unit testing framework.  
This repository is intended to be dropped into an autograder / course project where the Graph implementation is provided as a shared library (`libgraph.so`) and the public API is defined in `include/graph.h`.

---

## Repository Layout

```
.
├── include/              # Public headers (graph.h)
├── lib/                  # Prebuilt libgraph shared libraries + libgraph.so symlink/copy
├── tests/                # All unit tests (one file per API function)
│   ├── main.c
│   ├── setup_teardown.c  # shared fixtures + compare/destroy helpers
│   ├── test_graph_starter.c
│   └── graph_*_test.c
├── Makefile
└── README.md
```

**Note:** The build outputs are generated into:
- `obj/` — compiled object files  
- `bin/` — the test runner binary (`bin/test_graph`)

---

## What’s Tested

This suite verifies correctness (not OOM behavior) for:

### Creation & Destruction
- `graph_create` (NULL compare function rejected, destroy function optional)
- `graph_destroy` (safe on NULL, calls `destroy_fn` exactly once per stored payload)

### Payload Operations
- `graph_insert` (success, NULL args, duplicate payload detection via `compare_fn`)
- `graph_remove` (success/missing/NULL, removes incoming + outgoing edges as required)

### Edge Operations (Directed)
- `graph_connect` (success, NULL args, endpoint missing, duplicate edge rejected)
- `graph_disconnect` (success, missing edge/endpoint, NULL args)
- Directionality is enforced (A→B is distinct from B→A)

### Queries / Inspection
- `graph_size`
- `graph_contains`
- `graph_get_all_payloads` (insertion order)
- `graph_get_neighbors` (edge insertion order, zero-outgoing behavior)
- `graph_has_edge`
- `graph_indegree`, `graph_outdegree`
- `graph_edge_count`
- `graph_reachable`
- `graph_has_cycle` (including self-loop cycle)
- `graph_is_connected`

> Out-of-memory conditions (`GRAPH_STATUS_NO_MEMORY`) are intentionally not tested.

---

## Requirements

- GCC (or a compatible C compiler)
- `check` library available via `pkg-config`

### Install Check

**Ubuntu/Debian**
```bash
sudo apt-get update
sudo apt-get install -y check pkg-config
```

**macOS (Homebrew)**
```bash
brew install check pkg-config
```

---

## Build & Run (Using the Included Makefile)

### 1) Set up the correct shared library

This repo includes architecture-specific builds in `lib/`.  
Run:

```bash
make setup-lib
```

This copies the correct one to `lib/libgraph.so` based on your architecture:
- `lib/libgraph-linux-amd64.so` → `lib/libgraph.so`
- `lib/libgraph-linux-arm64.so` → `lib/libgraph.so`

### 2) Build the test runner

```bash
make
```

This produces:
- `bin/test_graph` (test executable)
- `obj/*.o` (object files)

### 3) Run tests

```bash
make test
```

You should see output like:

```
==> Running unit tests
Running suite(s): ...
100%: Checks: XX, Failures: 0, Errors: 0
```

### 4) Clean build artifacts

```bash
make clean
```

---

## Notes on Linking / Runtime

The Makefile links against `-lgraph` and sets:

- `-Llib` (search for `libgraph.so` in `./lib`)
- runtime rpath: `$$ORIGIN/../lib`

That means the executable in `bin/` will load the shared library from `lib/` at runtime.

If you move the binary, keep the relative layout or update rpath accordingly.

---

## Contributing

If you’d like to extend the suite:
- Keep tests deterministic (no reliance on timing)
- Prefer small, isolated tests with a fresh graph per test (fixtures)
- Avoid OOM/malloc-failure injection unless explicitly required by the assignment

---

## License

MIT (or replace with your preferred license).
