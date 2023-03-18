const pic = [...Buffer.from('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', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAFQAAAAAAAAAAAAAAAAAAABYAAAAAAAAAAAAAAAAAABUXFQAAAAAAAAAAAAAAAAAA0wAAAAAAAAAAAAAAAAAAAMwAAAAAAAAAAAAAAAAAAADMAAAAAAAAAAAAAAAAAAAAzAAAAAAAAAAAAAAAAAAAAMwAAAAAAAAAAAAAAAAAAADMAAAAAAAAAAAAAAAAAAAT0xMAAAAAAAAAAAAAAAAWFRMVFgAAAAAAAAAAAAAAFgAVABYAAAAAAAAAAAAAAAAAFgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABYAAAAAAAAAAAAAAAAAFgAVABYAAAAAAAAAAAAAABYVExUWAAAAAAAAAAAAAAAAE9MTAAAAAAAAAAAAAAAAAADMAAAAAAAAAAAAAAAAAAAAzAAAAAAAAAAAAAAAAAAAAMwAAAAAAAAAAAAAAAAAAADMAAAAAAAAAAAAAAAAAAAAzAAAAAAAAAAAAAAAAAAAANMAAAAAAAAAAAAAAAAAABUXFQAAAAAAAAAAAAAAAAAAFgAAAAAAAAAAAAAAAAAAABUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhYAAAAAAAAVAAAAAAAAExUAAAAAABUWF9PMzMzMzNMTFRYAAAAAABUAAAAAAAATFQAAAAAAAAAAAAAAAAAAABYWAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABYWAAAAAAAAAAAAAAAAAAAAFRMAAAAAAAAVAAAAAAAWFRPTzMzMzMzTFxYVAAAAAAAVEwAAAAAAABUAAAAAAAAWFgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 29,
  width: 16,
  height: 16,
  directions: 4,
  frames: 3,
  frame_speed: 4,
  frame_sequence: [0, 1, 0, 2],
  speed: 2,
  size_x: 15,
  size_y: 15,
  strength: 20,
  health: 30,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 1,
  shots_allowed: 1,
  solid: 1,
  flying: 0,
  rating: 0,
  type: 2,
  // 'YELGAURD'
  name: [89, 69, 76, 71, 65, 85, 82, 68, 0],
  func_num: 0,
  func_pass: 0,
  future1: [0, 0, 0, 0, 0, 0],
} as const;

const shot_info = {
  move: 1,
  width: 16,
  height: 16,
  directions: 4,
  frames: 1,
  frame_speed: 4,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 12,
  size_y: 12,
  strength: 20,
  health: 0,
  num_moves: 2,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 0,
  rating: 0,
  type: 3,
  // 'YELSHOT'
  name: [89, 69, 76, 83, 72, 79, 84, 0, 0],
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

