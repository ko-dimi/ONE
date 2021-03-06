/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_BACKEND_IDYNAMICTENSOR_MANAGER_H__
#define __ONERT_BACKEND_IDYNAMICTENSOR_MANAGER_H__

#include "ITensorManager.h"

#include <ir/Index.h>
#include <ir/Operation.h>
#include <ir/Shape.h>
#include <backend/ITensor.h>

namespace onert
{
namespace backend
{

/**
 * @brief Interface as an abstract tensor manager, providing ways to handle memory
 *        for dynamic tensors.
 */
struct IDynamicTensorManager : public ITensorManager
{
  virtual ~IDynamicTensorManager() = default;

public:
  /**
   * @brief Allocate memory for dynamic tensor
   */
  virtual void allocate(const ir::OperandIndex &, const ir::Shape &) = 0;

  /**
   * @brief Change shape of tensor, which makes the tensor "dynamic"
   * @note  This should be called before execution.
   */
  virtual void changeShape(const ir::OperandIndex &, const ir::Shape &) = 0;

  /**
   * @brief Plans when to delete a tensor. Note this planning is done at compilation time.
   */
  virtual void planDealloc(const ir::Operation *op, ir::OperandIndex operand_ind) = 0;

  /**
   * @brief Deallocate input tensors of op if an input tensor is a dynamic tensor and it won't
   *        be used anymore
   * @note  This will work after calling planDealloc
   */
  virtual void deallocInput(const ir::Operation *op) = 0;

  /**
   * @brief Deallocate an output tensor if the tensor is a dynamic tensor
   * @note  This will work after calling planDealloc
   */
  virtual void deallocSubgraphOutput(ir::OperandIndex ind) = 0;
};

} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_IDYNAMICTENSOR_MANAGER_H__
