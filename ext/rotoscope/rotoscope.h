#ifndef _INC_ROTOSCOPE_H_
#define _INC_ROTOSCOPE_H_

#include <unistd.h>
#include "stack.h"

#define EVENT_CALL (RUBY_EVENT_CALL | RUBY_EVENT_C_CALL)
#define EVENT_RETURN (RUBY_EVENT_RETURN | RUBY_EVENT_C_RETURN)

#define CLASS_METHOD "class"
#define INSTANCE_METHOD "instance"

#define STACK_CAPACITY 500
#define LOG_BUFFER_SIZE 1000

// clang-format off

#define RS_CSV_HEADER \
  "entity,caller_entity,filepath,lineno,method_name,method_level,caller_method_name,caller_method_level"
#define RS_CSV_FORMAT "\"%s\",\"%s\",\"%s\",%d,\"%s\",%s,\"%s\",%s"
#define RS_CSV_VALUES(method, caller_method, call_site) \
  StringValueCStr((method).class_name),        \
  StringValueCStr((caller_method).class_name), \
  StringValueCStr((call_site)->filepath),      \
  (call_site)->lineno,                         \
  StringValueCStr(method.name),                \
  (method).level,                              \
  StringValueCStr(caller_method.name),         \
  (caller_method).level

// clang-format on

typedef enum {
  RS_CLOSED = 0,
  RS_OPEN,
  RS_TRACING,
} rs_state;

typedef struct {
  VALUE self;
  VALUE log;
  VALUE tracepoint;
  VALUE blacklist;
  pid_t pid;
  unsigned long tid;
  rs_state state;
  rs_stack_t stack;
  VALUE output_buffer;
} Rotoscope;

#endif
