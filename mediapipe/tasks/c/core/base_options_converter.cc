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

#include "mediapipe/tasks/c/core/base_options_converter.h"

#include <memory>
#include <string>
#include <variant>
#include <optional>

#include "mediapipe/tasks/c/core/base_options.h"
#include "mediapipe/tasks/cc/core/base_options.h"

namespace mediapipe::tasks::c::core {

void CppConvertToBaseOptions(const BaseOptions& in,
                             mediapipe::tasks::core::BaseOptions* out) {
  out->model_asset_buffer =
      in.model_asset_buffer
          ? std::make_unique<std::string>(
                in.model_asset_buffer,
                in.model_asset_buffer + in.model_asset_buffer_count)
          : nullptr;
  out->model_asset_path =
      in.model_asset_path ? std::string(in.model_asset_path) : "";
  out->delegate = static_cast<mediapipe::tasks::core::BaseOptions::Delegate>((int) in.delegate);
  if (in.delegate == Delegate::GPU) {
    mediapipe::tasks::core::BaseOptions::GpuOptions gpu_options;
    if (in.gpu_delegate_cached_kernel_path) {
      gpu_options.cached_kernel_path = std::string(in.gpu_delegate_cached_kernel_path);
    }
    if (in.gpu_delegate_serialized_model_dir) {
      gpu_options.serialized_model_dir = std::string(in.gpu_delegate_serialized_model_dir);
    }
    if (in.gpu_delegate_model_token) {
      gpu_options.model_token = std::string(in.gpu_delegate_model_token);
    }
    out->delegate_options = gpu_options;
  }
}

}  // namespace mediapipe::tasks::c::core
