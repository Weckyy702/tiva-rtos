extern "C" [[noreturn]] void infinite_loop();

extern "C" [[gnu::weak]] void _start() { infinite_loop(); }
