const pic = [...Buffer.from('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', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAIgAAAAAAAAAAAAAAAAAAIiIiAAAAAAAAAAAAAAAAIiIiIiIAAAAAAAAAAAAAAAAAzwAAAAAAAAAAAAAAAAAAAM8AAAAAAAAAAAAAAAAAAADPAAAAAAAAAAAAAAAAAAAAzwAAAAAAAAAAAAAAAAAAAM8AAAAAAAAAAAAAAAAAAADPAAAAAAAAAAAAAAAAAAAAzwAAAAAAAAAAAAAAAAAAR89HAAAAAAAAAAAAAAAARwDPAEcAAAAAAAAAAAAAAABHz0cAAAAAAAAAAAAAAABHAM8ARwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABHAM8ARwAAAAAAAAAAAAAAAEfPRwAAAAAAAAAAAAAAAEcAzwBHAAAAAAAAAAAAAAAAR89HAAAAAAAAAAAAAAAAAADPAAAAAAAAAAAAAAAAAAAAzwAAAAAAAAAAAAAAAAAAAM8AAAAAAAAAAAAAAAAAAADPAAAAAAAAAAAAAAAAAAAAzwAAAAAAAAAAAAAAAAAAAM8AAAAAAAAAAAAAAAAAAADPAAAAAAAAAAAAAAAAACIiIiIiAAAAAAAAAAAAAAAAIiIiAAAAAAAAAAAAAAAAAAAiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAiAAAAAAAAAABHAEcAAAAiIgAAAAAAAABHAEcAAAAiIiLPz8/Pz8/Pz8/PzwAAACIiAAAAAAAAAEcARwAAAAAAIgAAAAAAAAAARwBHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABHAEcAAAAAAAAAACIAAAAAAEcARwAAAAAAAAAiIgAAAM/Pz8/Pz8/Pz8/PzyIiAAAARwBHAAAAAAAAACIiAAAARwBHAAAAAAAAAAAiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 3,
  width: 16,
  height: 16,
  directions: 4,
  frames: 3,
  frame_speed: 4,
  frame_sequence: [0, 1, 0, 2],
  speed: 1,
  size_x: 13,
  size_y: 15,
  strength: 5,
  health: 15,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 2,
  shots_allowed: 4,
  solid: 1,
  flying: 0,
  rating: 10,
  type: 2,
  // 'ARCHER'
  name: [65, 82, 67, 72, 69, 82, 0, 0, 0],
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
  frame_speed: 1,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 13,
  size_y: 13,
  strength: 10,
  health: 0,
  num_moves: 2,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 1,
  flying: 1,
  rating: 0,
  type: 3,
  // 'ARROW'
  name: [65, 82, 82, 79, 87, 0, 0, 0, 0],
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
