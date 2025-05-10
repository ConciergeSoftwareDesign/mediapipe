/* Copyright 2023 The MediaPipe Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_H_
#define MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

// The delegate to run MediaPipe. If the delegate is not set, the default
// delegate CPU is used. Use `delegate_options` to configure advanced
// features of the selected delegate."
enum Delegate {
  CPU = 0,
  GPU = 1,
  // Edge TPU acceleration using NNAPI delegate.
  EDGETPU_NNAPI = 2,
};


// Base options for MediaPipe C Tasks.
struct BaseOptions {
  // The model asset file contents as bytes.
  const char* model_asset_buffer;

  // The size of the model assets buffer (or `0` if not set).
  unsigned int model_asset_buffer_count;

  // The path to the model asset to open and mmap in memory.
  const char* model_asset_path;

  // Use a specific delegate
  Delegate delegate;

  // Load pre-compiled serialized binary cache to accelerate init process.
  // Only available on Android. Kernel caching will only be enabled if this
  // path is set. NOTE: binary cache usage may be skipped if valid serialized
  // model, specified by "serialized_model_dir", exists.
  const char* gpu_delegate_cached_kernel_path;

  // A dir to load from and save to a pre-compiled serialized model used to
  // accelerate init process.
  // NOTE: serialized model takes precedence over binary cache
  // specified by "cached_kernel_path", which still can be used if
  // serialized model is invalid or missing.
  const char* gpu_delegate_serialized_model_dir;

  // Unique token identifying the model. Used in conjunction with
  // "serialized_model_dir". It is the caller's responsibility to ensure
  // there is no clash of the tokens.
  const char* gpu_delegate_model_token;
};

#ifdef __cplusplus
}  // extern C
#endif

#endif  // MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_H_
