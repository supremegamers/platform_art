/*
 * Copyright (C) 2019 The Android Open Source Project
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

#ifndef ART_RUNTIME_BINARY_ANALYZER_BINARY_ANALYZER_H_
#define ART_RUNTIME_BINARY_ANALYZER_BINARY_ANALYZER_H_

#include <cstdint>

#include "binary_analyzer_x86.h"
#include "dex/dex_file.h"
#include "runtime.h"



namespace art {
#if defined(__i386__) || defined(__x86_64__)
static bool IsFastJNI(uint32_t method_idx, const DexFile& dex_file, const void* fn_ptr) {
  bool is_fast = false;
  InstructionSet instruction_set = Runtime::Current()->GetInstructionSet();
  switch (instruction_set) {
    case InstructionSet::kX86:
    case InstructionSet::kX86_64: {
      x86::AnalysisResult result = x86::AnalyzeMethod(method_idx, dex_file, fn_ptr);
      if (result == x86::AnalysisResult::kFast) {
        is_fast = true;
        VLOG(jni) <<  dex_file.PrettyMethod(method_idx) << " is a fast JNI Method";
      } else {
        VLOG(jni) <<  dex_file.PrettyMethod(method_idx) << " is not a fast JNI Method: "
                           << x86::AnalysisResultToStr(result);
      }
      break;
    }
    case InstructionSet::kArm:
    case InstructionSet::kArm64:
      break;
    default:
      LOG(ERROR) << "Unsupported ISA!";
      break;
  }
  return is_fast;
}
#else
// Todo:FastJni is currently enabled on Arm instruction set
static bool IsFastJNI(uint32_t method_idx, const DexFile& dex_file, const void* fn_ptr) {
  UNUSED(method_idx);
  UNUSED(dex_file);
  UNUSED(fn_ptr);
  return false;
}
#endif

}  // namespace art

#endif  // ART_RUNTIME_BINARY_ANALYZER_BINARY_ANALYZER_H_
