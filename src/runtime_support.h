/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_SRC_RUNTIME_SUPPORT_H_
#define ART_SRC_RUNTIME_SUPPORT_H_

#include "class_linker.h"
#include "object.h"
#include "thread_list.h"
#include "utils.h"

namespace art {

extern void CheckSuspendFromCode(Thread* thread);
extern Array* CheckAndAllocArrayFromCode(uint32_t type_idx, Method* method, int32_t component_count,
                                         Thread* self, bool access_check);
extern void DebugMe(Method* method, uint32_t info);
extern void UpdateDebuggerFromCode(Method* method, Thread* thread , int32_t dex_pc, Method** sp);
extern Object* DecodeJObjectInThread(Thread* thread, jobject obj);
extern Field* FindFieldFromCode(uint32_t field_idx, const Method* referrer, Thread* self,
                                bool is_static, bool is_primitive, bool is_set, size_t expected_size);
extern void* FindNativeMethod(Thread* thread);
extern void ThrowAbstractMethodErrorFromCode(Method* method, Thread* thread, Method** sp);
const void* UnresolvedDirectMethodTrampolineFromCode(Method*, Method**, Thread*,
                                                     Runtime::TrampolineType);
extern Class* ResolveVerifyAndClinit(uint32_t type_idx, const Method* referrer, Thread* self,
                                     bool can_run_clinit, bool verify_access);
extern Class* InitializeTypeFromCode(uint32_t type_idx, Method* method);
uint32_t IsAssignableFromCode(const Class* klass, const Class* ref_class);
void ObjectInitFromCode(Object* o);
extern void LockObjectFromCode(Thread* thread, Object* obj);
uint32_t TraceMethodUnwindFromCode(Thread* self);
extern int32_t CmpgDouble(double a, double b);
extern int32_t CmplDouble(double a, double b);
extern int32_t CmpgFloat(float a, float b);
extern int32_t CmplFloat(float a, float b);
extern int64_t D2L(double d);
extern int64_t F2L(float f);

}  // namespace art

// Helpers for both compiled code and libart.
extern "C" void art_deliver_exception_from_code(void*);
extern "C" void art_proxy_invoke_handler();
extern "C" void art_update_debugger(void*, void*, int32_t, void*);

#if defined(__arm__)
  /* Compiler helpers */
  extern "C" int32_t __memcmp16(void*, void*, int32_t);
  extern "C" int32_t art_indexof(void*, uint32_t, uint32_t, uint32_t);
  extern "C" int32_t art_string_compareto(void*, void*);
  extern "C" int32_t art_get32_static_from_code(uint32_t);
  extern "C" int64_t art_get64_static_from_code(uint32_t);
  extern "C" void* art_get_obj_static_from_code(uint32_t);
  extern "C" int32_t art_get32_instance_from_code(uint32_t, void*);
  extern "C" int64_t art_get64_instance_from_code(uint32_t, void*);
  extern "C" void* art_get_obj_instance_from_code(uint32_t, void*);
  extern "C" int art_set32_static_from_code(uint32_t, int32_t);
  extern "C" int art_set64_static_from_code(uint32_t, int64_t);
  extern "C" int art_set_obj_static_from_code(uint32_t, void*);
  extern "C" int art_set32_instance_from_code(uint32_t, void*, int32_t);
  extern "C" int art_set64_instance_from_code(uint32_t, void*, int64_t);
  extern "C" int art_set_obj_instance_from_code(uint32_t, void*, void*);
  extern "C" void art_can_put_array_element_from_code(void*, void*);
  extern "C" void art_check_cast_from_code(void*, void*);
  extern "C" void art_do_long_jump(uint32_t*, uint32_t*);
  extern "C" void art_handle_fill_data_from_code(void*, void*);
  extern "C" void art_invoke_direct_trampoline_with_access_check(uint32_t, void*);
  extern "C" void art_invoke_interface_trampoline(uint32_t, void*);
  extern "C" void art_invoke_interface_trampoline_with_access_check(uint32_t, void*);
  extern "C" void art_invoke_static_trampoline_with_access_check(uint32_t, void*);
  extern "C" void art_invoke_super_trampoline_with_access_check(uint32_t, void*);
  extern "C" void art_invoke_virtual_trampoline_with_access_check(uint32_t, void*);
  extern "C" void art_lock_object_from_code(void*);
  extern "C" void art_test_suspend();
  extern "C" void art_throw_array_bounds_from_code(int32_t index, int32_t limit);
  extern "C" void art_throw_div_zero_from_code();
  extern "C" void art_throw_neg_array_size_from_code(int32_t size);
  extern "C" void art_throw_no_such_method_from_code(int32_t method_idx);
  extern "C" void art_throw_null_pointer_exception_from_code();
  extern "C" void art_throw_stack_overflow_from_code(void*);
  extern "C" void art_throw_verification_error_from_code(int32_t src1, int32_t ref);
  extern "C" void art_unlock_object_from_code(void*);
  extern "C" void* art_alloc_array_from_code(uint32_t, void*, int32_t);
  extern "C" void* art_alloc_array_from_code_with_access_check(uint32_t, void*, int32_t);
  extern "C" void* art_alloc_object_from_code(uint32_t type_idx, void* method);
  extern "C" void* art_alloc_object_from_code_with_access_check(uint32_t type_idx, void* method);
  extern "C" void* art_check_and_alloc_array_from_code(uint32_t, void*, int32_t);
  extern "C" void* art_check_and_alloc_array_from_code_with_access_check(uint32_t, void*, int32_t);
  extern "C" void* art_initialize_static_storage_from_code(uint32_t, void*);
  extern "C" void* art_initialize_type_from_code(uint32_t, void*);
  extern "C" void* art_initialize_type_and_verify_access_from_code(uint32_t, void*);
  extern "C" void art_trace_entry_from_code(void*);
  extern "C" void art_trace_exit_from_code();
  extern "C" void* art_resolve_string_from_code(void*, uint32_t);
  extern "C" void art_work_around_app_jni_bugs();

  /* Conversions */
  extern "C" float __aeabi_i2f(int32_t op1);         // INT_TO_FLOAT
  extern "C" int32_t __aeabi_f2iz(float op1);        // FLOAT_TO_INT
  extern "C" float __aeabi_d2f(double op1);          // DOUBLE_TO_FLOAT
  extern "C" double __aeabi_f2d(float op1);          // FLOAT_TO_DOUBLE
  extern "C" double __aeabi_i2d(int32_t op1);        // INT_TO_DOUBLE
  extern "C" int32_t __aeabi_d2iz(double op1);       // DOUBLE_TO_INT
  extern "C" float __aeabi_l2f(int64_t op1);         // LONG_TO_FLOAT
  extern "C" double __aeabi_l2d(int64_t op1);        // LONG_TO_DOUBLE

  /* Single-precision FP arithmetics */
  extern "C" float __aeabi_fadd(float a, float b);   // ADD_FLOAT[_2ADDR]
  extern "C" float __aeabi_fsub(float a, float b);   // SUB_FLOAT[_2ADDR]
  extern "C" float __aeabi_fdiv(float a, float b);   // DIV_FLOAT[_2ADDR]
  extern "C" float __aeabi_fmul(float a, float b);   // MUL_FLOAT[_2ADDR]
  extern "C" float fmodf(float a, float b);          // REM_FLOAT[_2ADDR]

  /* Double-precision FP arithmetics */
  extern "C" double __aeabi_dadd(double a, double b); // ADD_DOUBLE[_2ADDR]
  extern "C" double __aeabi_dsub(double a, double b); // SUB_DOUBLE[_2ADDR]
  extern "C" double __aeabi_ddiv(double a, double b); // DIV_DOUBLE[_2ADDR]
  extern "C" double __aeabi_dmul(double a, double b); // MUL_DOUBLE[_2ADDR]
  extern "C" double fmod(double a, double b);         // REM_DOUBLE[_2ADDR]

  /* Integer arithmetics */
  extern "C" int __aeabi_idivmod(int32_t op1, int32_t op2);  // REM_INT[_2ADDR|_LIT8|_LIT16]
  extern "C" int __aeabi_idiv(int32_t op1, int32_t op2);     // DIV_INT[_2ADDR|_LIT8|_LIT16]

  /* Long long arithmetics - REM_LONG[_2ADDR] and DIV_LONG[_2ADDR] */
  extern "C" long long __aeabi_ldivmod(long long op1, long long op2);
  extern "C" long long __aeabi_lmul(long long op1, long long op2);
  extern "C" uint64_t art_shl_long(uint64_t, uint32_t);
  extern "C" uint64_t art_shr_long(uint64_t, uint32_t);
  extern "C" uint64_t art_ushr_long(uint64_t, uint32_t);

#endif

#if defined(__mips__)
  /* Conversions */
  extern "C" float __floatsisf(int op1);        // INT_TO_FLOAT
  extern "C" int32_t __fixsfsi(float op1);      // FLOAT_TO_INT
  extern "C" float __truncdfsf2(double op1);    // DOUBLE_TO_FLOAT
  extern "C" double __extendsfdf2(float op1);   // FLOAT_TO_DOUBLE
  extern "C" double __floatsidf(int op1);       // INT_TO_DOUBLE
  extern "C" int32_t __fixdfsi(double op1);     // DOUBLE_TO_INT
  extern "C" float __floatdisf(int64_t op1);    // LONG_TO_FLOAT
  extern "C" double __floatdidf(int64_t op1);   // LONG_TO_DOUBLE
  extern "C" int64_t __fixsfdi(float op1);      // FLOAT_TO_LONG
  extern "C" int64_t __fixdfdi(double op1);     // DOUBLE_TO_LONG

  /* Single-precision FP arithmetics */
  extern "C" float __addsf3(float a, float b);   // ADD_FLOAT[_2ADDR]
  extern "C" float __subsf3(float a, float b);   // SUB_FLOAT[_2ADDR]
  extern "C" float __divsf3(float a, float b);   // DIV_FLOAT[_2ADDR]
  extern "C" float __mulsf3(float a, float b);   // MUL_FLOAT[_2ADDR]
  extern "C" float fmodf(float a, float b);      // REM_FLOAT[_2ADDR]

  /* Double-precision FP arithmetics */
  extern "C" double __adddf3(double a, double b); // ADD_DOUBLE[_2ADDR]
  extern "C" double __subdf3(double a, double b); // SUB_DOUBLE[_2ADDR]
  extern "C" double __divdf3(double a, double b); // DIV_DOUBLE[_2ADDR]
  extern "C" double __muldf3(double a, double b); // MUL_DOUBLE[_2ADDR]
  extern "C" double fmod(double a, double b);     // REM_DOUBLE[_2ADDR]

  /* Long long arithmetics - REM_LONG[_2ADDR] and DIV_LONG[_2ADDR] */
  extern "C" long long __divdi3(int64_t op1, int64_t op2);
  extern "C" long long __moddi3(int64_t op1, int64_t op2);
#endif

#endif  // ART_SRC_RUNTIME_SUPPORT_H_
