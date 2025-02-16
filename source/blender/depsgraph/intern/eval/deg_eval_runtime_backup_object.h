/* SPDX-FileCopyrightText: 2019 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup depsgraph
 */

#pragma once

#include <optional>

#include "DNA_object_types.h"
#include "DNA_session_uid_types.h"

#include "BKE_object_types.hh"

#include "BLI_map.hh"

#include "intern/eval/deg_eval_runtime_backup_modifier.h"

struct Object;

namespace blender::deg {

struct Depsgraph;

class ObjectRuntimeBackup {
 public:
  ObjectRuntimeBackup(const Depsgraph *depsgraph);

  /* Make a backup of object's evaluation runtime data, additionally
   * make object to be safe for free without invalidating backed up
   * pointers. */
  void init_from_object(Object *object);
  void backup_modifier_runtime_data(Object *object);
  void backup_pose_channel_runtime_data(Object *object);

  /* Restore all fields to the given object. */
  void restore_to_object(Object *object);
  /* NOTE: Will free all runtime data which has not been restored. */
  void restore_modifier_runtime_data(Object *object);
  void restore_pose_channel_runtime_data(Object *object);

  bke::ObjectRuntime runtime;
  std::optional<LightLinkingRuntime> light_linking_runtime;
  short base_flag;
  unsigned short base_local_view_bits;
  Map<int, ModifierDataBackup> modifier_runtime_data;
  Map<SessionUID, bPoseChannel_Runtime> pose_channel_runtime_data;
};

}  // namespace blender::deg
