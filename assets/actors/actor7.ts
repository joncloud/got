const pic = [...Buffer.from('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', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 4,
  width: 16,
  height: 16,
  directions: 4,
  frames: 3,
  frame_speed: 6,
  frame_sequence: [0, 1, 0, 2],
  speed: 3,
  size_x: 15,
  size_y: 15,
  strength: 25,
  health: 20,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 0,
  rating: 0,
  type: 2,
  // 'ELF'
  name: [69, 76, 70, 0, 0, 0, 0, 0, 0],
  func_num: 0,
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
  size_x: 0,
  size_y: 0,
  strength: 0,
  health: 0,
  num_moves: 0,
  shot_type: 0,
  shot_pattern: 0,
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
