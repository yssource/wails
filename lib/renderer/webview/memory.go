package webview

/*
#include <stdlib.h>
*/
import "C"

import "unsafe"

// This is our allocated C Memory
var memory []unsafe.Pointer

func saveMemoryReference(mem unsafe.Pointer) {
	memory = append(memory, mem)
}

func freeMemory() {
	for _, mem := range memory {
		C.free(mem)
	}
}

func string2CString(str string) *C.char {
	result := C.CString(str)
	saveMemoryReference(unsafe.Pointer(result))
	return result
}
