'use strict';

const pic = [...Buffer.from('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', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 37,
  width: 16,
  height: 16,
  directions: 4,
  frames: 3,
  frame_speed: 6,
  frame_sequence: [0, 1, 0, 2],
  speed: 2,
  size_x: 11,
  size_y: 15,
  strength: 0,
  health: 5,
  num_moves: 1,
  shot_type: 10,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 0,
  rating: 15,
  type: 4,
  // '10:WOM2'
  name: [49, 48, 58, 87, 79, 77, 50, 0, 0],
  func_num: 10,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 0,
  width: 16,
  height: 16,
  directions: 0,
  frames: 0,
  frame_speed: 0,
  frame_sequence: [0, 0, 0, 0],
  speed: 0,
  size_x: 2,
  size_y: 2,
  strength: 0,
  health: 0,
  num_moves: 0,
  shot_type: 0,
  shot_pattern: 1,
  shots_allowed: 0,
  solid: 0,
  flying: 0,
  rating: 0,
  type: 0,
  // ''
  name: [0, 0, 0, 0, 0, 0, 0, 0, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const actor = {
  pic,
  shot,
  actor_info,
  shot_info,
} as const;

export default actor;

