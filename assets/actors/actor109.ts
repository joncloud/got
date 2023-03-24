const pic = [...Buffer.from('AAAAAACIiIyMjAAAAAAAAAAAAACIiIiMjIyMjAAAAAAAAACIiAAAAAAAAIyMAAAAAACIiAAAAAAAAAAAjIwAAACIiAAAAAAAAAAAAACMjACIiAAAAAAAAAAAAAAAAIyMiIgAAAAAAAAAAAAAAACMjIiIAAAAAAAAAAAAAAAAjIyJiQAAAAAAAAAAAAAAAIqKiYkAAAAAAAAAAAAAAACKiomJAAAAAAAAAAAAAAAAiooAiYkAAAAAAAAAAAAAiooAAACJiQAAAAAAAAAAiooAAAAAAImJAAAAAAAAiooAAAAAAAAAiYmJiYqKiooAAAAAAAAAAACJiYmKiooAAAAAAAAAAAAAiYmJiIiIAAAAAAAAAAAAiYmJiYiIiIgAAAAAAAAAiYkAAAAAAACIiAAAAAAAiYkAAAAAAAAAAIiIAAAAiYkAAAAAAAAAAAAAiIgAiYkAAAAAAAAAAAAAAACIiImJAAAAAAAAAAAAAAAAiIiJiQAAAAAAAAAAAAAAAIyMiooAAAAAAAAAAAAAAACMjIqKAAAAAAAAAAAAAAAAjIyKigAAAAAAAAAAAAAAAIwAAIqKAAAAAAAAAAAAAIyMAAAAiooAAAAAAAAAAIyMAAAAAACKigAAAAAAAIyMAAAAAAAAAIqKioqMjIyMAAAAAAAAAAAAioqKjIyMAAAAAAAAAAAAAIqKiomJiQAAAAAAAAAAAIqKioqJiYmJAAAAAAAAAIqKAAAAAAAAiYkAAAAAAIqKAAAAAAAAAACJiQAAAIqKAAAAAAAAAAAAAImJAIqKAAAAAAAAAAAAAAAAiYmKigAAAAAAAAAAAAAAAImJiooAAAAAAAAAAAAAAACJiYyMAAAAAAAAAAAAAAAAiIiMjAAAAAAAAAAAAAAAAIiIjIwAAAAAAAAAAAAAAACIiACMjAAAAAAAAAAAAACIiAAAAIyMAAAAAAAAAACIiAAAAAAAjIwAAAAAAACIiAAAAAAAAACMjIyMjIiIiAAAAAAAAAAAAACMjIyIiAAAAAAAAAAAAACMjIyKiooAAAAAAAAAAACMjIyMioqKigAAAAAAAACMjAAAAAAAAIqKAAAAAACMjAAAAAAAAAAAiooAAACMjAAAAAAAAAAAAACKigAAjAAAAAAAAAAAAAAAAIqKjIwAAAAAAAAAAAAAAACKioyMAAAAAAAAAAAAAAAAioqMjAAAAAAAAAAAAAAAAImJiIgAAAAAAAAAAAAAAACJiYiIAAAAAAAAAAAAAAAAiYkAiIgAAAAAAAAAAAAAiYkAAACIiAAAAAAAAAAAiYkAAAAAAIiIAAAAAAAAiYkAAAAAAAAAiIiIiImJiYkAAAAAAAAAAACIiIiJiYkAAAAAAAAAAAAAiIiMjIwAAAAAAAAAAAAAiIiIjIyMjIwAAAAAAAAAiIgAAAAAAACMjAAAAAAAiIgAAAAAAAAAAIyMAAAAiIgAAAAAAAAAAAAAjIwAiIgAAAAAAAAAAAAAAACMjIiIAAAAAAAAAAAAAAAAjIyIiAAAAAAAAAAAAAAAAIyMiYkAAAAAAAAAAAAAAACKiomJAAAAAAAAAAAAAAAAioqJiQAAAAAAAAAAAAAAAIqKAImJAAAAAAAAAAAAAIqKAAAAiYkAAAAAAAAAAIqKAAAAAACJiQAAAAAAAIqKAAAAAAAAAImJiYmKioqKAAAAAAAAAAAAiYmJioqKAAAAAAAAAAAAAImJiYiIiAAAAAAAAAAAAImJiYmIiIiIAAAAAAAAAImJAAAAAAAAiIgAAAAAAImJAAAAAAAAAACIiAAAAImJAAAAAAAAAAAAAIiIAImJAAAAAAAAAAAAAAAAiIiJiQAAAAAAAAAAAAAAAIiIiYkAAAAAAAAAAAAAAACMjIqKAAAAAAAAAAAAAAAAjIyKigAAAAAAAAAAAAAAAIyMiooAAAAAAAAAAAAAAACMAACKigAAAAAAAAAAAACMjAAAAIqKAAAAAAAAAACMjAAAAAAAiooAAAAAAACMjAAAAAAAAACKioqKjIyMjAAAAAAAAAAAAIqKioyMjAAAAAAAAAAAAACKioqJiYkAAAAAAAAAAACKioqKiYmJiQAAAAAAAACKigAAAAAAAImJAAAAAACKigAAAAAAAAAAiYkAAACKigAAAAAAAAAAAACJiQCKigAAAAAAAAAAAAAAAImJiooAAAAAAAAAAAAAAACJiYqKAAAAAAAAAAAAAAAAiYmMjAAAAAAAAAAAAAAAAIiIjIwAAAAAAAAAAAAAAACIiIyMAAAAAAAAAAAAAAAAiIgAjIwAAAAAAAAAAAAAiIgAAACMjAAAAAAAAAAAiIgAAAAAAIyMAAAAAAAAiIgAAAAAAAAAjIyMjIyIiIgAAAAAAAAAAAAAjIyMiIgAAAAAAAAAAAAAjIyMioqKAAAAAAAAAAAAjIyMjIqKiooAAAAAAAAAjIwAAAAAAACKigAAAAAAjIwAAAAAAAAAAIqKAAAAjIwAAAAAAAAAAAAAiooAAIwAAAAAAAAAAAAAAACKioyMAAAAAAAAAAAAAAAAioqMjAAAAAAAAAAAAAAAAIqKjIwAAAAAAAAAAAAAAACJiYiIAAAAAAAAAAAAAAAAiYmIiAAAAAAAAAAAAAAAAImJAIiIAAAAAAAAAAAAAImJAAAAiIgAAAAAAAAAAImJAAAAAACIiAAAAAAAAImJAAAAAAAAAIiIiIiJiYmJAAAAAAAAAAAAiIiIiYmJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCggAAAAAAAAAAAAAAAACCiYmCAAAAAAAAAAAAAACCiYiIiYIAAAAAAAAAAAAAAIKJiYIAAAAAAAAAAAAAAAAAgoIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCgoKCAAAAAAAAAAAAAIKCiYmJiYKCAAAAAAAAAIKJiIiIiIiJiYIAAAAAAACCiYgAAAAAiImCAAAAAACCiYgAAAAAAACIiYIAAAAAgomIAAAAAAAAiImCAAAAAIKJiAAAAAAAAIiJggAAAAAAgomIAAAAAIiJggAAAAAAAIKJiYiIiIiJiYIAAAAAAAAAgoKJiYmJgoIAAAAAAAAAAAAAgoKCggAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgoKCgoKCAAAAAAAAAACCgomJiYmJiYKCAAAAAACCiYmIiIiIiIiJiYIAAACCiYiIAAAAAAAAiIiJggCCiYiIAAAAAAAAAACIiImCgomIAAAAAAAAAAAAAIiJgoKJiAAAAAAAAAAAAACIiYKCiYgAAAAAAAAAAAAAiImCgomIAAAAAAAAAAAAAIiJgoKJiAAAAAAAAAAAAACIiYKCiYiIAAAAAAAAAACIiImCAIKJiIgAAAAAAACIiImCAAAAgomJiIiIiIiIiYmCAAAAAACCgomJiYmJiYKCAAAAAAAAAACCgoKCgoIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIKCgoIAAAAAAAAAAAAAgoKJiYmJgoIAAAAAAAAAgomIiIiIiImJggAAAAAAAIKJiAAAAACIiYIAAAAAAIKJiAAAAAAAAIiJggAAAACCiYgAAAAAAACIiYIAAAAAgomIAAAAAAAAiImCAAAAAACCiYgAAAAAiImCAAAAAAAAgomJiIiIiImJggAAAAAAAACCgomJiYmCggAAAAAAAAAAAACCgoKCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;
const shot = [...Buffer.from('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==', 'base64')] as const;

const actor_info = {
  move: 8,
  width: 16,
  height: 16,
  directions: 1,
  frames: 4,
  frame_speed: 4,
  frame_sequence: [0, 1, 2, 3],
  speed: 1,
  size_x: 15,
  size_y: 15,
  strength: 25,
  health: 0,
  num_moves: 1,
  shot_type: 0,
  shot_pattern: 0,
  shots_allowed: 0,
  solid: 0,
  flying: 0,
  rating: 0,
  type: 4,
  // 'SHIELD'
  name: [83, 72, 73, 69, 76, 68, 0, 0, 0],
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

