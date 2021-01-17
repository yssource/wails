package counter

import "sync"

type Counter struct {
	initialValue uint64
	value        uint64
	lock         sync.Mutex
}

func NewCounter(initialValue uint64) *Counter {
	return &Counter{
		initialValue: initialValue,
		value:        initialValue,
	}
}

// SetValue sets the value to the given value
func (c *Counter) SetValue(value uint64) {
	c.lock.Lock()
	c.value = value
	c.lock.Unlock()
}

// Increment adds 1 to the counter and returns its value
func (c *Counter) Increment() uint64 {
	var result uint64
	c.lock.Lock()
	c.value++
	result = c.value
	c.lock.Unlock()
	return result
}

// Reset the value to the initial value
func (c *Counter) Reset() {
	c.lock.Lock()
	c.value = c.initialValue
	c.lock.Unlock()
}
