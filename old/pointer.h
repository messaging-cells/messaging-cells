

//----------------------------------------------------------------------------

/*
void * operator new(size_t sz) noexcept {
	return 0;
}

void operator delete(void *pt) noexcept {
}

void * operator new[](size_t sz) noexcept {
	return operator new(sz);
}

void operator delete[](void *pt) noexcept {
	operator delete(pt);
}

void * operator new(size_t sz, std::nothrow_t) noexcept {
	return operator new(sz);
}

void operator delete(void *pt, std::nothrow_t) noexcept {
	operator delete(pt);
}*/

